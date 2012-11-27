//
//  Label.cpp
//  cheetah-assembler
//
//  Copyright (c) 2012 cafaxo. All rights reserved.
//

#include "Label.h"

Label::Label(const std::string &name) {
    mName = name;
    mPosition = new uint16_t(0);
    mDefined = false;
}

Label::~Label() {
    delete mPosition;
}
