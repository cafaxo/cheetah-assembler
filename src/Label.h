//
//  Label.h
//  cheetah-assembler
//
//  Copyright (c) 2012 cafaxo. All rights reserved.
//

#ifndef cheetah_Label_h
#define cheetah_Label_h

#include <string>
#include <vector>

class Label {
public:
    Label(const std::string &name);
    
    void addUsageLocation(const int &usageLocation) { mUsageLocations.push_back(usageLocation); }
    
    void setPosition(uint16_t position) { *mPosition = position; }
    
    void setDefined(const bool &defined) { mDefined = defined; }
    
    const std::string &getName() const { return mName; }
    
    const std::vector<int> &getUsageLocations() const { return mUsageLocations; }
    
    uint16_t *getPosition() { return mPosition; }
    
    const bool &getDefined() { return mDefined; }
    
private:
    std::string mName;
    
    std::vector<int> mUsageLocations;
    
    uint16_t *mPosition;
    
    bool mDefined;
};

#endif
