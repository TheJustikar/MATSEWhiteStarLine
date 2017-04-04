//
//  RoutePart.h
//  MATSEWhiteStarLine
//
//  Created by WetterOnline GmbH on 04.04.17.
//  Copyright © 2017 Sören Schmaljohann. All rights reserved.
//

#ifndef RoutePart_h
#define RoutePart_h

#include "Vector2D.h"
#include "Segment.h"
#include "CurrentField.h"

namespace Dataholder
{
    class RoutePart
    {
    public:
        const Vector2D start, end, skv;
        const double distance, speed, time;
        
        //Constructor
        RoutePart(const Segment segment, Vector2D skv) : start(segment.start()), end(segment.end()), skv(skv), distance((end - start).length()), speed(skv.length()), time(distance / speed) {};
    };
}

#endif /* RoutePart_h */
