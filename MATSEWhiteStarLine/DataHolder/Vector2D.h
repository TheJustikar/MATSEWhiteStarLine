//
//  Vector2D.h
//  MATSEWhiteStarLine
//
//  Created by WetterOnline GmbH on 04.04.17.
//  Copyright © 2017 Sören Schmaljohann. All rights reserved.
//

#ifndef Vector2D_h
#define Vector2D_h

#include <cmath>

namespace Dataholder
{
    class Vector2D
    {
        
    private:
        double x, y;
        double length;
        
    public:
        //Constructor
        Vector2D(const double& x, const double& y) : x(x), y(y) { length = std::hypot(x, y); };
        
        //Setter
        void setX(const double& x) { this->x = x; length = std::hypot(x, y); };
        void setY(const double& y) { this->y = y; length = std::hypot(x, y); };
        
        //Getter
        const double& getX() const { return x; };
        const double& getY() const { return y; };
        const double& getLength() const { return length; };
        
        //Operators
        Vector2D operator + (const Vector2D& rhs) const { return Vector2D::Vector2D(rhs.x + x, rhs.y + y); };
        Vector2D operator - (const Vector2D& rhs) const { return Vector2D::Vector2D(rhs.x - x, rhs.y - y); };
        Vector2D operator * (const double& rhs) const { return Vector2D::Vector2D(rhs * x, rhs * y); };
        bool operator == (const Vector2D& rhs) const { return rhs.x == x && rhs.y == y; };
        
    };
}

#endif /* Vector2D_h */
