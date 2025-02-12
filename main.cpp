// main.cpp
#include "DifferentialForm.h"
#include <iostream>
#include <fstream>
#include <sstream>

int main() {
    
    std::ofstream outfile("../output.md");
    if (!outfile) {
        std::cerr << "Error: Could not open output.md for writing." << std::endl;
        return 1;
    }   

    for(int i = 1; i <= 6; ++i){
        for(int j = i+1; j <= 6; ++j){
            for(int k = j+1; k <= 6; ++k){
                DifferentialForm form;

                form.addTerm({i,j,k}, 1.0);
                
                DifferentialForm dform = form.exteriorDerivative();

                if(!dform.checkZero()){
                    std::string latexString = form.toLatexString();
                    std::string dlatexString = dform.toLatexString();

                    outfile << "$d("<<latexString<<")  = " << dlatexString << "$\n\n";

                    //form.print();
                    //dform.print();
                }
            }
        }
    }

    outfile.close();
    std::cout << "Differential form written to output.md" << std::endl;
 
    return 0;
}
