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

    DifferentialForm() {}

    ~DifferentialForm() {}

    // Add a term given a sorted basis vector and its coefficient.
    void addTerm(const std::vector<int>& indices, double coeff) {
        std::vector<int> sortedIndices = indices;
        std::sort(sortedIndices.begin(), sortedIndices.end());

        terms[sortedIndices] += coeff;
    }

    DifferentialForm wedge(const DifferentialForm& other) const;
    
    DifferentialForm exteriorDerivative() const;
    
    void print() const;

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
        //ss << "$";  // Start LaTeX math mode
        
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
            else if (coeff != 1)
                ss << coeff;
            
            // If there are basis elements, print them in the form e^{i1} \wedge e^{i2} \wedge ...
            if (!indices.empty()) {
                //ss << " \\cdot ";
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
        //ss << "$";  // End LaTeX math mode
        
        return ss.str();
    }

};

#endif // DIFFERENTIAL_FORM_H
