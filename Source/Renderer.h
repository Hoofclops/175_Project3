//
//  Renderer.h
//  Project1
//
//  Created by Brandon Nguyen on 9/26/15.
//  Copyright (c) 2015 Brandon Nguyen. All rights reserved.
//

#ifndef __Project1__Renderer__
#define __Project1__Renderer__

#define CANVAS_RED 0
#define CANVAS_GREEN 0
#define CANVAS_BLUE 0

 #include <OpenGL/gl.h>
 #include <OpenGL/glu.h>
 #include <GLUT/glut.h>
//#include <GL/glut.h>
#include <limits>
#include <string>
#include <deque>
#include <cmath>
#include <functional>
#include "Vector2i.h"
#include "Vector3.h"
#include "Color.h"
#include "Polygon.h"
#include "GraphicsAlgorithm.h"
#include "ObjectEditor.h"
#include "Projector.h"
#include "Line3d.h"

using namespace std;

//Should contain the pixel buffer and handle drawing of points, lines, and polygons
class Renderer
{
public:
    
    static int sMainWindow, sSubWindow1, sSubWindow2, sSubWindow3;
    static std::deque<std::function<void()>> sAnimationQueue;

    enum Algo
    {
        DDA,
        BRESENHAM,
    };
    
    enum ProjectionPlane
    {
        XY,
        XZ,
        YZ,
    };
    
    static Renderer* Instance()
    {
        if (!sInstance)
            sInstance = new Renderer;
        return sInstance;
    }
    
    void InitWindow(int xDim, int yDim);
    
    Vector2i ScreenSize(){return sScreenSize;};
    void ScreenSize(Vector2i size){sScreenSize = size;}
    
    void DrawScene();
//    void DrawLine(Line line, Algo algo, int subWindow);
    void DrawPoint(Point point, int subWindow);

    static void DisplayPixelBuffer();
    static void DisplayPixelBuffer1();
    static void DisplayPixelBuffer2();
    static void DisplayPixelBuffer3();
    
    static void IdleAnimation();
    static void AnimateTranslate(Vector3 translationVector);
//    static void AnimateScale(float xScale, float yScale, float zScale);
    static void AnimateRotation(float degree, Vector3 P1, Vector3 P2);
    
    void ClearBuffer();
    
private:
    static Renderer* sInstance;
    static Vector2i  sScreenSize;
    static Vector2i sSubwindowSize;
    static float* sPixelBuffer;
    static float* sPixelBuffer1;
    static float* sPixelBuffer2;
    static float* sPixelBuffer3;
    
    Renderer();
    
    //Convert coordinate position to appropriate array index in pixel buffer
    int PosToIndex(Vector2i pos);
    
    void DrawPolygons();
    void UpdateLimits(float* min, float* max, Point p);
    void MapToPlaneQuadrant(deque<Point> *vertices, ProjectionPlane plane, float min, float max);
    void NormalizeVertices(deque<Point> vertices, deque<float> *normX, deque<float> *normY, float min, float max);
    
};

#endif /* defined(__Project1__Renderer__) */
