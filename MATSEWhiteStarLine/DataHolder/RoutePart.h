//
//  RoutePart.h
//  MATSEWhiteStarLine
//
//  Created by WetterOnline GmbH on 04.04.17.
//  Copyright © 2017 Sören Schmaljohann. All rights reserved.
//

#ifndef RoutePart_h
#define RoutePart_h

#include <string>

#include "Vector2D.h"
#include "Segment.h"
#include "CurrentField.h"

namespace Dataholder
{
    class RoutePart
    {
    public:
        const Segment route;
        const Vector2D skv;
        const double distance, speed, time;
        
        //Constructor
        RoutePart(const Segment route, Vector2D skv) : route(route), skv(skv), distance((route.end() - route.start()).length()), speed(skv.length()), time(distance / speed) {};
        
        string resultString() const;
    };
}

#endif /* RoutePart_h */
