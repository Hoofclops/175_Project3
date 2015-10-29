//
//  Polygon.cpp
//  Project1
//
//  Created by Brandon Nguyen on 9/26/15.
//  Copyright (c) 2015 Brandon Nguyen. All rights reserved.
//

#include "Polygon.h"

Polygon::Polygon()
{
    deque<Vector2i> edgeConnections;
    edgeConnections.push_back(Vector2i(1,2));
    
    deque<Vector3> vertPositions;
    vertPositions.push_back(Vector3(0,0,0));
    vertPositions.push_back(Vector3(0,0,0));
    
    long n = vertPositions.size();
    long m = edgeConnections.size();
    if(n <= 0 || m <= 0)
    {
        throw invalid_argument("Invalid amount of vertices or edges passed to Polygon constructor");
    }
    
    //Construct vertices
    Point3d first = Point3d(vertPositions[0]);
    mVertices.push_back(first);
    for(int i = 1; i < n; i++)
    {
        Point3d p = Point3d(vertPositions[i]);
        mVertices.push_back(p);
    }
    
    //Stor edge connections
    mEdgeConnections = edgeConnections;
}

Polygon::Polygon(deque<Vector3> vertPositions, deque<Vector2i> edgeConnections)
{
    long n = vertPositions.size();
    long m = edgeConnections.size();
    if(n <= 0 || m <= 0)
    {
        throw invalid_argument("Invalid amount of vertices or edges passed to Polygon constructor");
    }
    
    //Construct vertices
    Point3d first = Point3d(vertPositions[0]);
    mVertices.push_back(first);
    for(int i = 1; i < n; i++)
    {
        Point3d p = Point3d(vertPositions[i]);
        mVertices.push_back(p);
    }
    
    //Stor edge connections
    mEdgeConnections = edgeConnections;
    
    mSelected = false;
}

deque<Point3d> Polygon::GetVertices()
{
    return mVertices;
}
void Polygon::SetVertex(int index, Vector3 pos)
{
    mVertices[index].X(pos.mX);
    mVertices[index].Y(pos.mY);
    mVertices[index].Z(pos.mZ);
}

void Polygon::SetVertices(deque<Point3d> verts)
{
    mVertices = verts;
}

deque<Line3d> Polygon::GetEdges()
{
    //TODO: Check Next() pointers to see if they get messed up by transformations
    
    deque<Line3d> edges;
    
    long n = mEdgeConnections.size();
    for(int i = 0; i < n; i++)
    {
        int index1 = mEdgeConnections[i].mX, index2 = mEdgeConnections[i].mY;
        Line3d l = Line3d(mVertices[index1], mVertices[index2]);
        edges.push_back(l);
    }
    return edges;
}

deque<Line> Polygon::GetEdges2d(deque<Point> vertices)
{
    deque<Line> edges;
    long n = mEdgeConnections.size();
    for(int i = 0; i < n; i++)
    {
        int index1 = mEdgeConnections[i].mX, index2 = mEdgeConnections[i].mY;
        Line l = Line(vertices[index1], vertices[index2]);
        edges.push_back(l);
    }
    return edges;
}


void Polygon::SetSelected(bool isSelected)
{
    mSelected = isSelected;
}

bool Polygon::IsSelected()
{
    return mSelected;
}
