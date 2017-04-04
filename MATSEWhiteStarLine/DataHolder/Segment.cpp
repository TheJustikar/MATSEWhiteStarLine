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
    double multiplyer = (vector.x() - _start.x()) / _direction.x();
    
    return multiplyer <= 1 && multiplyer >= 0 && vector.y() == (_start.y() + (_direction.y() * multiplyer));
}

Vector2D* Segment::intersectionWith(const Dataholder::Segment &segment)
{
    double multiplyer = (segment._start.x() - _start.x()) / _direction.x();
    multiplyer += segment._direction.x() * ((_start.y() - segment._start.y()) / (_direction.x() * segment._direction.y()));
    multiplyer *= _direction.x() * segment._direction.y();
    multiplyer /= (_direction.x() * segment._direction.y()) - _direction.y();
    
    Vector2D* intersection = new Vector2D(_start.x() + _direction.x() * multiplyer, _start.y() + _direction.y() * multiplyer);
    
    return nullptr;
}
