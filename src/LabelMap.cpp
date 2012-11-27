//
//  LabelMap.cpp
//  cheetah-assembler
//
//  Copyright (c) 2012 cafaxo. All rights reserved.
//

#include "LabelMap.h"

uint16_t *LabelMap::get(std::string labelName, const bool &local, const int &lineNumber) {
    if (local) {
        if (mContextLabelName.empty()) {
            throw std::string("Called local label without context.");
        }
        
        labelName = mContextLabelName + labelName;
    }
    
    auto iterator = std::find_if(mLabels.begin(), mLabels.end(), [&](const Label &label) -> bool { return label.getName() == labelName; });
    
    if (iterator == mLabels.end()) {
        Label label(labelName);
        label.addUsageLocation(lineNumber);
        mLabels.push_back(label);
        
        return mLabels.back().getPosition();
    }
    
    return iterator->getPosition();
}

void LabelMap::connect(std::string labelName, const uint16_t &value, const bool &local) {
    if (local) {
        if (mContextLabelName.empty()) {
            throw std::string("Specified local label without context.");
        }
        
        labelName = mContextLabelName + labelName;
    } else {
        mContextLabelName = labelName;
    }
    
    auto iterator = std::find_if(mLabels.begin(), mLabels.end(), [&](const Label &label) -> bool { return label.getName() == labelName; });
    
    if (iterator != mLabels.end()) {
        if (iterator->getDefined()) {
            throw std::string("Label \"" + labelName + "\" already defined.");
        } else {
            iterator->setPosition(value);
            iterator->setDefined(true);
        }
    } else {
        Label label(labelName);
        label.setPosition(value);
        label.setDefined(true);
        mLabels.push_back(label);
    }
}
