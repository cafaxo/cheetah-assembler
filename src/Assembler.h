//
//  Assembler.h
//  cheetah-assembler
//
//  Copyright (c) 2012 cafaxo. All rights reserved.
//

#ifndef cheetah_Assembler_h
#define cheetah_Assembler_h

#include "LabelMap.h"
#include "Instruction.h"

#include <fstream>

class Assembler {
public:
    ~Assembler();
    
    void parse(const std::string &fileName);
    
    bool write(const std::string &fileName, bool generateDebugSymbols);
    
    const std::vector<std::pair<int, std::string>> &getErrors() { return mErrors; }
    
private:
    std::vector<std::string> readFileLines(const std::string &fileName);
    
    std::vector<std::string> mSourceLines;
    
    std::vector<Instruction *> mInstructions;
    
    std::vector<std::pair<int, int>> mDebugSymbols;
    
    std::vector<std::pair<int, std::string>> mErrors;
    
    LabelMap mLabelMap;
};

#endif
