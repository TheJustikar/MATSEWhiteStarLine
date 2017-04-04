//
//  CurrentField.cpp
//  MATSEWhiteStarLine
//
//  Created by WetterOnline GmbH on 04.04.17.
//  Copyright © 2017 Sören Schmaljohann. All rights reserved.
//

#include "CurrentField.h"

using namespace Dataholder;

bool CurrentField::contains(const Vector2D &vector)
{
    bool xIsInside = (vector.x() >= _origin.x() && vector.x() <= _end.x()) || (vector.x() <= _origin.x() && vector.x() >= _end.x());
    bool yIsInside = (vector.y() >= _origin.y() && vector.y() <= _end.y()) || (vector.y() <= _origin.y() && vector.y() >= _end.y());
    
    return xIsInside && yIsInside;
}

std::vector< Vector2D > CurrentField::intersectionsWith(const Dataholder::Segment &segment)
{
    bool containsStart = contains(segment.start());
    bool containsEnd = contains(segment.end());
    
    if (containsStart && containsEnd)
    {
        return std::vector<Vector2D>(0);
    }
    
    
    return std::vector<Vector2D>();
}
