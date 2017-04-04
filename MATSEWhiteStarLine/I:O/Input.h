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

vector<CurrentField>* fields = nullptr;
Segment* way = nullptr;
CurrentField* field = nullptr;
string* description = nullptr;

bool read(string filePath);

#endif /* Input_h */
