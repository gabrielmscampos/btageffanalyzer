#include <iostream>
#include <chrono>
#include "btageffanalyzer.h"

int main() {

    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;

    // Simulate event loop
    float eta = -3.0;
    float pt = 0.;
    std::vector<float> etaArray;
    std::vector<float> ptArray;
    while (eta < 3.0) {
        etaArray.push_back(eta);
        eta += 0.1;
    }
    while (pt < 5000.) {
        ptArray.push_back(pt);
        pt += 0.1;
    }
    std::cout << "eta going from " << etaArray[0] << " to " << etaArray[etaArray.size()-1] << std::endl;
    std::cout << "pt going from " << ptArray[0] << " to " << ptArray[ptArray.size()-1] << std::endl;
    std::cout << "total jets evaluated: " << etaArray.size()*ptArray.size() << std::endl;

    float jet_eta; float jet_pt;

    // Compute time to get scale factors using this lib
    auto t1 = high_resolution_clock::now();

    // BTagEffAnalyzer
    BTagEffAnalyzer effAnalyzer;
    effAnalyzer.readFile(
        "data/btageffmap-2016postVFP.json"
    );

    // "Event loop"
    for (unsigned int i = 0; i < etaArray.size(); i++) {
        jet_eta = etaArray[i];
        for (unsigned int j = 0; j < ptArray.size(); j++) {
            jet_pt = ptArray[j];
            double eff = effAnalyzer.getEfficiency("DY", jet_eta, jet_pt);
        }
    }

    auto t2 = high_resolution_clock::now();

    // Getting number of milliseconds as a double
    duration<double, std::milli> ms = t2 - t1;
    std::cout << "Execution time btageffanalyzer: " << ms.count() << " ms" << std::endl;
    
}