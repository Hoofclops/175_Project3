//
//  Point3d.h
//  Source
//
//  Created by Brandon Nguyen on 10/14/15.
//  Copyright © 2015 Brandon Nguyen. All rights reserved.
//

#ifndef Point3d_h
#define Point3d_h

#include "Vector3.h"
#include "Color.h"

class Point3d
{
private:
    Vector3 mPos;
    Color mColor;
    
public:
    
    Point3d();
    Point3d(Vector3 pos);
    Point3d(Vector3 pos, Color color);
    Point3d(float x, float y, float z);
    Point3d(float x, float y, float z, Color color);
    
    Vector3 Pos(){return mPos;}
    void Pos(Vector3 vect){mPos = vect;};
    int X(){return mPos.mX;}
    void X(float x){mPos.mX = x;}
    int Y(){return mPos.mY;}
    void Y(float y){mPos.mY = y;}
    int Z(){return mPos.mZ;}
    void Z(float z){mPos.mZ = z;}
    
    Color GetColor(){return mColor;}
    void SetColor( Color color){mColor = color;}
};

#endif /* Point3d_h */
