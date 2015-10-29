//
//  Vector2i.cpp
//  Project1
//
//  Created by Brandon Nguyen on 9/26/15.
//  Copyright (c) 2015 Brandon Nguyen. All rights reserved.
//

#include "Vector2i.h"

Vector2i::Vector2i()
{
    mX = 0;
    mY = 0;
}

Vector2i::Vector2i(int x, int y)
{
    mX = x;
    mY = y;
}

void Vector2i::Add(Vector2i other)
{
    this->mX += other.mX;
    this->mY += other.mY;
}

void Vector2i::Subtract(Vector2i other)
{
    this->mX -= other.mX;
    this->mY -= other.mY;
}

void Vector2i::Multiply(Vector2i other)
{
    this->mX *= other.mX;
    this->mY *= other.mY;
}