//
//  Color.h
//  Project1
//
//  Created by Brandon Nguyen on 9/26/15.
//  Copyright (c) 2015 Brandon Nguyen. All rights reserved.
//

#ifndef __Project1__Color__
#define __Project1__Color__

#include "Vector3.h"
#include <stdexcept>
using namespace std;

class Color
{
private:
    Vector3 mRGB;
    
    //Ensures vector3 values between 0 and 1 inclusive
    bool IsValidRGB(Vector3 color)
    {
        if((color.mX >= 0 && color.mX <= 1) &&
           (color.mY >= 0 && color.mY <= 1) &&
           (color.mZ >= 0 && color.mZ <= 1))
        {
            return true;
        }
        else
        {
            throw invalid_argument("RGB values not valid");
        }
    }
    
public:
    Color();
    Color(Vector3 color);
    Color(float r, float g, float b);
    
    static Color White(){return Color(1,1,1);}
    static Color Green(){return Color(0.4, 1, 0.4);}
    static Color Red(){return Color(1, 0.4, 0.4);}
    static Color Blue(){return Color(0.4, 0.7, 1);}
    
    void SetRGB(float r, float g, float b);
    void SetRGB(Vector3 color);
    
    float GetRed();
    float GetGreen();
    float GetBlue();
};
#endif /* defined(__Project1__Color__) */
