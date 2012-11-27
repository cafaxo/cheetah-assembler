//
//  Operand.h
//  cheetah-assembler
//
//  Copyright (c) 2012 cafaxo. All rights reserved.
//

#ifndef cheetah_Operand_h
#define cheetah_Operand_h

#include <string>
#include <map>
#include <sstream>

class LabelMap;

class Operand {
public:
    Operand(const std::string &unparsedOperand, LabelMap &labelMap, const int &lineNumber);
    
    ~Operand();
    
    void parse();
    
    const uint8_t &getOperand() const { return mOperand; }
    uint16_t *getTrailingData() const { return mTrailingData; }
    
private:
    bool parseNumber(const std::string &unparsedOperand, uint16_t &number) const;
    
    std::string mUnparsedOperand;
    
    LabelMap &mLabelMap;
    
    int mLineNumber;
    
    uint8_t mOperand;
    
    uint16_t *mTrailingData;
    
    static std::map<std::string, uint8_t> mSpecialValues;
};

#endif
