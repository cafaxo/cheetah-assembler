//
//  Instruction.h
//  cheetah-assembler
//
//  Copyright (c) 2012 cafaxo. All rights reserved.
//

#ifndef cheetah_Instruction_h
#define cheetah_Instruction_h

#include "Operation.h"
#include "Operand.h"

#include <string>
#include <vector>

class LabelMap;

class Instruction {
public:
    Instruction(const std::string &unparsedInstruction, LabelMap &labelMap, const int &lineNumber);
    
    void parse();
    
    const std::vector<uint16_t *> &getData() const { return mData; }
    
private:
    std::string mUnparsedInstruction;
    
    LabelMap &mLabelMap;
    
    int mLineNumber;

    std::vector<uint16_t *> mData;
};

#endif
