//
//  Segment.cpp
//  MATSEWhiteStarLine
//
//  Created by WetterOnline GmbH on 04.04.17.
//  Copyright © 2017 Sören Schmaljohann. All rights reserved.
//

#include "Segment.h"

using namespace Dataholder;

bool Segment::contains(const Vector2D &vector)
{
    double multiplyer = (vector.getX() - start.getX()) / direction.getX();
    
    return multiplyer <= 1 && multiplyer >= 0 && vector.getY() == (start.getY() + (direction.getY() * multiplyer));
}

Vector2D* Segment::intersectionWith(const Dataholder::Segment &segment)
{
    double multiplyer1 = (segment.start.getX() - start.getX()) / direction.getX();
    multiplyer1 += segment.direction.getX() * ((start.getY() - segment.start.getY()) / (direction.getX() * segment.direction.getY()));
    multiplyer1 *=
    
    return nullptr;
}
