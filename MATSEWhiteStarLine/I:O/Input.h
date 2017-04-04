//
//  Input.h
//  MATSEWhiteStarLine
//
//  Created by WetterOnline GmbH on 04.04.17.
//  Copyright © 2017 Sören Schmaljohann. All rights reserved.
//

#ifndef Input_h
#define Input_h

#include <string>
#include <vector>

#include "Vector2D.h"
#include "Segment.h"
#include "CurrentField.h"

using namespace Dataholder;
using namespace std;

namespace Input {
    
    extern vector<CurrentField>* fields;
    extern Segment* route;
    extern CurrentField* field;
    extern string* description;
    
    bool read(const string& filePath);
}

#endif /* Input_h */
