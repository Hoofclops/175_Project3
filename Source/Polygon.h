//
//  Polygon.h
//  Project1
//
//  Created by Brandon Nguyen on 9/26/15.
//  Copyright (c) 2015 Brandon Nguyen. All rights reserved.
//

#ifndef __Project1__Polygon__
#define __Project1__Polygon__

#include <deque>
#include <list>
#include <stdexcept>
#include <iostream>
#include "Point3d.h"
#include "Point.h"
#include "Line.h"
#include "Line3d.h"
#include "Vector3.h"
#include "Vector2i.h"

class Polygon
{
private:
    //deque to maintain stable references between edges and vertices
    deque<Point3d> mVertices;
    deque<Vector2i> mEdgeConnections;
    bool mSelected;
    
public:
    Polygon();
    Polygon(deque<Vector3> vertPositions, deque<Vector2i> edgeConnections);
    
    deque<Point3d> GetVertices();
    void SetVertex(int index, Vector3 pos);
    void SetVertices(deque<Point3d> verts);

    deque<Line3d> GetEdges();
    deque<Line> GetEdges2d(deque<Point> vertices);
    deque<Vector2i> GetEdgeConnections(){return mEdgeConnections;}
    
    void SetSelected(bool isSelected);
    bool IsSelected();
};
#endif /* defined(__Project1__Polygon__) */
