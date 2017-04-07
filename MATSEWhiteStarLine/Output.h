//
//  Output.h
//  MATSEWhiteStarLine
//
//  Created by WetterOnline GmbH on 05.04.17.
//  Copyright © 2017 Sören Schmaljohann. All rights reserved.
//

#ifndef Output_h
#define Output_h

#include "Input.h"
#include "RoutePart.h"

using namespace std;

namespace Output
{
    void writeResult(vector<pair<Input::InputData, vector<Dataholder::RoutePart> > > results);
}

#endif /* Output_h */
