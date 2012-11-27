//
//  Operation.cpp
//  cheetah-assembler
//
//  Copyright (c) 2012 cafaxo. All rights reserved.
//
//

#include "Operation.h"

Operation::Operation(const std::string &unparsedOperation) {
    mUnparsedOperation = unparsedOperation;
    mOperation  = 0xFF;
    mOperandCount = -1;
}

void Operation::parse() {
    auto iterator = mOpcodes.find(mUnparsedOperation);
    
    if (iterator != mOpcodes.end()) {
        mOperation = iterator->second;
        mOperandCount = 2;
    } else {
        iterator = mSpecialOpcodes.find(mUnparsedOperation);
        
        if (iterator != mOpcodes.end()) {
            mOperation = iterator->second;
            mOperandCount = 1;
        } else {
            throw std::string("Unknown operation \"" + mUnparsedOperation + "\" found.");
        }
    }
}

std::map<std::string, uint8_t> Operation::mOpcodes = {
    std::make_pair("set", 0x01),
    std::make_pair("add", 0x02),
    std::make_pair("sub", 0x03),
    std::make_pair("mul", 0x04),
    std::make_pair("mli", 0x05),
    std::make_pair("div", 0x06),
    std::make_pair("dvi", 0x07),
    std::make_pair("mod", 0x08),
    std::make_pair("mdi", 0x09),
    std::make_pair("and", 0x0a),
    std::make_pair("bor", 0x0b),
    std::make_pair("xor", 0x0c),
    std::make_pair("shr", 0x0d),
    std::make_pair("asr", 0x0e),
    std::make_pair("shl", 0x0f),
    std::make_pair("ifb", 0x10),
    std::make_pair("ifc", 0x11),
    std::make_pair("ife", 0x12),
    std::make_pair("ifn", 0x13),
    std::make_pair("ifg", 0x14),
    std::make_pair("ifa", 0x15),
    std::make_pair("ifl", 0x16),
    std::make_pair("ifu", 0x17),
    std::make_pair("adx", 0x1a),
    std::make_pair("sbx", 0x1b),
    std::make_pair("sti", 0x1e),
    std::make_pair("std", 0x1f),
};

std::map<std::string, uint8_t> Operation::mSpecialOpcodes = {
    std::make_pair("jsr", 0x01),
    std::make_pair("int", 0x08),
    std::make_pair("iag", 0x09),
    std::make_pair("ias", 0x0a),
    std::make_pair("rfi", 0x0b),
    std::make_pair("iaq", 0x0c),
    std::make_pair("hwn", 0x10),
    std::make_pair("hwq", 0x11),
    std::make_pair("hwi", 0x12),
};
