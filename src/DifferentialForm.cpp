// DifferentialForm.cpp
#include "Lie-Alg/LieAlgebra.h"

static int permutationSign(const std::vector<int>& original, const std::vector<int>& sorted) {
    // A simple (but not optimal) method: compute the number of transpositions
    int sign = 1;
    std::vector<int> temp = original;
    for (size_t i = 0; i < temp.size(); ++i) {
        for (size_t j = i + 1; j < temp.size(); ++j) {
            if (temp[i] > temp[j]) 
                sign = -sign;
        }
    }
    return sign;
}

DifferentialForm DifferentialForm::wedge(const DifferentialForm& other) const {
    DifferentialForm result;
    
    // Loop over terms in this form
    for (auto& term1 : this->terms) {
        const std::vector<int>& indices1 = term1.first;
        double coeff1 = term1.second;
        
        // Loop over terms in the other form
        for (auto& term2 : other.terms) {
            const std::vector<int>& indices2 = term2.first;
            double coeff2 = term2.second;
            
            // Check if indices are disjoint
            std::vector<int> combined = indices1;
            combined.insert(combined.end(), indices2.begin(), indices2.end());
            
            // Check for duplicates:
            bool duplicate = false;
            std::map<int, int> count;
            for (int idx : combined) {
                if (++count[idx] > 1) 
                    { duplicate = true; break; }
            }
            if (duplicate) 
                continue; // wedge product is zero if any basis appears twice.
            
            // Compute the sorted order and sign change.
            std::vector<int> sorted = combined;
            std::sort(sorted.begin(), sorted.end());
            int sign = permutationSign(combined, sorted);
            
            // Add the term to the result.
            result.addTerm(sorted, coeff1 * coeff2 * sign);
        }
    }
    
    return result;
}

DifferentialForm DifferentialForm::exteriorDerivative() const {
    DifferentialForm result;
    LieAlgebra lie;  // You might want to pass this in instead.
    
    // Loop over each term in the form
    for (const auto& term : this->terms) {
        const std::vector<int>& indices = term.first;  // e.g. {i1, i2, ..., ik}
        double coeff = term.second;
        int k = indices.size();
        
        // Apply d using the Leibniz rule.
        // For each index in the term, remove it and wedge in d(e^i)
        for (int j = 0; j < k; ++j) {
            // Build the remaining wedge product: remove indices[j]
            std::vector<int> remaining;
            for (int m = 0; m < k; ++m) {
                if (m != j) 
                    remaining.push_back(indices[m]);
            }
            
            // Get d(e^{indices[j]})
            DifferentialForm dEi = lie.dOf(indices[j]);
            
            // Create a DifferentialForm corresponding to the wedge of the remaining part.
            DifferentialForm remForm;
            remForm.addTerm(remaining, 1.0);  // coefficient 1
            
            // Compute the wedge product: remForm wedge dEi.
            DifferentialForm termContribution = remForm.wedge(dEi);
            
            // The sign is (-1)^(j+1) (here j is zero-indexed, so we use j+1)
            double sign = ((j + 1) % 2 == 0) ? 1.0 : -1.0;
            
            // Multiply the term contribution by the coefficient and sign.
            for (auto& t : termContribution.terms) {
                t.second *= coeff * sign;
            }
            
            // Add termContribution to the result.
            for (auto& t : termContribution.terms) {
                result.addTerm(t.first, t.second);
            }
        }
    }
    
    return result;
}

void DifferentialForm::print() const {
    for (auto term = terms.begin(); term != terms.end(); ++term) {
        double coeff = term->second;
        const std::vector<int>& indices = term->first;
        
        std::cout << coeff;
        
        if (!indices.empty()) {
            std::cout << " * ";
            for (size_t i = 0; i < indices.size(); ++i) {
                std::cout << "e^" << indices[i];
                if (i != indices.size() - 1)
                    std::cout << " ∧ ";
            }
        }
        if ( term == (--terms.end() ) ){
            std::cout << "." << std::endl;
            break;
        }
        std::cout << " + ";
    }
}

