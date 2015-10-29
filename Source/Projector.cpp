//
//  Projector.cpp
//  Source
//
//  Created by Brandon Nguyen on 10/14/15.
//  Copyright © 2015 Brandon Nguyen. All rights reserved.
//

#include "Projector.h"
deque <Point> Projector::AxonometricXY(deque <Point3d> vertices)
{
    deque <Point> ret;
    long n = vertices.size();
    for(int i = 0; i < n; i++)
    {
        Point p = Point(Vector2i(vertices[i].X(), vertices[i].Y()));
        ret.push_back(p);
    }
    
    return ret;
}

deque <Point> Projector::AxonometricXZ(deque <Point3d> vertices)
{
    deque <Point> ret;
    long n = vertices.size();
    for(int i = 0; i < n; i++)
    {
        Point p = Point(Vector2i(vertices[i].X(), vertices[i].Z()));
        ret.push_back(p);
    }
    
    return ret;
}

deque <Point> Projector::AxonometricYZ(deque <Point3d> vertices)
{
    deque <Point> ret;
    long n = vertices.size();
    for(int i = 0; i < n; i++)
    {
        Point p = Point(Vector2i(vertices[i].Y(), vertices[i].Z()));
        ret.push_back(p);
    }
    
    return ret;
}
