#include <iostream>
#include "btageffanalyzer.h"

int main() {

    // Inputs
    float jet_eta = 1.3;
    float jet_pt = 1500.0;;
    // std::string filePath = "data/btageffmap-2016postVFP.json";
    // std::string filePath = "data/btageffmap-2017.json";
    std::string filePath = "data/btageffmap-2018.json";
    std::string hadronFlavour = "b";

    // BTagEffAnalyzer
    BTagEffAnalyzer effAnalyzer;
    effAnalyzer.readFile(filePath, hadronFlavour);

    // Eval
    double eff = effAnalyzer.getEfficiency("TTTo2L2Nu", jet_eta, jet_pt);
    std::cout << "eff: " << eff << std::endl;
    
}