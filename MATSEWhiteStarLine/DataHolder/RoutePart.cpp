//
//  RoutePart.cpp
//  MATSEWhiteStarLine
//
//  Created by WetterOnline GmbH on 05.04.17.
//  Copyright © 2017 Sören Schmaljohann. All rights reserved.
//

#include "RoutePart.h"

namespace Dataholder
{
    string RoutePart::resultString() const
    {
        string result("");
        
        result += "Strecke: " + route.toString() + "\n";
        result += "\tEntfernung: " + to_string(distance) + " km\n";
        result += "\tSKV: " + skv.toString() + "\n";
        result += "\tSollgeschwindigkeit: " + to_string(speed) + " km/h\n";
        result += "\tFahrzeit: " + to_string(time) + " h\n";
        
        return result;
    }
}
