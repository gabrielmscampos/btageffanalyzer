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
    std::string _datasetName = "DYJetsToLL";
    std::string _fallbackDataset = "TTTo2L2Nu";
    std::string _forceDataset = "TTTo2L2Nu";

    // Class calibration
    effAnalyzer.calib(_datasetName, _fallbackDataset, _forceDataset);

    // Eval
    double eff = effAnalyzer.getEfficiency(hadronFlavour, jet_eta, jet_pt);
    std::cout << "eff: " << eff << std::endl;
    
}