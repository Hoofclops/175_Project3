//
//  GraphicsAlgorithm.cpp
//  Project1
//
//  Created by Brandon Nguyen on 9/27/15.
//  Copyright (c) 2015 Brandon Nguyen. All rights reserved.
//
//  Works Cited:
//  Code for DDA algorithm based off of text book pages: 140
//  Code for Bresenham algorithm based off of text book pages: 143-144
//  Code for Cohen Sutherland algorithm based off of text book pages: 255-256
//  Code for Sutherland Hodgman algorithm based off of text book pages: 267-269
//  Scan Line Algorithm based off of one described on http://www.cs.rit.edu/~icss571/filling/index.html
//  Centroid algorithm based off of http://stackoverflow.com/questions/2792443/finding-the-centroid-of-a-polygon described at https://en.wikipedia.org/wiki/Centroid#Centroid_of_polygon

#include "GraphicsAlgorithm.h"

/****************************
 *BRESENHAM HELPER FUNCTIONS*
 ****************************/
int GraphicsAlgorithm::DetermineCase(float dy, float dx)
{
    float m;
    
    if(dx == 0)
    {
        return 1;
    }
    
    m = dy / dx;
    if(m == 0 || m == 1 || m == -1)
    {
        return 1;
    }
    else if(m > 0)
    {
        return 2;
    }
    else
    {
        return 3;
    }
}

void GraphicsAlgorithm::HandlePositiveSlope(Point a, Point b, int dx, int dy, int subWindow)
{
    int x = a.X(), xEnd = b.X(), y = a.Y(), yEnd = b.Y();
    int p = 2 * dy - dx;
    float m = (float)dy / (float)dx;
    
    //Draw starting point
    Renderer::Instance()->DrawPoint(Point(x,y), subWindow);
    
    if(m < 1)
    {
        int twoDy = 2 * dy, twoDyMinusDx = 2 * (dy - dx);
        //increment in x direction
        while(x < xEnd)
        {
            x++;
            if(p < 0)
            {
                p += twoDy;
            }
            else
            {
                y++;
                p += twoDyMinusDx;
            }
            Renderer::Instance()->DrawPoint(Point(x,y), subWindow);
        }
    }
    else //flip x and y roles if m > 1
    {
        int twoDx = 2 * dx, twoDxMinusDy = 2 * (dx - dy);
        //increment in y direction
        while(y < yEnd)
        {
            y++;
            if(p < 0)
            {
                p += twoDx;
            }
            else
            {
                x++;
                p += twoDxMinusDy;
            }
            Renderer::Instance()->DrawPoint(Point(x,y), subWindow);
        }
    }
}

void GraphicsAlgorithm::HandleNegativeSlope(Point a, Point b, int dx, int dy, int subWindow)
{
    int x = a.X(), xEnd = b.X(), y = a.Y(), yEnd = b.Y();
    
    //get absolute values so p is calculated correctly
    dy = fabs(dy);
    dx = fabs(dx);
    
    int p = 2 * dy - dx;
    float m = (float)dy / (float)dx;
    
    //Draw starting point
    Renderer::Instance()->DrawPoint(Point(x,y), subWindow);
    
    if(m < 1)
    {
        int twoDy = 2 * dy, twoDyMinusDx = 2 * (dy - dx);
        //increment in x direction
        while(x < xEnd)
        {
            x++;
            if(p < 0)
            {
                p += twoDy;
            }
            else
            {
                y--;
                p += twoDyMinusDx;
            }
            Renderer::Instance()->DrawPoint(Point(x,y), subWindow);
        }
    }
    else
    {
        int twoDx = 2 * dx, twoDxMinusDy = 2 * (dx - dy);
        //increment in y direction
        while(y > yEnd)
        {
            y--;
            if(p < 0)
            {
                p += twoDx;
            }
            else
            {
                x++;
                p += twoDxMinusDy;
            }
            Renderer::Instance()->DrawPoint(Point(x,y), subWindow);
        }
    }
}

/*******************
 *SCAN LINE HELPERS*
 *******************/

bool GraphicsAlgorithm::InitScanLineValues(Line line, ScanData* data)
{
    int yMin, yMax;
    float xVal, inverseSlope;
    int x1 = line.A().X(), y1 = line.A().Y(),
        x2 = line.B().X(), y2 = line.B().Y();
    
    //Fill y values
    if(y1 == y2)
    {
        //dont fill values if horizontal line
        return false;
    }
    else if(y2 > y1)
    {
        yMax = y2;
        yMin = y1;
        xVal = x1;
    }
    else
    {
        yMax = y1;
        yMin = y2;
        xVal = x2;
    }

    //Find inverse slope
    inverseSlope = ((float)(x2 - x1)) / ((float)(y2 - y1));
    
    //fill values
    data->yMin = yMin;
    data->yMax = yMax;
    data->xVal = xVal;
    data->inverseSlope = inverseSlope;
    return true;
}

void GraphicsAlgorithm::FillRemainingEdges(deque<Line> edges, list<ScanData> * remainingEdges)
{
    //add first valid edge to remainingEdges
    bool foundFirst = false;
    while(!foundFirst)
    {
        ScanData data;
        if(InitScanLineValues(edges[0], &data))
        {
            foundFirst = true;
            remainingEdges->push_back(data);
        }
        edges.pop_front();
    }
    
    //Add and sort the rest to remainingEdges
    while(edges.size() != 0)
    {
        ScanData data;
        if(InitScanLineValues(edges[0], &data))
        {
            //valid, non horiontal line, find where to insert
            list<ScanData>::iterator iter = remainingEdges->begin();
            for(unsigned int i = 0; i <= edges.size(); i++)
            {
                
                //When we've reached end of list
                if(i == remainingEdges->size() || i == edges.size())
                {
                    remainingEdges->insert(iter, data);
                    break;
                }
                
                float yMinCur = iter->yMin,
                xValCur = iter->xVal;
                
                if(data.yMin > yMinCur ||
                   (data.yMin == yMinCur &&
                    data.xVal > xValCur))
                {
                    iter++;
                }
                else
                {
                    remainingEdges->insert(iter, data);
                    break;
                }
            }
        }
        
        edges.pop_front();
    }
}

bool GraphicsAlgorithm::SortActiveEdges(const ScanData first, const ScanData second)
{
    //sort by xVal
    return first.xVal < second.xVal;
}

void GraphicsAlgorithm::DrawScanLine(int curY, list<ScanData> activeEdges, int subWindow, bool drawGreen)
{
    Color color = Color(1,1,1);
    if(drawGreen)
    {
        color = Color(0.24f,.9,0.24f);
    }

    
    int curX = activeEdges.front().xVal;
    long totIntersections = activeEdges.size();
    int curIntersections = 0;
    bool parity = true;
    
    
    while(curIntersections != totIntersections)
    {
        //count intersections
        int intersected = 0;
        for(list<ScanData>::iterator it = activeEdges.begin(); it != activeEdges.end(); it++)
        {
            int xInt = (int)(it->xVal + 0.5f); // cast to int
            if(xInt == curX)
                intersected++;
        }
        
        //for each hit intersection: flip parity, increment curIntersections and it
        for(int i = 0; i < intersected; i++)
        {
            parity = !parity;
            
            if(!parity)
            {
                Point p = Point(curX, curY, color);
                Renderer::Instance()->DrawPoint(p, subWindow);
            }
            
            curIntersections++;
        }
        
        if(intersected == 0)
        {
            if(!parity)
            {
                Point p = Point(curX, curY, color);
                Renderer::Instance()->DrawPoint(p, subWindow);
            }
        }
        
        curX++;
    }
}

/**************************
 *COHEN SUTHERLAND HELPERS*
 **************************/

GLint GraphicsAlgorithm::Inside(GLint code)
{
    return GLint(!code);
}

GLint GraphicsAlgorithm::Reject(GLint code1, GLint code2)
{
    return GLint(code1 & code2);
}

GLint GraphicsAlgorithm::Accept(GLint code1, GLint code2)
{
    return GLint(!(code1 | code2));
}

GLubyte GraphicsAlgorithm::Encode(Point point, Vector2i minClip, Vector2i maxClip)
{
    GLubyte code = 0x00;
    
    if(point.X() < minClip.mX)
    {
        code = code | sBitCodeLeft;
    }
    if(point.X() > maxClip.mX)
    {
        code = code | sBitCodeRight;
    }
    if(point.Y() < minClip.mY)
    {
        code = code | sBitCodeBottom;
    }
    if(point.Y() > maxClip.mY)
    {
        code = code | sBitCodeTop;
    }
    
    return (code);
}

void GraphicsAlgorithm::SwapPoints(Point *p1, Point *p2)
{
    Point tmp;
    tmp = *p1;
    *p1 = *p2;
    *p2 = tmp;
}

void GraphicsAlgorithm::SwapCodes(GLubyte *c1, GLubyte *c2)
{
    GLubyte tmp;
    tmp = *c1;
    *c1 = *c2;
    *c2 = tmp;
}

/**************************
 *SUTHERLAND HODGMAN HELPERS*
 **************************/

GLint GraphicsAlgorithm::InsidePoly(Vector2i p, Boundary b, Vector2i minClip, Vector2i maxClip)
{
    switch(b)
    {
        case Left:
            if(p.mX < minClip.mX) return false;
            break;
        case Right:
            if(p.mX > maxClip.mX) return false;
            break;
        case Bottom:
            if(p.mY < minClip.mY) return false;
            break;
        case Top:
            if(p.mY > maxClip.mY) return false;
            break;
    }
    
    return true;
}

GLint GraphicsAlgorithm::Cross(Vector2i p1, Vector2i p2, Boundary winEdge, Vector2i minClip, Vector2i maxClip)
{
    if(InsidePoly(p1, winEdge, minClip, maxClip) == InsidePoly(p2, winEdge, minClip, maxClip))
        return false;
    else
        return true;
}

Vector2i GraphicsAlgorithm::Intersect(Vector2i p1, Vector2i p2, Boundary winEdge, Vector2i minClip, Vector2i maxClip)
{
    Vector2i iPt;
    float m = 0;
    
    if(p1.mX != p2.mX) m = ((float)(p1.mY - p2.mY)) / ((float)(p1.mX - p2.mX));
    switch(winEdge)
    {
        case Left:
            iPt.mX = minClip.mX;
            iPt.mY = p2.mY + (minClip.mX - p2.mX) * m;
            break;
        case Right:
            iPt.mX = maxClip.mX;
            iPt.mY = p2.mY + (maxClip.mX - p2.mX) * m;
            break;
        case Bottom:
            iPt.mY = minClip.mY;
            if(p1.mX != p2.mX) iPt.mX = p2.mX + (minClip.mY - p2.mY) / m;
            else iPt.mX = p2.mX;
            break;
        case Top:
            iPt.mY = maxClip.mY;
            if(p1.mX != p2.mX) iPt.mX = p2.mX + (maxClip.mY - p2.mY) / m;
            else iPt.mX = p2.mX;
            break;
    }
    
    return iPt;
}

void GraphicsAlgorithm::ClipPoint(Vector2i p, Boundary winEdge, Vector2i minClip, Vector2i maxClip, Vector2i *pOut, int *cnt, deque<Vector2i> *first, Vector2i *s)
{
    Vector2i iPt;
    if(first->size() == (int)winEdge)
    {
        first->push_back(p);
    }
    else
    {
        if(Cross(p, s[winEdge], winEdge, minClip, maxClip))
        {
            iPt = Intersect(p, s[winEdge], winEdge, minClip, maxClip);
            if(winEdge < Top)
            {
                ClipPoint(iPt, (Boundary)(((int)winEdge)+1), minClip, maxClip, pOut, cnt, first, s);
            }
            else
            {
                pOut[*cnt] = iPt;
                (*cnt)++;
            }
        }
    }
    
    s[winEdge] = p;
    
    if(InsidePoly(p, winEdge, minClip, maxClip))
    {
        if(winEdge < Top)
        {
            ClipPoint(p, (Boundary)(((int)winEdge)+1), minClip, maxClip, pOut, cnt, first, s);
        }
        else
        {
            pOut[*cnt] = p;
            (*cnt)++;
        }
    }
}

void GraphicsAlgorithm::CloseClip(Vector2i minClip, Vector2i maxClip, Vector2i *pOut, GLint *cnt, deque<Vector2i> *first, Vector2i *s)
{
    Vector2i pt;
    Boundary winEdge;
    
    for(winEdge = Left; winEdge <= Top; winEdge = (Boundary)(((int)winEdge)+1))
    {
        if(Cross(s[winEdge], first->at(winEdge), winEdge, minClip, maxClip))
        {
            pt = Intersect(s[winEdge], first->at(winEdge), winEdge, minClip, maxClip);
            if(winEdge < Top)
            {
                ClipPoint(pt, (Boundary)(((int)winEdge)+1), minClip, maxClip, pOut, cnt, first, s);
            }
            else
            {
                pOut[*cnt] = pt;
                (*cnt)++;
            }
        }
    }
}


/**************************
 *ALGORITHM IMPLEMENTATION*
 **************************/

void GraphicsAlgorithm::LineDDA(Line line, int subWindow, Color color)
{
    Renderer *renderer = Renderer::Instance();
    Point a = line.A(), b = line.B();
    
    int dx = b.Position().mX - a.Position().mX,
        dy = b.Position().mY - a.Position().mY, steps;
    float xIncrement, yIncrement, x = a.Position().mX, y = a.Position().mY;
    
    //determine which direction steps will orient towards
    if(fabs(dx) > fabs(dy))
    {
        steps = fabs(dx);
    }
    else
    {
        steps = fabs(dy);
    }
    
    //initialize increments
    xIncrement = (float)dx / (float)steps;
    yIncrement = (float)dy / (float)steps;
    
    //draw first point
    Point p = Point(nearbyint(x), nearbyint(y), color);
    renderer->DrawPoint(p, subWindow);
    
    //draw each subsequent point, incrementing along the way
    for(int i = 0; i < steps; i++)
    {
        x += xIncrement;
        y += yIncrement;
        
        p = Point(nearbyint(x), nearbyint(y), color);
        renderer->DrawPoint(p, subWindow);
    }
}

void GraphicsAlgorithm::LineBresenham(Line line, int subWindow)
{
    Point a = line.A(), b = line.B();
    //Ensure a -> b goes left to right
    if(a.X() > b.X())
    {
        Point t = a;
        a = b;
        b = t;
    }
    
    float dx = (float)(b.X() - a.X()),
          dy = (float)(b.Y() - a.Y());

    //Determine case and draw line
    int c = DetermineCase(dy, dx);
    switch(c)
    {
        case 1:
            //horizontal, vertical, or m = 1
            LineDDA(line, subWindow, Color::White());
            break;
        case 2:
            //m > 0
            HandlePositiveSlope(a, b, dx, dy, subWindow);
            break;
        case 3:
            //m < 0
            HandleNegativeSlope(a, b, dx, dy, subWindow);
            break;
    }
}

void GraphicsAlgorithm::PolyScanLine(deque<Line> edges, int subWindow, bool drawGreen)
{
    list<ScanData> remainingEdges;
    list<ScanData> activeEdges;
    
    
    FillRemainingEdges(edges, &remainingEdges);
    
    //initialize current Y scan value
    int curY = remainingEdges.front().yMin;
    
    while(true)
    {
        //fill and sort active edges
        list<ScanData>::iterator it = remainingEdges.begin();
        while(it != remainingEdges.end())
        {
            if(curY == it->yMin)
            {
                activeEdges.push_back((*it));
                it = remainingEdges.erase(it);
            }
            else
            {
                it++;
            }
        }
        activeEdges.sort(SortActiveEdges);
        
        //Draw Scan Line
        DrawScanLine(curY, activeEdges, subWindow, drawGreen);
        
        //increment Y
        curY++;
        
        //increment all x values
        for(list<ScanData>::iterator it = activeEdges.begin(); it != activeEdges.end(); it++)
        {
            it->xVal += it->inverseSlope;
        }
         
        //remove all edges that have a max y value == curent scan line y value
        it = activeEdges.begin();
        while(it != activeEdges.end())
        {
            if(curY == it->yMax)
            {
                it = activeEdges.erase(it);
            }
            else
            {
                it++;
            }
        }
        
        //check for finish condition
        if(activeEdges.size() == 0 && remainingEdges.size() == 0)
        {
            break;
        }
    }
}

Vector3i GraphicsAlgorithm::FindPolyCentroid(Polygon poly)
{
    deque<Point3d> vertices = poly.GetVertices();
    Vector3i centroid;
    
    //Find average of all vertices
    long vertexCount = vertices.size();
    for(int i = 0; i < vertexCount; i++)
    {
        centroid.mX += vertices[i].X();
        centroid.mY += vertices[i].Y();
        centroid.mZ += vertices[i].Z();
    }
    
    centroid.mX =(int)(((float)centroid.mX / (float)vertexCount) + 0.5f);
    centroid.mY =(int)(((float)centroid.mY / (float)vertexCount) + 0.5f);
    centroid.mZ =(int)(((float)centroid.mZ / (float)vertexCount) + 0.5f);
    
//    float x0 = 0.0f, y0 = 0.0f, x1 = 0.0f, y1 = 0.0f;
//    float a, area = 0.0f;
//    long vertexCount = vertices.size();
//    
//    //handle first vertexCount-1 vertices
//    int i;
//    for(i = 0; i < vertexCount - 1; i++)
//    {
//        x0 = vertices[i].GetX();
//        y0 = vertices[i].GetY();
//        x1 = vertices[i+1].GetX();
//        y1 = vertices[i+1].GetY();
//        a = (x0*y1) - (x1*y0);
//        area += a;
//        
//        centroid.mX += (x0 + x1) * a;
//        centroid.mY += (y0 + y1) * a;
//    }
//    
//    //handle last, closing vertex
//    x0 = vertices[i].GetX();
//    y0 = vertices[i].GetY();
//    x1 = vertices[0].GetX();
//    y1 = vertices[0].GetY();
//    a = (x0*y1) - (x1*y0);
//    area += a;
//    
//    centroid.mX += (x0 + x1) * a;
//    centroid.mY += (y0 + y1) * a;
//    
//    //Finalize calculations
//    area *= 0.5;
//    centroid.mX /= (6.0f * area);
//    centroid.mY /= (6.0f * area);
    
    return centroid;
}

void GraphicsAlgorithm::LineClipCohenSutherland(Vector2i minClip, Vector2i maxClip, Line *line)
{
    GLubyte code1, code2;
    GLint done = false, plotLine = false;
    float m = 0;
    Point p1 = line->A(), p2 = line->B();
    
    while(!done)
    {
        code1 = Encode(p1, minClip, maxClip);
        code2 = Encode(p2, minClip, maxClip);
        
        if(Accept(code1, code2)) //Accept line if completely inside
        {
            done = true;
            plotLine = true;
        }
        else if(Reject(code1, code2)) //Reject line if completely outside
        {
            line->A(Point(0,0));
            line->B(Point(0,0));
            return;
        }
        else // line is partially inside
        {
            //Make p1 = outside point
            if(Inside(code1))
            {
                SwapPoints(&p1, &p2);
                SwapCodes(&code1, &code2);
            }
            
            //use slope m to find clip field intersections
            if(p2.X() != p1.X())
            {
                m = ((float)(p2.Y() - p1.Y())) / ((float)(p2.X() - p1.X()));
            }
            
            if(code1 & sBitCodeLeft)
            {
                int x = p1.X(), y = p1.Y();
                
                y += (minClip.mX - x) * m;
                x = minClip.mX;
                
                p1.X(x);
                p1.Y(y);
            }
            else if(code1 & sBitCodeRight)
            {
                int x = p1.X(), y = p1.Y();
                
                y += (maxClip.mX - x) * m;
                x = maxClip.mX;
                
                p1.X(x);
                p1.Y(y);
            }
            else if(code1 & sBitCodeBottom)
            {
                int x = p1.X(), y = p1.Y();
                
                if(p2.X() != p1.X())
                {
                    x += (minClip.mY - y) / m;
                }
                y = minClip.mY;
                
                p1.X(x);
                p1.Y(y);
            }
            else if(code1 & sBitCodeTop)
            {
                int x = p1.X(), y = p1.Y();
                
                if(p2.X() != p1.X())
                {
                    x += (maxClip.mY - y) / m;
                }
                y = maxClip.mY;
                
                p1.X(x);
                p1.Y(y);
            }
        }
        
        if(plotLine)
        {
            line->A(p1);
            line->B(p2);
        }
    }    
}

int GraphicsAlgorithm::PolygonClipSutherlandHodgman(Vector2i minClip, Vector2i maxClip, Polygon poly, Vector2i *pOut)
{
    
    return 0;
//    deque<Vector2i> first;
//    Vector2i s[4];
//    GLint cnt = 0;
//    
//    deque<Point> vertices = poly.GetVertices();
//    long n = vertices.size();
//    for(unsigned int i = 0; i < n; i++)
//    {
//        Vector2i v = Vector2i(vertices[i].GetX(), vertices[i].GetY());
//        ClipPoint(v, Left, minClip, maxClip, pOut, &cnt, &first, s);
//    }
//    
//    //Reject if completely outside
//    if(cnt == 0)
//    {
//        pOut[0] = Vector2i(0,0);
//        pOut[1] = Vector2i(0,0);
//        return 2;
//    }
//    
//    CloseClip(minClip, maxClip, pOut, &cnt, &first, s);
//    
//    return cnt;
}

