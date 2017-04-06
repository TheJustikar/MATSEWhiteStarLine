//
//  Output.cpp
//  MATSEWhiteStarLine
//
//  Created by WetterOnline GmbH on 05.04.17.
//  Copyright © 2017 Sören Schmaljohann. All rights reserved.
//

#include <fstream>
#include <iostream>

#include "Output.h"

namespace Output
{
    void writeResult(vector<pair<Input::InputData, vector<Dataholder::RoutePart>>> results)
    {
        string result("");
        
        for (pair<Input::InputData, vector<Dataholder::RoutePart>> currentPair: results)
        {
            result += "\n\n---------------------------------------------------------------------------------------\n\n";
            
            result += currentPair.first.resultString();
            
            if (!currentPair.first.isError())
            {
                result += "\n\nDaten für die Planung der Route:\n\n";
                
                for (const Dataholder::RoutePart current: currentPair.second)
                {
                    result += current.resultString() + "\n";
                }
            }
            
            result += "\n\n---------------------------------------------------------------------------------------\n\n";
        }
        
        cout << result << endl;
        
        ofstream output;
        output.open("./Output/output.txt");
        if (output.is_open())
        {
            output << result;
            output.close();
        }
    }
}
