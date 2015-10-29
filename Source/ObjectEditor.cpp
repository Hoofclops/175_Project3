//
//  ObjectEditor.cpp
//  Project1
//
//  Created by Brandon Nguyen on 9/28/15.
//  Copyright (c) 2015 Brandon Nguyen. All rights reserved.
//

#include "ObjectEditor.h"

ObjectEditor* ObjectEditor::sInstance;
deque<Polygon> ObjectEditor::sPolyList;
deque<Line> ObjectEditor::sLineList;
int ObjectEditor::sSelectedPoly;
Vector2i ObjectEditor::sMinClip;
Vector2i ObjectEditor::sMaxClip;
Polygon ObjectEditor::sRotationAxis;
bool ObjectEditor::sAxisInitialized = false;

ObjectEditor::ObjectEditor()
{
    sSelectedPoly = -1;
    sMinClip = Vector2i(0,0);
    Vector2i screenSize = Renderer::Instance()->ScreenSize();
    sMaxClip = Vector2i(screenSize.mX, screenSize.mY);
}

void ObjectEditor::CreatePolygon(deque<Vector3> vertPositions, deque<Vector2i> edgeConnections)
{
    Polygon poly = Polygon(vertPositions, edgeConnections);
    sPolyList.push_back(poly);
}

void ObjectEditor::CreateLine(Line line)
{
    sLineList.push_back(line);
}

void ObjectEditor::TranslatePolygon(Vector3 translationVector)
{
    if(sSelectedPoly == -1)
        CycleSelectedPoly(true);
    
    unsigned int id = sSelectedPoly;
    if(id >= sPolyList.size())
    {
        throw invalid_argument("Invalid Polygon ID");
    }
       
    deque<Point3d> vertices = sPolyList[sSelectedPoly].GetVertices();
    
    long n = vertices.size();
    for(int i = 0; i < n; i++)
    {
        int x = vertices[i].X(), y = vertices[i].Y(), z = vertices[i].Z();
        x += translationVector.mX;
        y += translationVector.mY;
        z += translationVector.mZ;
        
        vertices[i].X(x);
        vertices[i].Y(y);
        vertices[i].Z(z);
    }
    sPolyList[sSelectedPoly].SetVertices(vertices);
}
void ObjectEditor::ScalePolygon(float scaleX, float scaleY, float scaleZ)
{
    if(sSelectedPoly == -1)
        CycleSelectedPoly(true);
    
    unsigned int id = sSelectedPoly;
    if(id >= sPolyList.size())
    {
        throw invalid_argument("Invalid Polygon ID");
    }
    
    Vector3i centroid = GraphicsAlgorithm::FindPolyCentroid(sPolyList[sSelectedPoly]);
    deque<Point3d> vertices = sPolyList[sSelectedPoly].GetVertices();
    
    long n = vertices.size();
    for(int i = 0; i < n; i++)
    {
        int x = vertices[i].X(), y = vertices[i].Y(), z = vertices[i].Z();
        x = (x * scaleX) + (centroid.mX * (1 - scaleX));
        y = (y * scaleY) + (centroid.mY * (1 - scaleY));
        z = (z * scaleZ) + (centroid.mZ * (1 - scaleZ));
        
        vertices[i].X(x);
        vertices[i].Y(y);
        vertices[i].Z(z);
    }
    sPolyList[sSelectedPoly].SetVertices(vertices);
}

void ObjectEditor::RotatePolygon(double degrees, Vector3 P1, Vector3 P2)
{
    if(sSelectedPoly == -1)
        CycleSelectedPoly(true);
    
    unsigned int id = sSelectedPoly;
    if(id >= sPolyList.size())
    {
        throw invalid_argument("Invalid Polygon ID");
    }
    
    //Initialize rotation axis
    deque<Vector3> verts;
    verts.push_back(P1);
    verts.push_back(P2);
    deque<Vector2i> connections;
    connections.push_back(Vector2i(1,2));
    sAxisInitialized = true;
    sRotationAxis = Polygon(verts, connections);
    
    Polygon poly = sPolyList[id];
    deque<Point3d> vertices = poly.GetVertices();
    long vertCount = vertices.size();
    double theta = degrees * (M_PI / 180);

    //STEP 1
    //translate the object so rotation axis passes through the coordinate origin    
    //Define Translation matrix
    deque<float> matDeque;
    matDeque.push_back(1);matDeque.push_back(0);matDeque.push_back(0);matDeque.push_back(-P1.mX);
    matDeque.push_back(0);matDeque.push_back(1);matDeque.push_back(0);matDeque.push_back(-P1.mY);
    matDeque.push_back(0);matDeque.push_back(0);matDeque.push_back(1);matDeque.push_back(-P1.mZ);
    matDeque.push_back(0);matDeque.push_back(0);matDeque.push_back(0);matDeque.push_back(1);
    Matrix transMat = Matrix(4,4, matDeque);
    
    P1 = transMat.MultiplyVector(P1);
    P2 = transMat.MultiplyVector(P2);
    for(unsigned int i = 0; i < vertCount; i++)
    {
        vertices[i] = Point3d(transMat.MultiplyVector((vertices[i].Pos())));
    }
    
    //STEP 2
    //rotate the object so that the axis of rotation coincides with one of the coordinate axis
    Vector3 V = P2.Subtract(P1); //Vector from P1 to P2
    float magV = V.GetMagnitude();
    Vector3 u = Vector3(V.mX / magV, V.mY / magV, V.mZ / magV);
    float x = u.mX, y = u.mY, z = u.mZ;
    float cosT = cos(theta);
    float sinT = sin(theta);
    
    matDeque.clear();
    matDeque.push_back((x*x)*(1-cosT) + cosT);
    matDeque.push_back((x*y)*(1-cosT) - (z*sinT));
    matDeque.push_back((x*z)*(1-cosT) + (y*sinT));
    matDeque.push_back(0);
    
    matDeque.push_back((y*x)*(1-cosT) + (z*sinT));
    matDeque.push_back((y*y)*(1-cosT) + (cosT));
    matDeque.push_back((y*z)*(1-cosT) - (x*sinT));
    matDeque.push_back(0);
    
    matDeque.push_back((z*x)*(1-cosT) - (y*sinT));
    matDeque.push_back((z*y)*(1-cosT) + (x*sinT));
    matDeque.push_back((z*z)*(1-cosT) + (cosT));
    matDeque.push_back(0);
    
    matDeque.push_back(0);
    matDeque.push_back(0);
    matDeque.push_back(0);
    matDeque.push_back(1);
    
    Matrix superMat = Matrix(4,4, matDeque);
    for(unsigned int i = 0; i < vertCount; i++)
    {
        vertices[i] = Point3d(superMat.MultiplyVector(vertices[i].Pos()));
    }

    //STEP 5
    //translate the rotation axis back to its original position
    Matrix invTransMat = Matrix(4,4);
    if(transMat.Invert4by4(&invTransMat))
    {
        for(unsigned int i = 0; i < vertCount; i++)
        {
            vertices[i] = Point3d(invTransMat.MultiplyVector((vertices[i].Pos())));
        }
    }
    else
    {
        throw exception();
    }

    sPolyList[id].SetVertices(vertices);
}

deque<Polygon> ObjectEditor::GetPolygons()
{
    return sPolyList;
}

deque<Line> ObjectEditor::GetLines()
{
    return sLineList;
}

Vector2i ObjectEditor::GetMinClip()
{
    return sMinClip;
}

Vector2i ObjectEditor::GetMaxClip()
{
    return sMaxClip;
}

void ObjectEditor::CycleSelectedPoly(bool forward)
{
    //Handle first selection
    if(sSelectedPoly == -1)
    {
        if(sPolyList.size() == 0)
            return;
        
        sSelectedPoly = 0;
        sPolyList[sSelectedPoly].SetSelected(true);
        return;
    }
    
    if(forward)
    {
        sPolyList[sSelectedPoly].SetSelected(false);
        unsigned int selectedUnsigned = sSelectedPoly;
        if(selectedUnsigned != sPolyList.size() - 1)
        {
            sSelectedPoly++;
        }
        else
        {
            sSelectedPoly = 0;
        }
        sPolyList[sSelectedPoly].SetSelected(true);
    }
    else
    {
        sPolyList[sSelectedPoly].SetSelected(false);
        if(sSelectedPoly != 0)
        {
            sSelectedPoly--;
        }
        else
        {
            sSelectedPoly = (int)(sPolyList.size() - 1);
        }
        sPolyList[sSelectedPoly].SetSelected(true);

    }
}

void ObjectEditor::ClearData()
{
    sPolyList.clear();
    sLineList.clear();
    sSelectedPoly = -1;
    sAxisInitialized = false;
}

void ObjectEditor::ClipScene(deque<Line> *clippedLines, deque<Polygon> *clippedPolys)
{
//    long n = sLineList.size();
//    for(unsigned int i = 0; i < n; i++)
//    {
//        Line l = sLineList[i];
//        GraphicsAlgorithm::LineClipCohenSutherland(sMinClip, sMaxClip, &l);
//        clippedLines->push_back(l);
//    }
//    
//    n = sPolyList.size();
//    for(unsigned int i = 0 ; i < n; i++)
//    {
//        Vector2i *pOut;
//        pOut = new Vector2i[100];
//        int count = GraphicsAlgorithm::PolygonClipSutherlandHodgman(sMinClip, sMaxClip, sPolyList[i], pOut);
//        
//        deque<Vector2i> vertices;
//        for(int i = 0; i < count; i++)
//        {
//            Vector2i v = Vector2i(pOut[i].mX, pOut[i].mY);
//            vertices.push_back(v);
//        }
//        Polygon p = Polygon(vertices);
//        
//        if(sPolyList[i].IsSelected())
//            p.SetSelected(true);
//        clippedPolys->push_back(p);
//    }
}

void ObjectEditor::SetClip(Vector2i minClip, Vector2i maxClip)
{    
    sMinClip = minClip;
    sMaxClip = maxClip;
}

