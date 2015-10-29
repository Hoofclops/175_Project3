//
//  Point3d.cpp
//  Source
//
//  Created by Brandon Nguyen on 10/14/15.
//  Copyright © 2015 Brandon Nguyen. All rights reserved.
//

#include "Point3d.h"
Point3d::Point3d(){}

Point3d::Point3d(Vector3 pos)
{
    mPos = pos;
}

Point3d::Point3d(Vector3 pos, Color color)
{
    mPos = pos;
    mColor = color;
}

Point3d::Point3d(float x, float y, float z)
{
    mPos.mX = x;
    mPos.mY = y;
    mPos.mZ = z;
}

Point3d::Point3d(float x, float y, float z, Color color)
{
    mPos.mX = x;
    mPos.mY = y;
    mPos.mZ = z;
    mColor = color;
}