//
//  Input.cpp
//  MATSEWhiteStarLine
//
//  Created by WetterOnline GmbH on 04.04.17.
//  Copyright © 2017 Sören Schmaljohann. All rights reserved.
//

#include "Input.h"

#include <fstream>
#include <sstream>
#include <dirent.h>

using namespace std;

namespace Input
{
    void InputData::onError(const int& line, const string& error)
    {
        *description = "ERROR in Line " + to_string(line) + ": " + error + "\n";
        fields = nullptr;
        route = nullptr;
        field = nullptr;
        this->error = true;
    }
    
    bool InputData::read(const string& filePath)
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
        
        stringstream lineStream;
        
        bool isField = true;
        
        while (isField && getline(stream, line))
        {
            if (line.length() != 0 && line[0] != ';')
            {
                lineStream = stringstream(line);
                double x, y;
                if (lineStream >> x >> y)
                {
                    isField = false;
                    field = new Dataholder::CurrentField(Dataholder::Vector2D(), Dataholder::Vector2D(x, y), Dataholder::Vector2D());
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
                lineStream = stringstream(line);
                double xStart, yStart, xEnd, yEnd;
                if (lineStream >> xStart >> yStart >> xEnd >> yEnd)
                {
                    isRoute = false;
                    route = new Dataholder::Segment(Dataholder::Vector2D(xStart, yStart), Dataholder::Vector2D(xEnd, yEnd));
                }
                else
                {
                    onError(lineCount, "Die Route wurde nicht (richtig) angegeben");
                    return false;
                }
            }
            ++lineCount;
        }
        
        fields = new vector<Dataholder::CurrentField>(0);
        
        while (getline(stream, line))
        {
            if (line.length() != 0 && line[0] != ';')
            {
                lineStream = stringstream(line);
                double xOrigin, yOrigin, xEnd, yEnd, xFlow, yFlow;
                if (lineStream >> xOrigin >> yOrigin >> xEnd >> yEnd >> xFlow >> yFlow)
                {
                    Dataholder::CurrentField current(Dataholder::Vector2D(xOrigin, yOrigin), Dataholder::Vector2D(xEnd, yEnd), Dataholder::Vector2D(xFlow, yFlow));
                    
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
    
    vector<InputData*>* readInputDir()
    {
        DIR *dir;
        struct dirent *ent;
        if ((dir = opendir ("./Input/")) != NULL)
        {
            vector<InputData*>* data = new vector<InputData*>(0);
            while ((ent = readdir (dir)) != NULL)
            {
                string name(ent->d_name);
                if (name != "." && name != "..")
                {
                    InputData* current = new InputData("./Input/" + name);
                    if (current != nullptr)
                    {
                        data->push_back(current);
                    }
                }
            }
            closedir (dir);
            return data;
        }
        else
        {
            return nullptr;
        }
    }
    
    string InputData::resultString() const
    {
        string result("");
        
        result += "*************************\n";
        result += *description;
        result += "*************************\n";
        
        if (error)
        {
            return result;
        }
        
        result += "\nGröße des Gebiets:\n";
        result += to_string(field->end().x()) + " " + to_string(field->end().y()) + "\n";
        
        result += "\nZu fahrende Route:\n";
        result += "Punkt A: " + route->start().toString() + "\n";
        result += "Punkt E: " + route->end().toString() + "\n";
        
        result += "\nStrömungen\n";
        for (Dataholder::CurrentField current: *fields)
        {
            result += current.toString() + "\n";
        }
        
        return result;
    }
}
