//
//  Vector2D.cpp
//  MATSEWhiteStarLine
//
//  Created by Sören Schmaljohann on 05.04.17.
//  Copyright © 2017 Sören Schmaljohann. All rights reserved.
//

#include "Vector2D.h"

namespace Dataholder
{
    Vector2D Vector2D::nearestOf(const vector<Vector2D>& vectors) const
    {
        if (vectors.size() == 0)
        {
            return *this;
        }
        
        const Vector2D* min = &vectors[0];
        
        for (Vector2D current: vectors)
        {
            if ((*min - *this)._length > (current - *this)._length)
            {
                min = &current;
            }
        }
        
        return *min;
    }
}
