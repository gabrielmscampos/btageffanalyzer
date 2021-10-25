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

    // Eval missing dataset default to TTTo2L2Nu
    double eff = effAnalyzer.getEfficiency("Signal_600_200", jet_eta, jet_pt, "TTTo2L2Nu");
    std::cout << "eff: " << eff << std::endl;
    
}