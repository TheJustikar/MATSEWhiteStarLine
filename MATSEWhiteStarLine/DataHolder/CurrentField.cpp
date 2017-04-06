//
//  CurrentField.cpp
//  MATSEWhiteStarLine
//
//  Created by WetterOnline GmbH on 04.04.17.
//  Copyright © 2017 Sören Schmaljohann. All rights reserved.
//

#include "CurrentField.h"

using namespace std;

namespace Dataholder
{
    bool CurrentField::contains(const Vector2D &vector) const
    {
        bool xIsInside = (vector.x() >= _origin.x() && vector.x() <= _end.x()) || (vector.x() <= _origin.x() && vector.x() >= _end.x());
        bool yIsInside = (vector.y() >= _origin.y() && vector.y() <= _end.y()) || (vector.y() <= _origin.y() && vector.y() >= _end.y());
        
        return xIsInside && yIsInside;
    }
    
    bool CurrentField::containsParts(const CurrentField &field) const
    {
        return contains(field._origin) || contains(field._end) || contains(Vector2D(field._origin.x(), field._end.y())) || contains(Vector2D(field._end.x(), field._origin.y()));
    }
    
    vector<Vector2D> CurrentField::intersectionsWith(const Dataholder::Segment &segment) const
    {
        bool containsStart = contains(segment.start());
        bool containsEnd = contains(segment.end());
        
        if (containsStart && containsEnd)
        {
            return vector<Vector2D>(0);
        }
        
        vector<Vector2D> ret(0);
        
        vector<Segment> borders(0);
        if (containsStart)
        {
            borders = nearestBordersTo(segment.end());
        }
        else if (containsEnd)
        {
            borders = nearestBordersTo(segment.start());
        }
        else
        {
            borders = nearestBordersTo(segment.start(), segment.end());
        }
        
        //Intersections with all relevat borders
        for (Segment current: borders)
        {
            const Vector2D* intersection = current.intersectionWith(segment);
            if (intersection != nullptr)
            {
                ret.push_back(*intersection);
            }
        }
        
        if (ret.size() <= 2)
        {
            return ret;
        }
        return vector<Vector2D>(0);
    }
    
    vector<Segment> CurrentField::nearestBordersTo(const Vector2D& point) const
    {
        vector<Segment> borders(0);
        
        bool nearXorigin = abs(point.x() - _origin.x()) < abs(point.x() - _end.x());
        bool nearYorigin = abs(point.y() - _origin.y()) < abs(point.y() - _end.y());
        bool insideX = (point.x() >= _origin.x() && point.x() <= _end.x()) || (point.x() <= _origin.x() && point.x() >= _end.x());
        bool insideY = (point.y() >= _origin.y() && point.y() <= _end.y()) || (point.y() <= _origin.y() && point.x() >= _end.y());
        
        if (nearXorigin && nearYorigin)
        {
            if (insideX && !insideY)
            {
                borders.push_back(Segment(_origin, Vector2D(_end.x(), _origin.y())));
            }
            else if (insideY && !insideX)
            {
                borders.push_back(Segment(_origin, Vector2D(_origin.x(), _end.y())));
            }
            else
            {
                borders.push_back(Segment(_origin, Vector2D(_end.x(), _origin.y())));
                borders.push_back(Segment(_origin, Vector2D(_origin.x(), _end.y())));
            }
        }
        else if (!nearXorigin && nearYorigin)
        {
            if (insideX && !insideY)
            {
                borders.push_back(Segment(_origin, Vector2D(_end.x(), _origin.y())));
            }
            else if (insideY && !insideX)
            {
                borders.push_back(Segment(Vector2D(_end.x(), _origin.y()), _end));
            }
            else
            {
                borders.push_back(Segment(_origin, Vector2D(_end.x(), _origin.y())));
                borders.push_back(Segment(Vector2D(_end.x(), _origin.y()), _end));
            }
        }
        else if (nearXorigin && !nearYorigin)
        {
            if (insideX && !insideY)
            {
                borders.push_back(Segment(Vector2D(_origin.x(), _end.y()), _end));
            }
            else if (insideY && !insideX)
            {
                borders.push_back(Segment(_origin, Vector2D(_origin.x(), _end.y())));
            }
            else
            {
                borders.push_back(Segment(Vector2D(_origin.x(), _end.y()), _end));
                borders.push_back(Segment(_origin, Vector2D(_origin.x(), _end.y())));
            }
        }
        else
        {
            if (insideX && !insideY)
            {
                borders.push_back(Segment(Vector2D(_origin.x(), _end.y()), _end));
            }
            else if (insideY && !insideX)
            {
                borders.push_back(Segment(Vector2D(_end.x(), _origin.y()), _end));
            }
            else
            {
                borders.push_back(Segment(Vector2D(_origin.x(), _end.y()), _end));
                borders.push_back(Segment(Vector2D(_end.x(), _origin.y()), _end));
            }
        }
        
        return borders;
    }
    
    vector<Segment> CurrentField::nearestBordersTo(const Vector2D& point1, const Vector2D& point2) const
    {
        vector<Segment> borders = nearestBordersTo(point1);
        
        for(Segment currentBorder: nearestBordersTo(point2))
        {
            bool shouldAdd = true;
            for (Segment current: borders)
            {
                shouldAdd = shouldAdd && current != currentBorder;
            }
            if (shouldAdd)
            {
                borders.push_back(currentBorder);
            }
        }
        
        return borders;
    }
}
