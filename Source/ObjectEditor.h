//
//  ObjectEditor.h
//  Project1
//
//  Created by Brandon Nguyen on 9/28/15.
//  Copyright (c) 2015 Brandon Nguyen. All rights reserved.
//

#ifndef __Project1__ObjectEditor__
#define __Project1__ObjectEditor__

#include <deque>
#include <math.h>
#include <exception>
#include <iostream>
#include "Polygon.h"
#include "Line.h"
#include "Renderer.h"
#include "Vector2i.h"
#include "Vector3.h"
#include "Matrix.h"
class ObjectEditor
{
private:
    static ObjectEditor* sInstance;
    static deque<Polygon> sPolyList;
    static deque<Line> sLineList;
    static int sSelectedPoly;
    static Vector2i sMinClip;
    static Vector2i sMaxClip;
    
    ObjectEditor();
public:
    static ObjectEditor *Instance()
    {
        if (!sInstance)
            sInstance = new ObjectEditor;
        return sInstance;
    }
    static Polygon sRotationAxis;
    static bool sAxisInitialized;

    
    void CreatePolygon(deque<Vector3> vertPositions, deque<Vector2i> edgeConnections);
    void CreateLine(Line line);
    
    void TranslatePolygon(Vector3 translationVector);
    void ScalePolygon(float scaleX, float scaleY, float scaleZ);
    void RotatePolygon(double degrees, Vector3 P1, Vector3 P2);

    deque<Polygon> GetPolygons();
    deque<Line> GetLines();
    Vector2i GetMinClip();
    Vector2i GetMaxClip();
        
    void CycleSelectedPoly(bool forward);
    void ClearData();
    void ClipScene(deque<Line> *clippedLines, deque<Polygon> *clippedPolys);
    void SetClip(Vector2i minClip, Vector2i maxClip);
};
#endif /* defined(__Project1__ObjectEditor__) */
