//
//  Operation.h
//  cheetah-assembler
//
//  Copyright (c) 2012 cafaxo. All rights reserved.
//

#ifndef cheetah_Operation_h
#define cheetah_Operation_h

#include <string>
#include <map>

class Operation {
public:
    Operation(const std::string &unparsedOperation);
    
    void parse();
    
    const uint8_t &getOperation() { return mOperation; }
    
    const unsigned char &getOperandCount() { return mOperandCount; }
    
private:
    std::string mUnparsedOperation;
    
    uint8_t mOperation;
    
    unsigned char mOperandCount;
    
    static std::map<std::string, uint8_t> mOpcodes;
    
    static std::map<std::string, uint8_t> mSpecialOpcodes;
};

#endif
