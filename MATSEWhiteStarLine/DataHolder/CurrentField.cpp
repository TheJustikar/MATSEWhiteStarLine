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
    bool xIsInside = (vector.getX() >= origin.getX() && vector.getX() <= end.getX()) || (vector.getX() <= origin.getX() && vector.getX() >= end.getX());
    bool yIsInside = (vector.getY() >= origin.getY() && vector.getY() <= end.getY()) || (vector.getY() <= origin.getY() && vector.getY() >= end.getY());
    
    return xIsInside && yIsInside;
}

std::vector< Vector2D > CurrentField::intersectionsWith(const Dataholder::Segment &segment)
{
    bool containsStart = contains(segment.getStart());
    bool containsEnd = contains(segment.getEnd());
    
    if (containsStart && containsEnd)
    {
        return std::vector<Vector2D>(0);
    }
    
    
    return std::vector<Vector2D>();
}
