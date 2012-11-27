//
//  Instruction.cpp
//  cheetah-assembler
//
//  Copyright (c) 2012 cafaxo. All rights reserved.
//

#include "Instruction.h"

Instruction::Instruction(const std::string &unparsedInstruction, LabelMap &labelMap, const int &lineNumber) : mLabelMap(labelMap) {
    mUnparsedInstruction = unparsedInstruction;
    mLineNumber = lineNumber;
}

void Instruction::parse() {
    const std::string unparsedOperation = mUnparsedInstruction.substr(0, 3);
    
    Operation operation(unparsedOperation);
    operation.parse();
    
    std::stringstream unparsedOperands(mUnparsedInstruction.substr(3, mUnparsedInstruction.size() - 3));
    std::string unparsedOperand;
    std::vector<Operand *> parsedOperands;
    
    while (std::getline(unparsedOperands, unparsedOperand, ',')) {
        Operand *operand = new Operand(unparsedOperand, mLabelMap, mLineNumber);
        operand->parse();
        parsedOperands.push_back(operand);
    }
    
    if (operation.getOperandCount() != parsedOperands.size()) {
        throw std::string("Expected " + std::to_string(operation.getOperandCount()) + " operand(s), but got " + std::to_string(parsedOperands.size()) + ".");
    }
    
    if (operation.getOperandCount() == 1) {
        const uint8_t a = parsedOperands[0]->getOperand();
        
        mData.push_back(new uint16_t(((operation.getOperation() & 0x1f) << 5) | ((a & 0x3f) << 10)));
    } else if (operation.getOperandCount() == 2) {
        const uint8_t a = parsedOperands[1]->getOperand();
        const uint8_t b = parsedOperands[0]->getOperand();
        
        mData.push_back(new uint16_t((operation.getOperation() & 0x1f) | ((b & 0x1f) << 5) | ((a & 0x3f) << 10)));
    }
    
    for (Operand *parsedOperand : parsedOperands) {
        if (parsedOperand->getOperand() == 0x1f || parsedOperand->getOperand() == 0x1e) {
            mData.push_back(parsedOperand->getTrailingData());
        }
    }
}
