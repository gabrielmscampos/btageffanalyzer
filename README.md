# btageffanalyzer

btageffanalyzer is a C++ header-only library for parsing b-tagging efficiency maps computed with [BTaggingEffAnalyzer](https://github.com/gabrielmscampos/BTaggingEffAnalyzer).

# Dependencies

* CMake >= 3
* C++ >= 11

# Example Usage

Here is a simple example for getting b-tagging effciency for a given `eta`, `pt` and `datasetName` value.

[btageffmap-2016postVFP.json](data/btageffmap-2016postVFP.json) head:
```
{"Signal_800_200": [{"eta_min": 0.0, "eta_max": 0.6, "pt_min": 20.0, "pt_max": 30.0, "eff": 0.433295456090487}, {"eta_min": 0.6, "eta_max": 1.2, "pt_min": 20.0, "pt_max": 30.0, "eff": 0.46964317999893784}, {"eta_min": 1.2, "eta_max": 2.5, "pt_min": 20.0, "pt_max": 30.0, "eff": 0.5722244373026955}, {"eta_min": 0.0, "eta_max": 0.6, "pt_min": 30.0, "pt_max": 45.0, "eff": 0.44112388514263945}, {"eta_min": 0.6, "eta_max": 1.2, "pt_min": 30.0, "pt_max": 45.0, "eff": 0.47972418428427305}, {"eta_min": 1.2, "eta_max": 2.5, "pt_min": 30.0, "pt_max": 45.0, "eff": 0.5467838925161108}, {"eta_min": 0.0, "eta_max": 0.6, "pt_min": 45.0, "pt_max": 65.0, "eff": 0.4694192736013139}, {"eta_min": 0.6, "eta_max": 1.2, "pt_min": 45.0, "pt_max": 65.0, "eff": 0.4840473080818207}, {"eta_min": 1.2, "eta_max": 2.5, "pt_min": 45.0, "pt_max": 65.0, "eff": 0.5442698495409704}, {"eta_min": 0.0, "eta_max": 0.6, "pt_min": 65.0, "pt_max": 95.0, "eff": 0.5091626744354952}, {"eta_min": 0.6, "eta_max": 1.2, "pt_min": 65.0, "pt_max": 95.0, "eff": 0.5207359187236046}, {"eta_min": 1.2, "eta_max": 2.5, "pt_min": 65.0, "pt_max": 95.0, "eff": 0.5337840684601137}, {"eta_min": 0.0, "eta_max": 0.6, "pt_min": 95.0, "pt_max": 150.0, "eff": 0.5605520897876368}, {"eta_min": 0.6, "eta_max": 1.2, "pt_min": 95.0, "pt_max": 150.0, "eff": 0.5399186489252115}, {"eta_min": 1.2, "eta_max": 2.5, "pt_min": 95.0, "pt_max": 150.0, "eff": 0.5307771954593483}, {"eta_min": 0.0, "eta_max": 0.6, "pt_min": 150.0, "pt_max": 1500.0, "eff": 0.6587289939394163}, {"eta_min": 0.6, "eta_max": 1.2, "pt_min": 150.0, "pt_max": 1500.0, "eff": 0.6372306528595777}, {"eta_min": 1.2, "eta_max": 2.5, "pt_min": 150.0, "pt_max": 1500.0, "eff": 0.5601023234034963}]
```

[main.cc](examples/main.cc) content:
```cpp
#include <iostream>
#include "btageffanalyzer.h"

int main(int argc, char *argv[]) {

    // Inputs
    float jet_eta = 1.3;
    float jet_pt = 234.32;;

    // BTagEffAnalyzer
    BTagEffAnalyzer effAnalyzer;
    effAnalyzer.readFile(
        "data/btageffmap-2016postVFP.json"
    );

    // Eval
    double eff = effAnalyzer.getEfficiency("DY", jet_eta, jet_pt);
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