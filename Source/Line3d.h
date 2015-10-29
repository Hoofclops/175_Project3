//
//  Line3d.h
//  Source
//
//  Created by Brandon Nguyen on 10/14/15.
//  Copyright © 2015 Brandon Nguyen. All rights reserved.
//

#ifndef Line3d_h
#define Line3d_h

#include "Point3d.h"

class Line3d
{
private:
    Point3d mA;
    Point3d mB;
    
public:
    Line3d();
    Line3d(Point3d a, Point3d b);
    
    Point3d A(){return mA;}
    void A(Point3d a){mA = a;}
    Point3d B(){return mB;}
    void B(Point3d b){mB = b;}
};


#endif /* Line3d_h */
