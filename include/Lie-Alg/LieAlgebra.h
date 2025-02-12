// LieAlgebra.h
#ifndef LIE_ALGEBRA_H
#define LIE_ALGEBRA_H

#include "Lie-Alg/DifferentialForm.h"
#include <map>
#include <vector>

// This class encapsulates the Lie algebra structure constants,
// The values are given d(e^i) for i=1,...,6.
class LieAlgebra {
public:
    std::map<int, DifferentialForm> structureConstants;
    
    LieAlgebra() {
        for (int i = 1; i <= 6; ++i) {
            DifferentialForm dEi;
            structureConstants[i] = dEi; // defaults to zero form
        }

        structureConstants[4].addTerm({1,5}, 1.0);
        structureConstants[6].addTerm({1,3}, 1.0);
    }
    
    DifferentialForm dOf(int i) const {
        auto it = structureConstants.find(i);
        if (it != structureConstants.end())
            return it->second;
        else
            return DifferentialForm(); // zero vector
    }
};

#endif // LIE_ALGEBRA_H
