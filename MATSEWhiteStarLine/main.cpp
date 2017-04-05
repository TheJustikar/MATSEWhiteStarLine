//
//  main.cpp
//  MATSEWhiteStarLine
//
//  Created by WetterOnline GmbH on 04.04.17.
//  Copyright © 2017 Sören Schmaljohann. All rights reserved.
//

#include <iostream>
#include <string>
#include <stack>
#include <list>

#include "Vector2D.h"
#include "Segment.h"
#include "CurrentField.h"
#include "RoutePart.h"

#include "Input.h"
#include "Output.h"

using namespace std;

vector<Dataholder::RoutePart>* calculateRouteForInput(const Input::InputData& data)
{
    vector<Dataholder::RoutePart>* result = new vector<Dataholder::RoutePart>(0);
    
    if (data.isError())
    {
        return result;
    }
    
    vector<Dataholder::Segment> segments(0);
    segments.push_back(*data.route);
    
    stack<Dataholder::CurrentField> currents;
    for (int i = 0; i < data.fields->size(); ++i)
    {
        currents.push(data.fields->at(i));
    }
    
    while (!segments.empty() && !currents.empty()) {
        
        Dataholder::CurrentField currentField = currents.top();
        vector<Dataholder::Segment> newSegments(0);
        
        for (int i = 0; i < segments.size();)
        {
            vector<Dataholder::Vector2D> intersections = currentField.intersectionsWith(segments[i]);
            
            if (intersections.size() == 0 && currentField.contains(segments[i]))
            {
                result->push_back(Dataholder::RoutePart(Dataholder::Segment(segments[i].start(), segments[i].end()), currentField.current()));
                segments.erase(segments.begin() + i);
            }
            else if (intersections.size() == 1)
            {
                if (currentField.contains(segments[i].start()))
                {
                    result->push_back(Dataholder::RoutePart(Dataholder::Segment(segments[i].start(), intersections[0]), currentField.current()));
                    newSegments.push_back(Dataholder::Segment(intersections[0], segments[i].end()));
                    segments.erase(segments.begin() + i);
                }
                else
                {
                    result->push_back(Dataholder::RoutePart(Dataholder::Segment(intersections[0], segments[i].end()), currentField.current()));
                    newSegments.push_back(Dataholder::Segment(segments[i].start(), intersections[0]));
                    segments.erase(segments.begin() + i);
                }
            }
            else if (intersections.size() == 2)
            {
                result->push_back(Dataholder::RoutePart(Dataholder::Segment(segments[i].start().nearestOf(intersections), segments[i].end().nearestOf(intersections)), currentField.current()));
                newSegments.push_back(Dataholder::Segment(segments[i].start(), segments[i].start().nearestOf(intersections)));
                newSegments.push_back(Dataholder::Segment(segments[i].end().nearestOf(intersections), segments[i].end()));
                segments.erase(segments.begin() + i);
            }
            else
            {
                ++i;
            }
        }
        
        for (Dataholder::Segment newSegment: newSegments)
        {
            segments.push_back(newSegment);
        }
        
        currents.pop();
    }
    
    return result;
}

int main(int argc, const char * argv[])
{
    vector<Input::InputData*>* data = Input::readInputDir();
    
    if (data != nullptr)
    {
        vector<pair<Input::InputData, vector<Dataholder::RoutePart>>> results(0);
        
        for (Input::InputData* current: *data)
        {
            results.push_back(pair<Input::InputData, vector<Dataholder::RoutePart>>(*current, *calculateRouteForInput(*current)));
        }
        
        Output::writeResult(results);
    }
    
    return 0;
}
