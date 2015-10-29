//
//  Vector3.h
//  Project1
//
//  Created by Brandon Nguyen on 9/25/15.
//  Copyright (c) 2015 Brandon Nguyen. All rights reserved.
//

#ifndef __Project1__Vector3__
#define __Project1__Vector3__

#include <cmath>

class Vector3
{
public:
    float mX;
    float mY;
    float mZ;
    
    Vector3();
    Vector3(float x, float y, float z);
    Vector3 Add(Vector3 other);
    Vector3 Subtract(Vector3 other);
    Vector3 Multiply(Vector3 other);
    
    float GetMagnitude()
    {
        return sqrt((mX * mX) + (mY * mY) + (mZ * mZ));
    }
    
    float Dot(Vector3 other)
    {
        return (mX * other.mX) + (mY * other.mY) + (mZ * other.mZ);
    }
    
    Vector3 Cross(Vector3 other)
    {
        float cX = (mY * other.mZ) - (mZ * other.mY);
        float cY = (mZ * other.mX) - (mX * other.mZ);
        float cZ = (mX * other.mY) - (mY * other.mX);
        return Vector3(cX, cY, cZ);
    }
};

#endif /* defined(__Project1__Vector3__) */
