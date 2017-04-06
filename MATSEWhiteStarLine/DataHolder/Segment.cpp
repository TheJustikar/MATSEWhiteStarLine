//
//  Segment.cpp
//  MATSEWhiteStarLine
//
//  Created by WetterOnline GmbH on 04.04.17.
//  Copyright © 2017 Sören Schmaljohann. All rights reserved.
//

#include "Segment.h"

namespace Dataholder
{
    bool Segment::contains(const Vector2D &vector) const
    {
        if (_direction.x() != 0)
        {
            double multiplyer = (vector.x() - _start.x()) / _direction.x();
            
            if (_start.x() < _end.x())
            {
                return multiplyer <= 1 && multiplyer >= 0 && vector.y() == (_start.y() + (_direction.y() * multiplyer));
            }
            else
            {
                return multiplyer >= -1 && multiplyer <= 0 && vector.y() == (_start.y() + (_direction.y() * multiplyer));
            }
        }
        else
        {
            // Use y-direction, if x-dircetion is zero
            double multiplyer = (vector.y() - _start.y()) / _direction.y();
            
            if (_start.y() < _end.y())
            {
                return multiplyer <= 1 && multiplyer >= 0 && vector.x() == (_start.x() + (_direction.x() * multiplyer));
            }
            else
            {
                return multiplyer >= -1 && multiplyer <= 0 && vector.x() == (_start.x() + (_direction.x() * multiplyer));
            }
        }
    }
    
    const Vector2D* Segment::intersectionWith(const Dataholder::Segment &segment)
    {
        if (isParallell(segment) || contains(segment._start) || contains(segment._end))
        {
            return nullptr;
        }
        
        //Cramer's rule
        double x1 = _start.x(), x2 = _end.x(), x3 = segment._start.x(), x4 = segment._end.x();
        double y1 = _start.y(), y2 = _end.y(), y3 = segment._start.y(), y4 = segment._end.y();
        
        double denominator = ((y4 - y3) * (x2 - x1)) - ((y2 - y1) * (x4 - x3));
        
        if (denominator == 0)
        {
            return nullptr;
        }
        
        double x = ((x4 - x3) * ((x2 * y1) - (x1 * y2))) - ((x2 - x1) * ((x4 * y3) - (x3 * y4)));
        x /= denominator;
        double y = ((y1 - y2) * ((x4 * y3) - (x3 * y4))) - ((y3 - y4) * ((x2 * y1) - (x1 * y2)));
        y /= denominator;
        
        Vector2D* intersection = new Vector2D(x, y);
        // Check if intersection is on segment
        if (contains(*intersection) && segment.contains(*intersection))
        {
            return intersection;
        }
        
        return nullptr;
    }
}
