//
//  Vector3.cpp
//  Project1
//
//  Created by Brandon Nguyen on 9/25/15.
//  Copyright (c) 2015 Brandon Nguyen. All rights reserved.
//

#include "Vector3.h"

Vector3::Vector3()
{
    mX = 0;
    mY = 0;
    mZ = 0;
}

Vector3::Vector3(float x, float y, float z)
{
    mX = x;
    mY = y;
    mZ = z;
}

Vector3 Vector3::Add(Vector3 other)
{
    Vector3 ret;
    ret.mX = mX + other.mX;
    ret.mY = mY + other.mY;
    ret.mZ = mZ + other.mZ;
    return ret;
}

Vector3 Vector3::Subtract(Vector3 other)
{
    Vector3 ret;
    ret.mX = mX - other.mX;
    ret.mY = mY - other.mY;
    ret.mZ = mZ - other.mZ;
    return ret;
}

Vector3 Vector3::Multiply(Vector3 other)
{
    Vector3 ret;
    ret.mX = mX * other.mX;
    ret.mY = mY * other.mY;
    ret.mZ = mZ * other.mZ;
    return ret;

}

