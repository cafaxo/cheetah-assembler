//
//  main.cpp
//  cheetah-assembler
//
//  Copyright (c) 2012 cafaxo. All rights reserved.
//

#include "Assembler.h"

#include <iostream>

int main(int argc, const char * argv[]) {
    Assembler assembler;
    assembler.parse("test.asm");
    assembler.write("test.bin", true);
    
    for (auto iterator : assembler.getErrors()) {
        std::cout << "On line " << iterator.first << ": " << iterator.second << std::endl;
    }
    
    return 0;
}
