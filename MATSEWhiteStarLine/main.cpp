//
//  main.cpp
//  MATSEWhiteStarLine
//
//  Created by WetterOnline GmbH on 04.04.17.
//  Copyright © 2017 Sören Schmaljohann. All rights reserved.
//

#include <iostream>
#include <string>
#include <list>
#include <stack>

#include "Vector2D.h"
#include "Segment.h"
#include "CurrentField.h"
#include "RoutePart.h"

#include "Input.h"
#include "Output.h"

using namespace std;

vector<Dataholder::RoutePart>* calculateRouteForInput(const Input::InputData& data)
{
    if (data.isError())
    {
        return new vector<Dataholder::RoutePart>(0);
    }
    
    list<Dataholder::RoutePart> results = list<Dataholder::RoutePart>(0);
    
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
            Dataholder::RoutePart* currentResult = nullptr;
            
            if (intersections.size() == 0 && currentField.contains(segments[i]))
            {
                currentResult = new Dataholder::RoutePart(Dataholder::Segment(segments[i].start(), segments[i].end()), currentField.current());
                segments.erase(segments.begin() + i);
            }
            else if (intersections.size() == 1)
            {
                if (currentField.contains(segments[i].start()))
                {
                    currentResult = new Dataholder::RoutePart(Dataholder::Segment(segments[i].start(), intersections[0]), currentField.current());
                    newSegments.push_back(Dataholder::Segment(intersections[0], segments[i].end()));
                    segments.erase(segments.begin() + i);
                }
                else
                {
                    currentResult = new Dataholder::RoutePart(Dataholder::Segment(intersections[0], segments[i].end()), currentField.current());
                    newSegments.push_back(Dataholder::Segment(segments[i].start(), intersections[0]));
                    segments.erase(segments.begin() + i);
                }
            }
            else if (intersections.size() == 2)
            {
                currentResult = new Dataholder::RoutePart(Dataholder::Segment(segments[i].start().nearestOf(intersections), segments[i].end().nearestOf(intersections)), currentField.current());
                newSegments.push_back(Dataholder::Segment(segments[i].start(), segments[i].start().nearestOf(intersections)));
                newSegments.push_back(Dataholder::Segment(segments[i].end().nearestOf(intersections), segments[i].end()));
                segments.erase(segments.begin() + i);
            }
            else
            {
                ++i;
            }
            
            if (currentResult != nullptr)
            {
                results.push_back(*currentResult);
            }
        }
        
        for (Dataholder::Segment newSegment: newSegments)
        {
            segments.push_back(newSegment);
        }
        
        currents.pop();
    }
    
    if (!segments.empty())
    {
        for (Dataholder::Segment current: segments)
        {
            results.push_back(Dataholder::RoutePart(current, Dataholder::Vector2D()));
        }
    }
    
    vector<Dataholder::RoutePart>* sortedResults = new vector<Dataholder::RoutePart>(0);
    Dataholder::Vector2D referencePoint = data.route->start();
    
    Dataholder::RoutePart* nearest = nullptr;
    
    while (!results.empty())
    {
        for (Dataholder::RoutePart currentResult: results)
        {
            if (nearest == nullptr || (referencePoint - currentResult.route.start()).length() < (referencePoint - nearest->route.start()).length())
            {
                nearest = &currentResult;
            }
        }
        
        sortedResults->push_back(*nearest);
        results.remove(*nearest);
    }
    
    return sortedResults;
}

int main(int argc, const char * argv[])
{
    vector<Input::InputData*>* data = Input::readInputDir();
    
    if (data != nullptr)
    {
        vector<pair<Input::InputData, vector<Dataholder::RoutePart>>> results(0);
        
        for (Input::InputData* currentData: *data)
        {
            vector<Dataholder::RoutePart>* routeParts = calculateRouteForInput(*currentData);
            
//            Dataholder::Vector2D start = currentData->route->start();
//            sort(routeParts->begin(), routeParts->end(), [start](const Dataholder::RoutePart& a, const  Dataholder::RoutePart& b) -> bool
//            {
//                return (start - a.route.start()) < (start - b.route.start());
//            });
            
            results.push_back(pair<Input::InputData, vector<Dataholder::RoutePart>>(*currentData, *routeParts));
        }
        
        Output::writeResult(results);
    }
    
    return 0;
}
