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
        double _x, _y;
        double _length;
        
    public:
        //Constructor
        Vector2D(const double& x, const double& y) : _x(x), _y(y) { _length = std::hypot(x, y); };
        
        //Getter
        const double& x() const { return _x; };
        const double& y() const { return _y; };
        const double& length() const { return _length; };
        
        //Setter
        void setX(const double& x) { _x = x; _length = std::hypot(x, _y); };
        void setY(const double& y) { _y = y; _length = std::hypot(_x, y); };
        
        //Operators
        Vector2D operator + (const Vector2D& rhs) const { return Vector2D::Vector2D(rhs._x + _x, rhs._y + _y); };
        Vector2D operator - (const Vector2D& rhs) const { return Vector2D::Vector2D(rhs._x - _x, rhs._y - _y); };
        Vector2D operator * (const double& rhs) const { return Vector2D::Vector2D(rhs * _x, rhs * _y); };
        bool operator == (const Vector2D& rhs) const { return rhs._x == _x && rhs._y == _y; };
        
    };
}

#endif /* Vector2D_h */
