//
//  Operand.cpp
//  cheetah-assembler
//
//  Copyright (c) 2012 cafaxo. All rights reserved.
//

#include "LabelMap.h"
#include "Operand.h"

Operand::Operand(const std::string &unparsedOperand, LabelMap &labelMap, const int &lineNumber) : mLabelMap(labelMap) {
    mUnparsedOperand = unparsedOperand;
    mLineNumber = lineNumber;
    mOperand = 0xFF;
	mTrailingData = NULL;
}

Operand::~Operand() {
    delete mTrailingData;
}

void Operand::parse() {
    uint16_t tmpNumber = 0;
    std::map<std::string, uint8_t>::iterator tmpIterator;
    
    if (parseNumber(mUnparsedOperand, tmpNumber)) {
        if (tmpNumber < 0x1f) {
            mOperand = tmpNumber + 0x21;
        } else {
            mTrailingData = new uint16_t(tmpNumber);
            mOperand = 0x1f;
        }
    } else if (mUnparsedOperand.at(0) == '[') {
        size_t split;
        
        if ((split = mUnparsedOperand.find('+')) == std::string::npos) {
            const std::string part = mUnparsedOperand.substr(1, mUnparsedOperand.length() - 2);
            if (parseNumber(part, tmpNumber)) {
                mOperand = 0x1e;
                mTrailingData = new uint16_t(tmpNumber);
            } else if ((tmpIterator = mSpecialValues.find(part)) != mSpecialValues.end()) {
                mOperand = tmpIterator->second + 0x08;
            }
        } else {
            const std::string firstPart = mUnparsedOperand.substr(1, split - 1);
            const std::string secondPart = mUnparsedOperand.substr(split + 1, mUnparsedOperand.size() - split - 2);
            
            if ((parseNumber(firstPart, tmpNumber) && (tmpIterator = mSpecialValues.find(secondPart)) != mSpecialValues.end()) ||
                (parseNumber(secondPart, tmpNumber) && (tmpIterator = mSpecialValues.find(firstPart)) != mSpecialValues.end())) {
                mOperand = tmpIterator->second + 0x10;
                mTrailingData = new uint16_t(tmpNumber);
            }
        }
    } else if ((tmpIterator = mSpecialValues.find(mUnparsedOperand)) != mSpecialValues.end()) {
        mOperand = tmpIterator->second;
    } else if (std::find_if(mUnparsedOperand.begin(), mUnparsedOperand.end(), [](char c) { return !(isalnum(c) || (c == '_') || (c == '.')); }) == mUnparsedOperand.end()) {
        mTrailingData = mLabelMap.get(mUnparsedOperand, mUnparsedOperand.at(0) == '.', mLineNumber);
        mOperand = 0x1f;
    } else {
        throw std::string("Unknown operand \"" + mUnparsedOperand +"\" found.");
    }
}

bool Operand::parseNumber(const std::string &unparsedOperand, uint16_t &number) const {
    if (std::find_if(unparsedOperand.begin(), unparsedOperand.end(), [](char c) { return !std::isdigit(c); }) == unparsedOperand.end()) {
        std::stringstream stringStream;
        stringStream << unparsedOperand;
        stringStream >> number;
        return true;
    } else if (unparsedOperand.substr(0, 2) == "0x") {
        std::stringstream stringStream;
        stringStream << std::hex << unparsedOperand.substr(2, unparsedOperand.length() - 2);
        stringStream >> number;
        return true;
    }
    
    return false;
}

std::map<std::string, uint8_t> Operand::mSpecialValues = {
    std::make_pair("a", 0x00),
    std::make_pair("b", 0x01),
    std::make_pair("c", 0x02),
    std::make_pair("x", 0x03),
    std::make_pair("y", 0x04),
    std::make_pair("z", 0x05),
    std::make_pair("i", 0x06),
    std::make_pair("j", 0x07),
    std::make_pair("push", 0x18),
    std::make_pair("pop", 0x18),
    std::make_pair("peek", 0x19),
    std::make_pair("pick", 0x1a),
    std::make_pair("sp", 0x1b),
    std::make_pair("pc", 0x1c),
    std::make_pair("ex", 0x1d),
};
