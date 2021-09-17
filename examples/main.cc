#include <iostream>
#include "btageffanalyzer.h"

int main() {

    // Inputs
    float jet_eta = 1.3;
    float jet_pt = 1500.0;;

    // BTagEffAnalyzer
    BTagEffAnalyzer effAnalyzer;
    effAnalyzer.readFile(
        "data/btageffmap-2016postVFP.json"
    );

    // Eval
    double eff = effAnalyzer.getEfficiency("DY", jet_eta, jet_pt);
    std::cout << "eff: " << eff << std::endl;
    
}