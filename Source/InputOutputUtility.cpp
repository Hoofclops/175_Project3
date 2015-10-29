//
//  InputOutputUtility.cpp
//  Project1
//
//  Created by Brandon Nguyen on 9/28/15.
//  Copyright (c) 2015 Brandon Nguyen. All rights reserved.
//
//  Parse polygon file Code based off of code from http://cs.dvc.edu/HowTo_Cparse.html

#include "InputOutputUtility.h"

void InputOutputUtility::QueryWindowSize()
{
    int xDim, yDim;
    
    cout << "Enter X window dimension: ";
    cin >> xDim;
    cout << "Enter Y window dimension: ";
    cin >> yDim;
    cin.ignore();
    
    Renderer::Instance()->InitWindow(xDim + 1, yDim + 1);
}

void InputOutputUtility::DetectInput(unsigned char key, int xmouse, int ymouse)
{
    switch(key)
    {
            case 'i':
                ProcessInput();
            break;
            case 'I':
                ProcessInput();
            break;
            case 'n':
                ObjectEditor::Instance()->CycleSelectedPoly(true);
            break;
            case 'b':
                ObjectEditor::Instance()->CycleSelectedPoly(false);
            break;
    }
    
    Renderer::Instance()->DrawScene();
}

void InputOutputUtility::ProcessInput()
{
    string input;
    cout << "Enter command: ";
    getline(cin, input);
    
    deque<string> tokens = SplitString(input, string(" "));
    
    if(tokens.size() == 0)
    {
        return;
    }
    
    string command = tokens[0];
    tokens.pop_front();
    
    //Parse strings
//    if(command == "Polygon" || command == "polygon")
//    {
//        ProcessCommandPolygon(tokens);
//    }
//    else if(command == "Line" || command == "line")
//    {
//        ProcessCommandLine(tokens);
//    }
    if(command == "Translate" || command == "translate")
    {
        ProcessCommandTranslate(tokens);
    }
    else if(command == "Scale" || command == "scale")
    {
        ProcessCommandScale(tokens);
    }
    else if(command == "Rotate" || command == "rotate")
    {
        ProcessCommandRotate(tokens);
    }
    else if(command == "Load" || command == "load")
    {
        ProcessCommandLoadFile(tokens);
    }
    else if(command == "Save" || command == "save")
    {
        ProcessCommandSaveFile(tokens);
    }
    else if(command == "Clear" || command == "clear")
    {
        Renderer::Instance()->ClearBuffer();
        ObjectEditor::Instance()->ClearData();
    }
    else
    {
        cout << "Invalid command, please enter another command" << endl;
        return;
    }
}

//void InputOutputUtility::ProcessCommandPolygon(deque<string> tokens)
//{
//    deque<Vector3i> vertexPositions = ExtractVertices(tokens);
//    
//    if(vertexPositions.size() == 0)
//    {
//        cout << "Invalid command" << endl;
//        return;
//    }
//    ObjectEditor::Instance()->CreatePolygon(vertexPositions);
//}

//void InputOutputUtility::ProcessCommandLine(deque<string> tokens)
//{
//    deque<Vector3> vertexPositions = ExtractVertices(tokens);
//    
//    if(vertexPositions.size() != 2)
//    {
//        cout << "Invalid command" << endl;
//        return;
//    }
//    
//    Line line = Line(Point(vertexPositions[0].mX, vertexPositions[0].mY), Point(vertexPositions[1].mX, vertexPositions[1].mY));
//    ObjectEditor::Instance()->CreateLine(line);
//}

void InputOutputUtility::ProcessCommandTranslate(deque<string> tokens)
{
    bool animate = false;
    if(tokens[0] == "Animate" || tokens[0] == "animate")
    {
        animate = true;
        tokens.pop_front();
    }
    
    deque<Vector3> vertexPositions = ExtractVertices(tokens);
    
    if(vertexPositions.size() != 1)
    {
        cout << "Invalid command" << endl;
        return;
    }
    if(animate)
    {
//        Renderer::Instance()->AnimateTranslate(vertexPositions[0]);
        ObjectEditor::Instance()->TranslatePolygon(vertexPositions[0]);
    }
    else
    {
        ObjectEditor::Instance()->TranslatePolygon(vertexPositions[0]);
    }
}

void InputOutputUtility::ProcessCommandScale(deque<string> tokens)
{
    
    bool animate = false;
    if(tokens[0] == "Animate" || tokens[0] == "animate")
    {
        animate = true;
        tokens.pop_front();
    }
    
    if(tokens.size() != 3)
    {
        cout << "Invalid command" << endl;
        return;
    }
    
    float scaleX = stof(tokens[0]);
    float scaleY = stof(tokens[1]);
    float scaleZ = stof(tokens[2]);
    
    
    if(animate)
    {
        ObjectEditor::Instance()->ScalePolygon(scaleX, scaleY, scaleZ);
    }
    else
    {
        ObjectEditor::Instance()->ScalePolygon(scaleX, scaleY, scaleZ);
    }
}
void InputOutputUtility::ProcessCommandRotate(deque<string> tokens)
{
    bool animate = false;
    if(tokens[0] == "Animate" || tokens[0] == "animate")
    {
        animate = true;
        tokens.pop_front();
    }
    
    if(tokens.size() != 3)
    {
        cout << "Invalid command" << endl;
        return;
    }
    
    double degrees = stod(tokens[0]);
    tokens.pop_front();
    deque<Vector3> vertexPositions = ExtractVertices(tokens);
    if(animate)
    {
//        Renderer::Instance()->AnimateRotation(degrees, vertexPositions[0], vertexPositions[1]);
        ObjectEditor::Instance()->RotatePolygon(degrees, vertexPositions[0], vertexPositions[1]);
    }
    else
    {
        ObjectEditor::Instance()->RotatePolygon(degrees, vertexPositions[0], vertexPositions[1]);
    }
}

//void InputOutputUtility::ProcessCommandClip(deque<string> tokens)
//{
//    deque<Vector3> vertexPositions = ExtractVertices(tokens);
//
//    if(vertexPositions.size() != 2)
//    {
//        cout << "Invalid command" << endl;
//        return;
//    }
//    
//    ObjectEditor::Instance()->SetClip(vertexPositions[0], vertexPositions[1]);
//}

void InputOutputUtility::ProcessCommandLoadFile(deque<string> tokens)
{
    if(tokens.size() != 1)
    {
        cout << "Invalid command" << endl;
        return;
    }
    
    ParsePolygonFile(tokens[0]);
}

void InputOutputUtility::ProcessCommandSaveFile(deque<string> tokens)
{
    if(tokens.size() != 1)
    {
        cout << "Invalid command" << endl;
        return;
    }
    
    SavePolygonFile(tokens[0]);
}

void InputOutputUtility::ParsePolygonFile(string fileName)
{
    bool parsingEdges = false;
    ifstream fin;
//   fin.open(fileName);
     fin.open("//Users//BrandonHome//GitHub//175_Project2//DataFiles//" + fileName);
    if (!fin.good())
        throw runtime_error("Error opening poly.txt");
    
    const char* tokens[MAX_TOKENS] = {}; // initialize to 0
    deque<Vector3> vertexPositions;
    deque<Vector2i> edgeConnections;
    
    while (!fin.eof())
    {
        char buf[MAX_LINE_LEN];
        fin.getline(buf, MAX_LINE_LEN);
        
        int i = 0;
        tokens[0] = strtok(buf, ", ");
        if (tokens[0]) // zero if line is blank
        {
            for (i = 1; i < MAX_TOKENS; i++)
            {
                tokens[i] = strtok(0, ", ");
                if (!tokens[i])
                    break;
            }
        }
        
        if(!tokens[0])
        {
            continue;
        }
        
        //Parse strings
        if(strcmp(tokens[0], "End") == 0 || strcmp(tokens[0], "end") == 0)
        {
            ObjectEditor::Instance()->CreatePolygon(vertexPositions, edgeConnections);
            vertexPositions.clear();
            edgeConnections.clear();
            parsingEdges = false;
        }
        else if(strcmp(tokens[0], "Edges") == 0 || strcmp(tokens[0], "edges") == 0)
        {
            parsingEdges = true;
        }
        else if(!parsingEdges)
        {
            float x = atof(tokens[0]);
            float y = atof(tokens[1]);
            float z = atof(tokens[2]);
            vertexPositions.push_back(Vector3(x, y, z));
        }
        else
        {
            int index1 = atoi(tokens[0]) - 1;
            int index2 = atoi(tokens[1]) - 1;
            edgeConnections.push_back(Vector2i(index1, index2));
        }
    }
    
    fin.close();
}

void InputOutputUtility::SavePolygonFile(string fileName)
{
    ofstream fout;
//    fout.open(fileName, ofstream::out | ofstream::trunc);
    fout.open("//Users//BrandonHome//GitHub//175_Project2//DataFiles//" + fileName, ofstream::out | ofstream::trunc);
    
    deque<Polygon> allPolys = ObjectEditor::Instance()->GetPolygons();
    
    long polyCount = allPolys.size();
    for(unsigned int i = 0; i < polyCount; i++)
    {
        deque<Point3d> vertices = allPolys[i].GetVertices();
        deque<Vector2i> edges = allPolys[i].GetEdgeConnections();
        
        //store vertices
        long vertexCount = vertices.size();
        for(unsigned int j = 0; j < vertexCount; j++)
        {
            fout << vertices[j].X() << " " << vertices[j].Y() << " " << vertices[j].Z() << "\n";
        }
        
        //store edge connections
        fout << "Edges" << "\n";
        long edgeCount = edges.size();
        for(unsigned int j = 0; j < edgeCount; j++)
        {
            fout << edges[j].mX + 1 << " " << edges[j].mY + 1 << "\n";
        }
        
        fout << "End" << "\n" << "\n";
    }
    
    fout.close();
}

deque<string> InputOutputUtility::SplitString(string s, string delims)
{
    deque<string> tokens;
    const char *str = s.c_str();
    do
    {
        const char *begin = str;
        
        while(*str)//(*str != c && *str)
        {
            
            //Search delims for current char
            size_t found = delims.find(*str);
            if (found != string::npos)
                break;
            
            str++;
        }
        
        string tok = string(begin, str);
        if(tok != "")
            tokens.push_back(string(begin, str));
        
    } while (0 != *str++);
    
    return tokens;

}

deque<Vector3> InputOutputUtility::ExtractVertices(deque<string> tokens)
{
    deque<Vector3> vertexPositions;
    
    long n = tokens.size();
    for(int i = 0; i < n; i++)
    {
        deque<string> vertex = SplitString(tokens[i], string("(),"));
        
        if(vertex.size() != 3)
        {
            cout << "Invalid vertex format" << endl;
            vertexPositions.clear();
            return vertexPositions;
        }
        
        Vector3 vertPos = Vector3(atof(vertex[0].c_str()), atof(vertex[1].c_str()), atof(vertex[2].c_str()));
        vertexPositions.push_back(Vector3(vertPos.mX, vertPos.mY, vertPos.mZ));
    }
    
    return vertexPositions;
}
