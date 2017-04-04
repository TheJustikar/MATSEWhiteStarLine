//
//  CurrentField.cpp
//  MATSEWhiteStarLine
//
//  Created by WetterOnline GmbH on 04.04.17.
//  Copyright © 2017 Sören Schmaljohann. All rights reserved.
//

#include "CurrentField.h"

using namespace Dataholder;

bool CurrentField::contains(const Vector2D &vector) const
{
    bool xIsInside = (vector.x() >= _origin.x() && vector.x() <= _end.x()) || (vector.x() <= _origin.x() && vector.x() >= _end.x());
    bool yIsInside = (vector.y() >= _origin.y() && vector.y() <= _end.y()) || (vector.y() <= _origin.y() && vector.y() >= _end.y());
    
    return xIsInside && yIsInside;
}

bool CurrentField::contains(const Segment &segment) const
{
    return contains(segment.start()) && contains(segment.end());
}

bool CurrentField::contains(const CurrentField &field) const
{
    return contains(field._origin) && contains(field._end);
}

std::vector< Vector2D > CurrentField::intersectionsWith(const Dataholder::Segment &segment) const
{
    bool containsStart = contains(segment.start());
    bool containsEnd = contains(segment.end());
    
    if (containsStart && containsEnd)
    {
        return std::vector<Vector2D>(0);
    }
    
    Segment border[4] = {
                            Segment(_origin,    Vector2D(_origin.x(),   _end.y())),
                            Segment(_origin,    Vector2D(_end.x(),      _origin.y())),
                            Segment(_end,       Vector2D(_end.x(),      _origin.y())),
                            Segment(_end,       Vector2D(_origin.x(),   _end.y()))
                        };
    
    std::vector<Vector2D> ret(0);
    
    for (Segment current: border) {
        const Vector2D* intersection = current.intersectionWith(segment);
        if (intersection != nullptr) {
            ret.push_back(*intersection);
        }
    }
    
    if (ret.size() <= 2)
    {
        return ret;
    }
    return std::vector<Vector2D>(0);
}
