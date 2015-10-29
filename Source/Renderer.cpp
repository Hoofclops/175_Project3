//
//  Renderer.cpp
//  Project1
//
//  Created by Brandon Nguyen on 9/26/15.
//  Copyright (c) 2015 Brandon Nguyen. All rights reserved.
//

#include "Renderer.h"

/****************************
 *STATIC VARIABLE DECLARATIONS*
 ****************************/

Renderer* Renderer::sInstance;
Vector2i Renderer::sScreenSize;
Vector2i Renderer::sSubwindowSize;
float*  Renderer::sPixelBuffer;
float*  Renderer::sPixelBuffer1;
float*  Renderer::sPixelBuffer2;
float*  Renderer::sPixelBuffer3;
int Renderer::sMainWindow;
int Renderer::sSubWindow1;
int Renderer::sSubWindow2;
int Renderer::sSubWindow3;
deque<function<void()>> Renderer::sAnimationQueue;


Renderer::Renderer()
{}

/****************************
 *PUBLIC FUNCTIONS*
 ****************************/

void Renderer::InitWindow(int xDim, int yDim)
{
    sScreenSize = Vector2i(xDim, yDim);
    sSubwindowSize = Vector2i(xDim/2, yDim/2);
    int windowPixelCount = (sScreenSize.mX) * (sScreenSize.mY) * 3;
    int subWindowPixelCount = windowPixelCount / 4;
    
    sPixelBuffer = new float[windowPixelCount];
    sPixelBuffer1 = new float[subWindowPixelCount];
    sPixelBuffer2 = new float[subWindowPixelCount];
    sPixelBuffer3 = new float[subWindowPixelCount];
    
    for(int i = 0; i < windowPixelCount; i++)
    {
        sPixelBuffer[i] = 0.0f;
        
        if(i < subWindowPixelCount)
        {
            sPixelBuffer1[i] = 0.55f;
            sPixelBuffer2[i] = 0.4f;
            sPixelBuffer3[i] = 0.25f;
        }
    }
}

void Renderer::DrawScene()
{
    ClearBuffer();
    
//    //Colorize quadrants
//    int windowPixelCount = (sScreenSize.mX) * (sScreenSize.mY) * 3;
//    int subWindowPixelCount = windowPixelCount / 4;
//    for(int i = 0; i < subWindowPixelCount; i++)
//    {
//        sPixelBuffer1[i] = 0.55f;
//        sPixelBuffer2[i] = 0.4f;
//        sPixelBuffer3[i] = 0.25f;
//    }
//    
    DrawPolygons();
    
    //Post redisplay for all sub windows
    glutSetWindow(sMainWindow);
    glutPostRedisplay();
    glutSetWindow(sSubWindow1);
    glutPostRedisplay();
    glutSetWindow(sSubWindow2);
    glutPostRedisplay();
    glutSetWindow(sSubWindow3);
    glutPostRedisplay();
}

//void Renderer::DrawLine(Line line, Algo algo, int subWindow)
//{
//    if(algo == DDA)
//    {
//        GraphicsAlgorithm::LineDDA(line, subWindow);
//    }
//    else if(algo == BRESENHAM)
//    {
//        GraphicsAlgorithm::LineBresenham(line, subWindow);
//    }
//}

void Renderer::DrawPoint(Point point, int subWindow)
{
    int pixelStart = PosToIndex((point.Position()));
    
    Color color = point.GetColor();
    
    if(pixelStart >= 0 && pixelStart + 2 <= (sSubwindowSize.mX) * (sSubwindowSize.mY) * 3)
    {
        if(subWindow == sSubWindow1)
        {
            sPixelBuffer1[pixelStart] = color.GetRed();
            sPixelBuffer1[pixelStart + 1] = color.GetGreen();
            sPixelBuffer1[pixelStart + 2] = color.GetBlue();
        }
        else if(subWindow == sSubWindow2)
        {
            sPixelBuffer2[pixelStart] = color.GetRed();
            sPixelBuffer2[pixelStart + 1] = color.GetGreen();
            sPixelBuffer2[pixelStart + 2] = color.GetBlue();

        }
        else if(subWindow == sSubWindow3)
        {
            sPixelBuffer3[pixelStart] = color.GetRed();
            sPixelBuffer3[pixelStart + 1] = color.GetGreen();
            sPixelBuffer3[pixelStart + 2] = color.GetBlue();

        }
    }
    else
    {
        throw out_of_range("Point outside of pixel buffer range");
    }
}

void Renderer::DisplayPixelBuffer()
{
    //Misc.
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();//load identity matrix
    
    //draws pixel on screen, width and height must match pixel buffer dimension
    glDrawPixels(sScreenSize.mX, sScreenSize.mY, GL_RGB, GL_FLOAT, sPixelBuffer);
    glEnd();
    glFlush();
}
void Renderer::DisplayPixelBuffer1()
{
    //Misc.
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();//load identity matrix
    
    //draws pixel on screen, width and height must match pixel buffer dimension
    glDrawPixels(sSubwindowSize.mX, sSubwindowSize.mY, GL_RGB, GL_FLOAT, sPixelBuffer1);
    glEnd();
    glFlush();
}
void Renderer::DisplayPixelBuffer2()
{
    //Misc.
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();//load identity matrix
    
    //draws pixel on screen, width and height must match pixel buffer dimension
    glDrawPixels(sSubwindowSize.mX, sSubwindowSize.mY, GL_RGB, GL_FLOAT, sPixelBuffer2);
    glEnd();
    glFlush();
}
void Renderer::DisplayPixelBuffer3()
{
    //Misc.
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();//load identity matrix
    
    //draws pixel on screen, width and height must match pixel buffer dimension
    glDrawPixels(sSubwindowSize.mX, sSubwindowSize.mY, GL_RGB, GL_FLOAT, sPixelBuffer3);
    glEnd();
    glFlush();
}

void Renderer::IdleAnimation()
{
    long n = sAnimationQueue.size();
    if(n != 0)
    {
        sAnimationQueue.front()();
        sAnimationQueue.pop_front();
        Renderer::Instance()->DrawScene();
    }
    
}

void Renderer::AnimateTranslate(Vector3 translationVector)
{
    ObjectEditor* editor = ObjectEditor::Instance();
    
    if(translationVector.mX != 0)
    {
        int xMax = abs(translationVector.mX);
        for(int i = 0; i < xMax; i = i + 5)
        {
            int x;
            if(translationVector.mX > 0) x = 5;
            else if(translationVector.mX < 0) x = -5;
            Vector3 vect = Vector3(x,0,0);
            sAnimationQueue.push_back([&editor,vect]{editor->TranslatePolygon(vect);});
        }
        
        int remainder = abs((int)translationVector.mX) % 5;
        if(remainder)
        {
            if(translationVector.mX < 0) remainder *= -1;
            Vector3 vect = Vector3(remainder,0,0);
            sAnimationQueue.push_back([&editor,vect]{editor->TranslatePolygon(vect);});
        }
    }

    
    if(translationVector.mY != 0)
    {
        int yMax = abs(translationVector.mY);
        for(int i = 0; i < yMax; i = i + 5)
        {
            int y;
            if(translationVector.mY > 0) y = 5;
            else if(translationVector.mY < 0) y = -5;
            Vector3 vect = Vector3(0,y,0);
            sAnimationQueue.push_back([&editor,vect]{editor->TranslatePolygon(vect);});
        }
        
        int remainder = abs((int)translationVector.mY) % 5;
        if(remainder)
        {
            if(translationVector.mY < 0) remainder *= -1;
            Vector3 vect = Vector3(0,remainder,0);
            sAnimationQueue.push_back([&editor,vect]{editor->TranslatePolygon(vect);});
        }

    }
    
    if(translationVector.mZ != 0)
    {
        int zMax = abs(translationVector.mZ);
        for(int i = 0; i < zMax; i = i + 5)
        {
            int z;
            if(translationVector.mZ > 0) z = 5;
            else if(translationVector.mZ < 0) z = -5;
            Vector3 vect = Vector3(0,0,z);
            sAnimationQueue.push_back([&editor,vect]{editor->TranslatePolygon(vect);});
        }
        
        int remainder = abs((int)translationVector.mZ) % 5;
        if(remainder)
        {
            if(translationVector.mZ < 0) remainder *= -1;
            Vector3 vect = Vector3(0,0,remainder);
            sAnimationQueue.push_back([&editor,vect]{editor->TranslatePolygon(vect);});
        }
    }
}

//void Renderer::AnimateScale(float xScale, float yScale, float zScale)
//{
////    double steps = 100;
////    
////    double incX = (double)xScale / steps;
////    double incY = (double)yScale / steps;
////    double incZ = (double)zScale / steps;
////    double x = 0, y = 0, z = 0;
////    ObjectEditor* editor = ObjectEditor::Instance();
////    
////    while(abs(x) < abs(xScale) || abs(y) < abs(yScale) || abs(z) < abs(zScale))
////    {
////        if(abs(x) < abs(xScale)) x+=incX;
////        if(abs(y) < abs(yScale)) y+=incY;
////        if(abs(z) < abs(zScale)) z+=incZ;
////        sAnimationQueue.push_back([&editor,incX,incY,incZ]{editor->ScalePolygon(incX, incY, incZ);});
////    }
//    
//    for(int i = 0; i < 20;i++)
//    {
//        
//    }
//}

void Renderer::AnimateRotation(float degree, Vector3 P1, Vector3 P2)
{
    ObjectEditor* editor = ObjectEditor::Instance();
    if(degree == 0)
    {
        return;
    }
    else if(degree > 0)
    {
        for(int i = 1; i <= degree; i++)
        {
            sAnimationQueue.push_back([&editor,i,P1,P2]{editor->RotatePolygon(1, P1, P2);});
        }
    }
    else
    {
        for(int i = -1; i >= degree ; i--)
        {
            sAnimationQueue.push_back([&editor,i,P1,P2]{editor->RotatePolygon(1, P1, P2);});
        }
    }
}

void Renderer::ClearBuffer()
{
    int n = sScreenSize.mX * sScreenSize.mY * 3;
    int m = n / 4;
    for(int i = 0; i < n; i++)
    {
        sPixelBuffer[i] = 0.0f;
        
        if(i < m)
        {
            sPixelBuffer1[i] = 0.55f;
            sPixelBuffer2[i] = 0.4f;
            sPixelBuffer3[i] = 0.25f;
        }
    }
}

/****************************
 *PRIVATE FUNCTIONS*
 ****************************/

int Renderer::PosToIndex(Vector2i pos)
{
    int width = sSubwindowSize.mX;
    return (pos.mX + width * pos.mY) * 3;
}

void Renderer::UpdateLimits(float* min, float* max, Point p)
{
    int x = p.X(), y = p.Y();
    if(x < *min)
        *min = x;
    if(y < *min)
        *min = y;
    if(x > *max)
        *max = x;
    if(y > *max)
        *max = y;
}

void Renderer::DrawPolygons()
{
    deque<Polygon> polys = ObjectEditor::Instance()->GetPolygons();
    deque<deque<Point>> verticesXY, verticesXZ, verticesYZ;
    bool axisInitialized = ObjectEditor::Instance()->sAxisInitialized;
    
    //Project all vertices
    long polyCount = polys.size();
    for(int i = 0; i < polyCount; i++)
    {
        verticesXY.push_back(Projector::AxonometricXY(polys[i].GetVertices()));
        verticesXZ.push_back(Projector::AxonometricXZ(polys[i].GetVertices()));
        verticesYZ.push_back(Projector::AxonometricYZ(polys[i].GetVertices()));
    }
    
    deque<Point> rotAxisXY;
    deque<Point> rotAxisXZ;
    deque<Point> rotAxisYZ;
    if(axisInitialized)
    {
        //Project rotation axis
        rotAxisXY = Projector::AxonometricXY(ObjectEditor::sRotationAxis.GetVertices());
        rotAxisXZ = Projector::AxonometricXZ(ObjectEditor::sRotationAxis.GetVertices());
        rotAxisYZ = Projector::AxonometricYZ(ObjectEditor::sRotationAxis.GetVertices());
    }
    
    //Find min and max points for each plane
    float minXY = numeric_limits<float>::max();
    float minXZ = numeric_limits<float>::max();
    float minYZ = numeric_limits<float>::max();
    float maxXY = 0;
    float maxXZ = 0;
    float maxYZ = 0;
    for(int i = 0; i < polyCount; i++)
    {
        long m = verticesXY[i].size();
        for(int j = 0; j < m; j++)
        {
            UpdateLimits(&minXY, &maxXY, verticesXY[i][j]);
            UpdateLimits(&minXZ, &maxXZ, verticesXZ[i][j]);
            UpdateLimits(&minYZ, &maxYZ, verticesYZ[i][j]);
        }
    }
    
    if(axisInitialized)
    {
        //Min and max rotation axis
        for(int i = 0; i < 2; i++)
        {
            UpdateLimits(&minXY, &maxXY, rotAxisXY[i]);
            UpdateLimits(&minXZ, &maxXZ, rotAxisXZ[i]);
            UpdateLimits(&minYZ, &maxYZ, rotAxisYZ[i]);
        }
    }

    bool axisDrawn = false;
    //Normalize and draw wire frames
    for(int i = 0; i < polyCount; i++)
    {
        //Normalize and project vertices
        MapToPlaneQuadrant(&verticesXY[i], XY, minXY, maxXY);
        MapToPlaneQuadrant(&verticesXZ[i], XZ, minXZ, maxXZ);
        MapToPlaneQuadrant(&verticesYZ[i], YZ, minYZ, maxYZ);
        
        if(axisInitialized && !axisDrawn)
        {
            MapToPlaneQuadrant(&rotAxisXY, XY, minXY, maxXY);
            MapToPlaneQuadrant(&rotAxisXZ, XZ, minXZ, maxXZ);
            MapToPlaneQuadrant(&rotAxisYZ, YZ, minYZ, maxYZ);
        }
        
        deque<Line> edgesXY = polys[i].GetEdges2d(verticesXY[i]);
        deque<Line> edgesXZ = polys[i].GetEdges2d(verticesXZ[i]);
        deque<Line> edgesYZ = polys[i].GetEdges2d(verticesYZ[i]);
        
        deque<Line> edgeRotAxisXY;
        deque<Line> edgeRotAxisXZ;
        deque<Line> edgeRotAxisYZ;
        if(axisInitialized)
        {
            edgeRotAxisXY = ObjectEditor::sRotationAxis.GetEdges2d(rotAxisXY);
            edgeRotAxisXZ = ObjectEditor::sRotationAxis.GetEdges2d(rotAxisXZ);
            edgeRotAxisYZ = ObjectEditor::sRotationAxis.GetEdges2d(rotAxisYZ);
        }
        
        //draw wire frame
        long edgesCount = edgesXY.size();
        for(int j = 0; j < edgesCount; j++)
        {
            if(polys[i].IsSelected())
            {
                GraphicsAlgorithm::LineDDA(edgesXY[j], Renderer::sSubWindow1, Color::Green());
                GraphicsAlgorithm::LineDDA(edgesXZ[j], Renderer::sSubWindow2, Color::Green());
                GraphicsAlgorithm::LineDDA(edgesYZ[j], Renderer::sSubWindow3, Color::Green());
            }
            else
            {
                GraphicsAlgorithm::LineDDA(edgesXY[j], Renderer::sSubWindow1, Color::White());
                GraphicsAlgorithm::LineDDA(edgesXZ[j], Renderer::sSubWindow2, Color::White());
                GraphicsAlgorithm::LineDDA(edgesYZ[j], Renderer::sSubWindow3, Color::White());
            }
        }
        
        if(axisInitialized && !axisDrawn)
        {
            //draw rotation axis
            GraphicsAlgorithm::LineDDA(edgeRotAxisXY[0], Renderer::sSubWindow1, Color::Blue());
            GraphicsAlgorithm::LineDDA(edgeRotAxisXZ[0], Renderer::sSubWindow2, Color::Blue());
            GraphicsAlgorithm::LineDDA(edgeRotAxisYZ[0], Renderer::sSubWindow3, Color::Blue());
            axisDrawn = true;
        }
    }
}

void Renderer::MapToPlaneQuadrant(deque<Point> *vertices, ProjectionPlane plane, float min, float max)
{
    deque<float> normX, normY;
    NormalizeVertices(*vertices, &normX, &normY, min, max);
    
    //Define quadrant
    Vector2i minQuad, maxQuad;
    minQuad.mX = 0;
    minQuad.mY = 0;
    maxQuad.mX = sSubwindowSize.mX - 1;
    maxQuad.mY = sSubwindowSize.mY - 1;
    
    //Map normalized values to quadrant
    long n = vertices->size();
    for(int i = 0; i < n; i++)
    {
        float zX = normX[i], zY = normY[i];
        int x, y;
        
        x = maxQuad.mX * zX;
        y = maxQuad.mY * zY;//minQuad.mY + (zY * (maxQuad.mY - minQuad.mY));
        
        vertices->at(i) = Point(x,y);
    }
}

void Renderer::NormalizeVertices(deque<Point> vertices, deque<float> *normX, deque<float> *normY, float min, float max)
{
    
    long n = vertices.size();
    //Find normalized points
    for(int i = 0; i < n; i++)
    {
        float x = vertices[i].X(), y = vertices[i].Y();
        
        x = (x - min) / (max - min);
        y = (y - min) / (max - min);
        
        if(x < 0 || x > 1 || y < 0 || y > 1)
        {
            throw exception();
        }
        
        normX->push_back(x);
        normY->push_back(y);
    }
}

