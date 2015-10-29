//
//  Line3d.cpp
//  Source
//
//  Created by Brandon Nguyen on 10/14/15.
//  Copyright © 2015 Brandon Nguyen. All rights reserved.
//

#include "Line3d.h"

Line3d::Line3d(){}
Line3d::Line3d(Point3d a, Point3d b)
{
    mA = a;
    mB = b;
}