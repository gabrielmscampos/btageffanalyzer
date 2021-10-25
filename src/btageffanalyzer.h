/*
 * btageffanalyzer.h
 *
 * URL:      https://github.com/gabrielmscampos/btageffanalyzer
 * Version:  2.1.0
 *
 * Copyright (C) 2021-2021 Gabriel Moreira da Silva Campos <gabrielmscampos@gmail.com>
 *
 * btageffanalyzer is distributed under the GPL-3.0 license, see LICENSE for details.
 *
 */

#include <iostream>
#include <vector>
#include <map>
#include <math.h>

#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"

class BTagEffAnalyzer {

    private:
        struct data {
            float etaMin;
            float etaMax;
            float ptMin;
            float ptMax;
            double eff;
        };
        
        struct bounds {
            float etaMin;
            float etaMax;
            float ptMin;
            float ptMax;
        };

        double evalEfficiency(
            std::string datasetName,
            float eta,
            float pt
        ) {
            const auto &entries = dataMap.at(datasetName);
            for (const auto &e: entries) {
                if (
                    eta >= e.etaMin &&
                    eta <= e.etaMax &&
                    pt >= e.ptMin &&
                    pt < e.ptMax
                ) {
                    return e.eff;
                }
            }
            return 0.;
        }

    public:
        std::map<std::string, std::vector<data>> dataMap;
        std::map<std::string, bounds> boundsMap;

        void readFile(
            std::string fpath,
            std::string hadronFlavour
        ){
            rapidjson::Document effFileMap;
            FILE *fp_cert = fopen(fpath.c_str(), "r"); 
            char buf_cert[0XFFFF];
            rapidjson::FileReadStream input_cert(fp_cert, buf_cert, sizeof(buf_cert));
            effFileMap.ParseStream(input_cert);

            for (auto i = effFileMap.MemberBegin(); i != effFileMap.MemberEnd(); i++) {
                std::string dt = i->name.GetString();
                rapidjson::Value& dtValues = effFileMap[dt.c_str()];
                rapidjson::Value& dtHfValues = dtValues[hadronFlavour.c_str()];
                float minEtaBound = 0.; float maxEtaBound = 0.;
                float minPtBound = -1.; float maxPtBound = -1.;
                for (int j = 0; j < dtHfValues.Size(); j++) {
                    data te;
                    te.etaMin = dtHfValues[j]["eta_min"].GetFloat();
                    te.etaMax = dtHfValues[j]["eta_max"].GetFloat();
                    te.ptMin = dtHfValues[j]["pt_min"].GetFloat();
                    te.ptMax = dtHfValues[j]["pt_max"].GetFloat();
                    te.eff = dtHfValues[j]["eff"].GetDouble();
                    dataMap[dt].push_back(te);
                    minEtaBound = minEtaBound < te.etaMin ? minEtaBound : te.etaMin;
                    maxEtaBound = maxEtaBound > te.etaMax ? maxEtaBound : te.etaMax;
                    minPtBound = minPtBound < te.ptMin ? minPtBound : te.ptMin;
                    maxPtBound = maxPtBound > te.ptMax ? maxPtBound : te.ptMax;
                    if (minPtBound < 0.) {
                        minPtBound = te.ptMin;
                        maxPtBound = te.ptMax;
                    }
                }
                bounds tb;
                tb.etaMin = minEtaBound;
                tb.etaMax = maxEtaBound;
                tb.ptMin = minPtBound;
                tb.ptMax = maxPtBound;
                boundsMap[dt] = tb;
            }

            fclose(fp_cert);
        }

        double getEfficiency(
            std::string datasetName,
            float eta,
            float pt,
            std::string defaultDataset
        ) {
            // Absolute value of eta
            eta = fabs(eta);

            // Check if key 'hat' exists in the map
            if (dataMap.count(datasetName) < 1) {
                std::cout << "WARNING: Missing dataset " + datasetName + " in efficiency file. Defaulting to " + defaultDataset + "." << std::endl;
                datasetName = defaultDataset;
            }

            // If eta is out of bounds, return 0
            if (
                eta < boundsMap.at(datasetName).etaMin ||
                eta > boundsMap.at(datasetName).etaMax
            ) return 0;

            // If pt is out of bounds, define pt to evaluate next to bound
            float ptToEvaluate = pt;
            bool ptOutOfBounds = false;

            // If pt is lesser than minimum bound, return 0
            if (pt < boundsMap.at(datasetName).ptMin) return 0;

            // When given pT is greater then maximum boundary we compute
            // the efficiency at the maximum boundary
            if (pt >= boundsMap.at(datasetName).ptMax) {
                ptOutOfBounds = true;
                ptToEvaluate = boundsMap.at(datasetName).ptMax - .0001;
            }

            return evalEfficiency(datasetName, eta, ptToEvaluate);
        }
};