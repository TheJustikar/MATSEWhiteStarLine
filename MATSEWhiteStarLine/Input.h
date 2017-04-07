//
//  Input.h
//  MATSEWhiteStarLine
//
//  Created by Sören Schmaljohann on 04.04.17.
//  Copyright © 2017 Sören Schmaljohann. All rights reserved.
//

#ifndef Input_h
#define Input_h

#include <string>
#include <vector>

#include "CurrentField.h"
#include "Segment.h"
#include "Vector2D.h"

namespace Input {
    
    using namespace std;
    
    class InputData
    {
        
    private:
        string* description;
        bool error;
        void onError(const int& line, const string& error);
        bool read(const string& filePath);
        
    public:
        vector<Dataholder::CurrentField>* fields;
        Dataholder::Segment* route;
        Dataholder::CurrentField* field;
        
        const bool& isError() const { return error; };
        
        InputData(const string& filePath = "") : fields(nullptr), route(nullptr), field(nullptr), description(nullptr), error(false) { read(filePath); };
        
        string resultString() const;
    };
    
    vector<InputData*>* readInputDir();
}

#endif /* Input_h */
