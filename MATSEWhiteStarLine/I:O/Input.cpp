//
//  Input.cpp
//  MATSEWhiteStarLine
//
//  Created by WetterOnline GmbH on 04.04.17.
//  Copyright © 2017 Sören Schmaljohann. All rights reserved.
//

#include "Input.h"

#include <fstream>

using namespace std;

namespace Input
{
    string* description = nullptr;
    vector<CurrentField>* fields = nullptr;
    Segment* route = nullptr;
    CurrentField* field = nullptr;
    
    void onError(const int& line, const string& error)
    {
        *description = string("ERROR in Line ") + to_string(line) + string(": ") + error;
        fields = nullptr;
        route = nullptr;
        field = nullptr;
    }
    
    bool read(const string& filePath)
    {
        ifstream stream(filePath);
        
        int lineCount = 1;
        
        bool isDescription = true;
        
        string line;
        
        description = new string("");
        
        while (isDescription && getline(stream, line))
        {
            if (line.length() != 0)
            {
                if (line[0] != ';' || (line.length() <= 2 && line[1] != ' '))
                {
                    onError(lineCount, "Beschreibung beginnt nicht mit einem '; '");
                    return false;
                }
                
                string text = line.substr(2);
                
                if (lineCount == 1)
                {
                    if (text != "*************************")
                    {
                        onError(lineCount, "Beschreibung wird nicht mit 25 '*' eingeleitet");
                        return false;
                    }
                }
                else
                {
                    if (text == "*************************")
                    {
                        isDescription = false;
                    }
                    else
                    {
                        *description += text + "\n";
                    }
                }
            }
            
            ++lineCount;
        }
        
        if (isDescription)
        {
            onError(lineCount, "Beschreibung wurde nicht beendet");
            return false;
        }
        
        ifstream lineStream;
        
        bool isField = true;
        
        while (isField && getline(stream, line))
        {
            if (line.length() != 0 && line[0] != ';')
            {
                lineStream = ifstream(line);
                double x, y;
                if (lineStream >> x >> y)
                {
                    isField = false;
                    *field = CurrentField(Vector2D(), Vector2D(x, y), Vector2D());
                }
                else
                {
                    onError(lineCount, "Das Feld wurde nicht eingegrenzt");
                    return false;
                }
            }
            ++lineCount;
        }
        
        bool isRoute = true;
        
        while (isRoute && getline(stream, line))
        {
            if (line.length() != 0 && line[0] != ';')
            {
                lineStream = ifstream(line);
                double xStart, yStart, xEnd, yEnd;
                if (lineStream >> xStart >> yStart >> xEnd >> yEnd)
                {
                    isRoute = false;
                    *route = Segment(Vector2D(xStart, yStart), Vector2D(xEnd, yEnd));
                }
                else
                {
                    onError(lineCount, "Die Route wurde nicht (richtig) angegeben");
                    return false;
                }
            }
            ++lineCount;
        }
        
        *fields = vector<CurrentField>(0);
        
        while (getline(stream, line))
        {
            if (line.length() != 0 && line[0] != ';')
            {
                lineStream = ifstream(line);
                double xOrigin, yOrigin, xEnd, yEnd, xFlow, yFlow;
                if (lineStream >> xOrigin >> yOrigin >> xEnd >> yEnd >> xFlow >> yFlow)
                {
                    CurrentField current(Vector2D(xOrigin, yOrigin), Vector2D(xEnd, yEnd), Vector2D(xFlow, yFlow));
                    
                    if ((*field).containsParts(current))
                    {
                        (*fields).push_back(current);
                    }
                }
                else
                {
                    onError(lineCount, "Das Strömungsfeld wurde nicht (richtig) angegeben");
                    return false;
                }
            }
            ++lineCount;
        }
        
        if (!(*field).contains(*route))
        {
            onError(lineCount, "Route liegt nicht im Gebiet");
            return false;
        }
        
        return true;
    }
}
