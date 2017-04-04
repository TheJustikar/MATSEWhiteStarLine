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
        CurrentField(const Vector2D origin, const Vector2D end, const Vector2D current) : _origin(origin), _end(end), _current(current) {};
        
        //Getter
        const Vector2D& origin() const { return _origin; };
        const Vector2D& end() const { return _end; };
        const Vector2D& current() const { return _current; };
        
        //Setter
        void setOrigin(const Vector2D origin) { _origin = origin; };
        void setEnd(const Vector2D end) { _end = end; };
        void setCurrent(const Vector2D current) { _current = current; };
        
        //Methods
        bool contains(const Vector2D& vector) const;
        bool contains(const Segment& segment) const;
        bool contains(const CurrentField& field) const;
        vector< Vector2D > intersectionsWith(const Segment& segment) const;
        
    };
}

#endif /* CurrentField_hpp */
