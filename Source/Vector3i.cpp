//
//  Vector3i.cpp
//  Source
//
//  Created by Brandon Nguyen on 10/14/15.
//  Copyright © 2015 Brandon Nguyen. All rights reserved.
//

#include "Vector3i.h"

Vector3i::Vector3i()
{
    mX = 0;
    mY = 0;
    mZ = 0;
}

Vector3i::Vector3i(int x, int y, int z)
{
    mX = x;
    mY = y;
    mZ = z;
}

void Vector3i::Add(Vector3i other)
{
    this->mX += other.mX;
    this->mY += other.mY;
    this->mZ += other.mZ;
}

void Vector3i::Subtract(Vector3i other)
{
    this->mX -= other.mX;
    this->mY -= other.mY;
    this->mZ -= other.mZ;
}

void Vector3i::Multiply(Vector3i other)
{
    this->mX *= other.mX;
    this->mY *= other.mY;
    this->mZ *= other.mZ;
}