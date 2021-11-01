#include <iostream>
#include "btageffanalyzer.h"

int main() {

    // Setup analyzer
    std::string filePath = "data/btageffmap-DeepJet-loose-2017.json";
    BTagEffAnalyzer effAnalyzer;
    effAnalyzer.readFile(filePath);

    // Event loop
    float jet_eta = 1.3;
    float jet_pt = 1500.0;;
    std::string hadronFlavour = "b";
    std::string datasetName = "TTBar_test";
    std::string fallbackDataset = "TTTo2L2Nu";

    // Eval
    double eff = effAnalyzer.getEfficiency(datasetName, hadronFlavour, jet_eta, jet_pt, fallbackDataset);
    std::cout << "eff: " << eff << std::endl;
    
}