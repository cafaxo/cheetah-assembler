//
//  LabelMap.h
//  cheetah-assembler
//
//  Copyright (c) 2012 cafaxo. All rights reserved.
//

#ifndef cheetah_LabelMap_h
#define cheetah_LabelMap_h

#include "Label.h"

#include <iostream>
#include <vector>

class LabelMap {
public:
    uint16_t *get(std::string labelName, const bool &local, const int &lineNumber);
    
    void connect(std::string labelName, const uint16_t &value, const bool &local);
    
    const std::vector<Label> &getLabels() { return mLabels; }
    
private:
    std::vector<Label> mLabels;
    
    std::string mContextLabelName;
};

#endif
