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
        Vector2D _start, _end, _direction;
        double _length;
        
    public:
        //Constructor
        Segment(const Vector2D start, const Vector2D end) : _start(start), _end(end), _direction(end - start) { _length = _direction.length(); };
        
        //Getter
        const Vector2D& start() const { return _start; };
        const Vector2D& end() const { return _end; };
        const Vector2D& direction() const { return _direction; };
        const double& length() const { return _length; };
        
        //Setter
        void setStart(const Vector2D& start) { _start = start; _direction = _end - start; _length = _direction.length(); };
        void setEnd(const Vector2D& end) { _end = end; _direction = end - _start; _length = _direction.length(); };
        
        //Operator
        bool operator == (const Segment& rhs) const { return rhs._start == _start && rhs._end == _end; };
        
        //Methods
        bool isParallell (const Segment& segment) const;
        bool contains(const Vector2D& vector) const;
        bool contains(const Segment& segment) const;
        const Vector2D* intersectionWith(const Segment& segment);
    };
}

#endif /* Segment_h */
