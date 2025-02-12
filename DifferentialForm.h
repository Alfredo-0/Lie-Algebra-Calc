// DifferentialForm.h
#ifndef DIFFERENTIAL_FORM_H
#define DIFFERENTIAL_FORM_H

#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>

class DifferentialForm {
public:
    // The internal representation: 
    // Each key is an ordered list of indices (e.g. {1,3,4} for e^1^e^3^e^4)
    // and the value is the coefficient.
    std::map<std::vector<int>, double> terms;
    
    // Constructors
    DifferentialForm() {}

    ~DifferentialForm() {}

    // Add a term given a sorted basis vector and its coefficient.
    void addTerm(const std::vector<int>& indices, double coeff) {
        std::vector<int> sortedIndices = indices;
        std::sort(sortedIndices.begin(), sortedIndices.end());
        // (Optional: if the key already exists, add to the coefficient.)
        terms[sortedIndices] += coeff;
    }
    
    // Wedge product: returns a new DifferentialForm which is the wedge product of this form and 'other'
    DifferentialForm wedge(const DifferentialForm& other) const;
    
    // Exterior derivative: compute d(form) given a function that returns d(e^i)
    DifferentialForm exteriorDerivative() const;
    
    // Print the form (for debugging)
    void print() const {
    // Iterate over each term in the differential form.
        for (auto term = terms.begin(); term != terms.end(); ++term) {
            double coeff = term->second;
            const std::vector<int>& indices = term->first;
            
            // Print the coefficient.
            std::cout << coeff;
            
            // If there are basis elements, print them.
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

    bool checkZero(){
        double total = 0;
        bool check = true;

        for (const auto& term : this -> terms) {
            if (term.second != 0)
                return false;
        }

        return check;
    }

    std::string toLatexString() const {
        std::stringstream ss;
        ss << "$";  // Start LaTeX math mode
        
        bool firstTerm = true;
        // Loop over each term in the differential form.
        for (const auto& term : terms) {
            double coeff = term.second;
            const std::vector<int>& indices = term.first;
            
            if (!firstTerm) {
                ss << " + ";
            }
            
            // Print the coefficient.
            if(coeff<0)
                ss << '(' << coeff << ')';
            else
                ss << coeff;
            
            // If there are basis elements, print them in the form e^{i1} \wedge e^{i2} \wedge ...
            if (!indices.empty()) {
                ss << " \\cdot ";
                std::string index = " ";
                for (size_t i = 0; i < indices.size(); ++i) {
                    
                    index += std::to_string(indices[i]);
                    
                    //ss << "e^{" << indices[i] << "}";
                    //if (i != indices.size() - 1) {
                    //    ss << " \\wedge ";
                    //}
                }
                ss << "e^{"<< index << "}";
            }
            
            firstTerm = false;
        }
        ss << "$";  // End LaTeX math mode
        
        return ss.str();
    }

};

#endif // DIFFERENTIAL_FORM_H
