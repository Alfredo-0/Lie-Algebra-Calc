// LieAlgebra.h
#ifndef LIE_ALGEBRA_H
#define LIE_ALGEBRA_H

#include "DifferentialForm.h"
#include <map>
#include <vector>

// This class encapsulates the Lie algebra structure constants,
// i.e. it gives d(e^i) for i=1,...,6.
class LieAlgebra {
public:
    // For each basis index i (1-indexed), we store the DifferentialForm d(e^i)
    // For example, if d(e^4) = e^1 ^ e^5, then structureConstants[4] is the form with one term {1,5} with coefficient 1.
    std::map<int, DifferentialForm> structureConstants;
    
    LieAlgebra() {
        // Initialize: e.g., assume d(e^1) = d(e^2) = d(e^3) = 0, d(e^4) = e^1^e^5, etc.
        for (int i = 1; i <= 6; ++i) {
            DifferentialForm dEi;
            structureConstants[i] = dEi; // defaults to zero form
        }
        // Set d(e^4) = e^1^e^5 as an example:
        structureConstants[4].addTerm({1,5}, 1.0);
        structureConstants[6].addTerm({1,3}, 1.0);

        // You can initialize the other structure constants as needed.
    }
    
    // Return d(e^i)
    DifferentialForm dOf(int i) const {
        auto it = structureConstants.find(i);
        if (it != structureConstants.end())
            return it->second;
        else
            return DifferentialForm(); // zero form
    }
};

#endif // LIE_ALGEBRA_H
