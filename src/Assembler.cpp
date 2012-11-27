//
//  Assembler.cpp
//  cheetah-assembler
//
//  Copyright (c) 2012 cafaxo. All rights reserved.
//

#include "Assembler.h"

Assembler::~Assembler() {
    mErrors.erase(mErrors.begin(), mErrors.end());
}

void Assembler::parse(const std::string &fileName) {
    try {
        mSourceLines = readFileLines(fileName);
    } catch (std::string description) {
        mErrors.push_back(std::make_pair(-1, std::string(description)));
    }
    
    unsigned int pcCounter = 0;
    
    for (int i = 0; i < mSourceLines.size(); ++i) {
        std::string sourceLine = mSourceLines.at(i);
        
        // strip whitespace
        sourceLine.erase(std::remove(sourceLine.begin(), sourceLine.end(), ' '), sourceLine.end());

        // strip comments
        // TODO: don't strip literals
        sourceLine.erase(std::find(sourceLine.begin(), sourceLine.end(), ';'), sourceLine.end());
        
        // make all letters lower-case
        std::transform(sourceLine.begin(), sourceLine.end(), sourceLine.begin(), ::tolower);
        
        if (!sourceLine.empty()) {
            if (sourceLine.at(0) == ':') {
                // label
                
                try {
                    mLabelMap.connect(sourceLine.substr(1, sourceLine.length() - 1), pcCounter, sourceLine.at(1) == '.');
                } catch (std::string description) {
                    mErrors.push_back(std::make_pair(i + 1, std::string(description)));
                }
            } else {
                // instruction
                
                Instruction *instruction = new Instruction(sourceLine, mLabelMap, i + 1);
                
                try {
                    instruction->parse();
                    pcCounter += instruction->getData().size();
                    mInstructions.push_back(instruction);
                } catch (std::string description) {
                    mErrors.push_back(std::make_pair(i + 1, std::string(description)));
                }
            }
        }
    }
    
    for (auto label : mLabelMap.getLabels()) {
        if (!label.getDefined()) {
            for (auto usageLocation : label.getUsageLocations()) {
                mErrors.push_back(std::make_pair(usageLocation, "Undefined label \"" + label.getName() + "\" found."));
                continue;
            }
            
            mErrors.push_back(std::make_pair(-1, "Unused label \"" + label.getName() + "\" found."));
        }
    }
}

bool Assembler::write(const std::string &fileName, bool generateDebugSymbols) {
    std::ofstream file = std::ofstream(fileName, std::ios::out | std::ios::binary);
    
    for (Instruction *instruction : mInstructions) {
        uint16_t instruction_flipped = ((((*instruction->getData()[0]) >> 8) & 0xff) | (((*instruction->getData()[0]) & 0xff) << 8));
        file.write((char *)&instruction_flipped, 2);
        
        for (int i = 1; i < instruction->getData().size(); ++i) {
            uint16_t trailingData = *instruction->getData().at(i);
            
            uint16_t trailing_data_flipped = ((((trailingData) >> 8) & 0xff) | (((trailingData) & 0xff) << 8));
            file.write((char *)&trailing_data_flipped, 2);
        }
    }
    
    file.close();
    
    // TODO: implement writing debug symbols
    
    return true;
}

std::vector<std::string> Assembler::readFileLines(const std::string &fileName) {
    std::ifstream file(fileName, std::ifstream::in);
    
    if (!file.is_open()) {
        throw std::string("Error opening file: " + fileName);
    }
    
    std::vector<std::string> lines;
    std::string line;
    
    while (std::getline(file, line, '\n')) {
        lines.push_back(line);
    }
    
    return lines;
}
