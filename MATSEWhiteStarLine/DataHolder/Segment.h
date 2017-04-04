//
//  Segment.h
//  MATSEWhiteStarLine
//
//  Created by WetterOnline GmbH on 04.04.17.
//  Copyright © 2017 Sören Schmaljohann. All rights reserved.
//

#ifndef Segment_h
#define Segment_h

#include "Vector2D.h"

namespace Dataholder
{
    class Segment
    {
        
    private:
        Vector2D start, end, direction;
        double length;
        
    public:
        //Constructor
        Segment(const Vector2D start, const Vector2D end) : start(start), end(end), direction(end - start) { length = direction.getLength(); };
        
        //Setter
        void setStart(const Vector2D& start) { this->start = start; direction = end - start; length = direction.getLength(); };
        void setEnd(const Vector2D& end) { this->end = end; direction = end - start; length = direction.getLength(); };
        
        //Getter
        const Vector2D& getStart() const { return start; };
        const Vector2D& getEnd() const { return end; };
        const Vector2D& getDirection() const { return direction; };
        const double& getLength() const { return length; };
        
        //Methods
        bool contains(const Vector2D& vector);
        Vector2D* intersectionWith(const Segment& segment);
    };
}

#endif /* Segment_h */
