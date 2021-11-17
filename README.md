# btageffanalyzer

btageffanalyzer is a C++ header-only library for parsing b-tagging efficiency maps computed with [btaggingEffMaps](https://github.com/gabrielmscampos/btaggingEffMaps).

# Dependencies

* CMake >= 3
* C++ >= 11

# Example Usage

Here is a simple example for getting b-tagging effciency for a given `eta`, `pt` and `datasetName` value. Refer to [data](data/) for efficiency maps examples.

[main.cc](examples/main.cc) content:
```cpp
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
    std::string _datasetName = "TTTo2L2Nu";
    std::string _fallbackDataset = "TTTo2L2Nu";

    // Class calibration
    effAnalyzer.calib(_datasetName, _fallbackDataset);

    // Eval
    double eff = effAnalyzer.getEfficiency(hadronFlavour, jet_eta, jet_pt);
    std::cout << "eff: " << eff << std::endl;
    
}
```

# Installation

Simply copy [src/btageffanalyzer.h](src/btageffanalyzer.h) and [include/rapidjson](include/rapidjson) to your project/include directory and include it.

# Validation

This repository ships a performance test script [performance.cc](tests/performance.cc) execution time.

[performance.cc](tests/performance.cc) result:
```
eta going from -3 to 3
pt going from 0 to 4999.93
total jets evaluated: 3048475
Execution time btageffanalyzer: 5390.1 ms
```

# TODO

- [x] Add hadron flavour check
- [x] Update efficiency sample files with hadron flavour
- [x] Add fallback for missing datasets
- [x] Updated class for filtering hadron flavour when calling `getEfficiency`. It is not necessary anymore to instanciate three objects for each flavour.
- [ ] Change warning log for a better logging object instead of std::cout