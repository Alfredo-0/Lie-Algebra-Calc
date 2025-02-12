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

    int getDegree() const {
        if (terms.empty())
            return 0; // or you could throw an exception if appropriate
        return terms.begin()->first.size();
    }

    void addTerm(const std::vector<int>& indices, double coeff) {
        std::vector<int> sortedIndices = indices;
        std::sort(sortedIndices.begin(), sortedIndices.end());

        terms[sortedIndices] += coeff;
    }

    bool checkZero(){
        bool check = true;

        for (const auto& term : this -> terms) {
            if (term.second != 0)
                return false;
        }
        return check;
    }

    DifferentialForm wedge(const DifferentialForm& other) const;
    
    DifferentialForm exteriorDerivative() const;
    
    void print() const;

    std::string toLatexString() const;

};

#endif // DIFFERENTIAL_FORM_H
