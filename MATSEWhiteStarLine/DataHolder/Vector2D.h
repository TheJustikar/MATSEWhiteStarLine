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
#include <string>

namespace Dataholder
{
    using namespace std;
    
    class Vector2D
    {
        
    private:
        double _x, _y;
        double _length;
        
    public:
        //Constructor
        Vector2D(const double x = 0, const double y = 0) : _x(x), _y(y) { _length = hypot(_x, _y); };
        
        //Getter
        const double& x() const { return _x; };
        const double& y() const { return _y; };
        const double& length() const { return _length; };
        
        //Setter
        void setX(const double x) { _x = x; _length = hypot(_x, _y); };
        void setY(const double y) { _y = y; _length = hypot(_x, _y); };
        
        //Operators
        Vector2D operator + (const Vector2D& rhs) const { return Vector2D::Vector2D(_x + rhs._x, _y + rhs._y); };
        Vector2D operator - (const Vector2D& rhs) const { return Vector2D::Vector2D(_x - rhs._x, _y - rhs._y); };
        Vector2D operator * (const double& rhs) const { return Vector2D::Vector2D(_x * rhs, _y * rhs); };
        double operator * (const Vector2D& rhs) const { return (_x * rhs._x) + (_y * rhs._y); };
        bool operator == (const Vector2D& rhs) const { return _x == rhs._x && _y == rhs._y; };
        
        //Methods
        string toString() const { return "(" + to_string(_x) + ";" + to_string(_y) + ")"; };
    };
}

#endif /* Vector2D_h */
