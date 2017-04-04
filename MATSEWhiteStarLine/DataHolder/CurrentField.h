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
    class CurrentField
    {
        
    private:
        Vector2D origin, end, current;
        
    public:
        //Constructor
        CurrentField(const Vector2D& origin, const Vector2D& end, const Vector2D& current) : origin(origin), end(end), current(current) {};
        
        //Getter
        const Vector2D& getOrigin() const { return origin; };
        const Vector2D& getEnd() const { return end; };
        const Vector2D& getCurrent() const { return current; };
        
        //Setter
        void setOrigin(const Vector2D& origin) { this->origin = origin; };
        void setEnd(const Vector2D& end) { this->end = end; };
        void setCurrent(const Vector2D& current) { this->current = current; };
        
        //Methods
        bool contains(const Vector2D& vector);
        std::vector< Vector2D > intersectionsWith(const Segment& segment);
        
    };
}

#endif /* CurrentField_hpp */
