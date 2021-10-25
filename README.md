# btageffanalyzer

btageffanalyzer is a C++ header-only library for parsing b-tagging efficiency maps computed with [BTaggingEffAnalyzer](https://github.com/gabrielmscampos/BTaggingEffAnalyzer).

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

    // Inputs
    float jet_eta = 1.3;
    float jet_pt = 1500.0;;
    // std::string filePath = "data/btageffmap-2016postVFP.json";
    // std::string filePath = "data/btageffmap-2017.json";
    std::string filePath = "data/btageffmap-2018.json";

    // BTagEffAnalyzer
    BTagEffAnalyzer effAnalyzer;
    effAnalyzer.readFile(filePath);

    // Eval
    double eff = effAnalyzer.getEfficiency("TTTo2L2Nu", jet_eta, jet_pt, "TTTo2L2Nu");
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
Execution time btageffanalyzer: 5013.64 ms
```

# TODO

- [x] Add hadron flavour check
- [x] Update efficiency sample files with hadron falvour schema
- [x] Add fallback to missing datasets
- [ ] Change warning log for a better logging object instead of std::cout