//
//  CurrentField.h
//  MATSEWhiteStarLine
//
//  Created by WetterOnline GmbH on 04.04.17.
//  Copyright © 2017 Sören Schmaljohann. All rights reserved.
//

#ifndef CurrentField_h
#define CurrentField_h

#include <vector>

#include "Vector2D.h"
#include "Segment.h"

namespace Dataholder
{
    using namespace std;
    
    class CurrentField
    {
        
    private:
        Vector2D _origin, _end, _current;
        
    public:
        //Constructor
        CurrentField(const Vector2D& origin = Vector2D(), const Vector2D& end = Vector2D(), const Vector2D& current = Vector2D()) : _origin(origin), _end(end), _current(current) {};
        
        //Getter
        const Vector2D& origin() const { return _origin; };
        const Vector2D& end() const { return _end; };
        const Vector2D& current() const { return _current; };
        
        //Setter
        void setOrigin(const Vector2D& origin) { _origin = origin; };
        void setEnd(const Vector2D& end) { _end = end; };
        void setCurrent(const Vector2D& current) { _current = current; };
        
        //Methods
        bool contains(const Vector2D& vector) const;
        bool contains(const Segment& segment) const;
        bool containsParts(const Segment& segment) const;
        bool contains(const CurrentField& field) const;
        bool containsParts(const CurrentField& field) const;
        vector<Vector2D> intersectionsWith(const Segment& segment) const;
        string toString() const { return _origin.toString() + " " + _end.toString() + " SV = " + _current.toString(); };
        vector<Segment> nearestBordersTo(const Vector2D& point) const;
        vector<Segment> nearestBordersTo(const Vector2D& point1, const Vector2D& point2) const;
        
    };
}

#endif /* CurrentField_hpp */
