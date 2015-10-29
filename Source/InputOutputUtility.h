//
//  InputOutputUtility.h
//  Project1
//
//  Created by Brandon Nguyen on 9/28/15.
//  Copyright (c) 2015 Brandon Nguyen. All rights reserved.
//

#ifndef __Project1__InputOutputUtility__
#define __Project1__InputOutputUtility__

#define MAX_LINE_LEN 100
#define MAX_TOKENS 100

#include <fstream>
#include <cstring>
#include <stdexcept>
#include <deque>
#include <string>
#include <iostream>
#include "Vector2i.h"
#include "ObjectEditor.h"
#include "Line3d.h"
using namespace std;

class InputOutputUtility
{
private:    
    static void ProcessInput();
    
    //commands
//    static void ProcessCommandPolygon(deque<string> tokens);
//    static void ProcessCommandLine(deque<string> tokens);
    static void ProcessCommandTranslate(deque<string> tokens);
    static void ProcessCommandScale(deque<string> tokens);
    static void ProcessCommandRotate(deque<string> tokens);
//    static void ProcessCommandClip(deque<string> tokens);
    static void ProcessCommandLoadFile(deque<string> tokens);
    static void ProcessCommandSaveFile(deque<string> tokens);
    
    static deque<string> SplitString(string s, string delims);
    static deque<Vector3> ExtractVertices(deque<string> tokens);
    
public:
    static void QueryWindowSize();
    static void DetectInput(unsigned char key, int xmouse, int ymouse);
    static void ParsePolygonFile(string fileName);
    static void SavePolygonFile(string fileName);
};

#endif /* defined(__Project1__InputOutputUtility__) */
