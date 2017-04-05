//
//  Output.cpp
//  MATSEWhiteStarLine
//
//  Created by WetterOnline GmbH on 05.04.17.
//  Copyright © 2017 Sören Schmaljohann. All rights reserved.
//

#include <fstream>

#include "Output.h"

namespace Output
{
    void writeResult(const vector< const pair< const Input::InputData&, const vector< const Dataholder::RoutePart >& > >& results)
    {
        string result("");
        
        for (pair< const Input::InputData&, const vector<const Dataholder::RoutePart >& > currentPair: results)
        {
            result += "\n\n---------------------------------------------------------------------------------------\n\n";
            
            result += currentPair.first.resultString();
            
            result += "\n\nDaten für die Planung der Route:\n\n";
            
            for (Dataholder::RoutePart current: currentPair.second)
            {
                result += current.resultString() + "\n";
            }
            
            result += "\n\n---------------------------------------------------------------------------------------\n\n";
        }
        
        ofstream output;
        output.open("./Output/output.txt");
        if (output.is_open())
        {
            output << result;
            output.close();
        }
    }
}
