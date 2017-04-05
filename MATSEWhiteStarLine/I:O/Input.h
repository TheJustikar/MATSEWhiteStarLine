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
    
    class InputData
    {
        
    private:
        void onError(const int& line, const string& error);
        
    public:
        vector<CurrentField>* fields;
        Segment* route;
        CurrentField* field;
        string* description;
        
        InputData() : fields(nullptr), route(nullptr), field(nullptr), description(nullptr) {};
    
        bool read(const string& filePath);
    };
    
    vector<InputData> readInputDir();
}

#endif /* Input_h */
