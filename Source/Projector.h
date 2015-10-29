//
//  Projector.h
//  Source
//
//  Created by Brandon Nguyen on 10/14/15.
//  Copyright © 2015 Brandon Nguyen. All rights reserved.
//

#ifndef Projector_h
#define Projector_h

#include "Point.h"
#include "Point3d.h"
#include <deque>

class Projector
{
public:
    static deque <Point> AxonometricXY(deque <Point3d> vertices);
    static deque <Point> AxonometricXZ(deque <Point3d> vertices);
    static deque <Point> AxonometricYZ(deque <Point3d> vertices);
};

#endif /* Projector_h */
