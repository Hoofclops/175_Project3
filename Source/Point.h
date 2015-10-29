//
//  Point.h
//  Project1
//
//  Created by Brandon Nguyen on 9/25/15.
//  Copyright (c) 2015 Brandon Nguyen. All rights reserved.
//

#ifndef __Project1__Point__
#define __Project1__Point__

#include "Vector2i.h"
#include "Color.h"

class Point
{
private:
    Vector2i mPos;
    Color mColor;
    
public:
    
    Point();
    Point(Vector2i pos);
    Point(Vector2i pos, Color color);
    Point(int x, int y);
    Point(int x, int y, Color color);
    
    //Setters and getters
    Vector2i Position(){return mPos;}
    void Position(Vector2i pos){mPos = pos;}
    int X(){return mPos.mX;}
    void X(int x){mPos.mX = x;}
    int Y(){return mPos.mY;}
    void Y(int y){mPos.mY = y;}
    Color GetColor(){return mColor;}
    void SetColor(Color color){mColor = color;}
};

#endif /* defined(__Project1__Point__) */
