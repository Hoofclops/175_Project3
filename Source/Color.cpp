//
//  Color.cpp
//  Project1
//
//  Created by Brandon Nguyen on 9/26/15.
//  Copyright (c) 2015 Brandon Nguyen. All rights reserved.
//

#include "Color.h"

Color::Color()
{
    mRGB = Vector3(1,1,1);
}

Color::Color(Vector3 color)
{
    if(IsValidRGB(color))
        mRGB = color;
}

Color::Color(float r, float g, float b)
{
    Vector3 color = Vector3(r,g,b);
    if(IsValidRGB(color))
        mRGB = color;
}

void Color::SetRGB(float r, float g, float b)
{
    Vector3 color = Vector3(r,g,b);
    if(IsValidRGB(color))
        mRGB = color;
}

void Color::SetRGB(Vector3 color)
{
    if(IsValidRGB(color))
        mRGB = color;
}

float Color::GetRed()
{
    return mRGB.mX;
}

float Color::GetGreen()
{
    return mRGB.mY;
}

float Color::GetBlue()
{
    return mRGB.mZ;
}