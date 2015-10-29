//
//  main.cpp
//  Project1
//
//  Created by Brandon Nguyen on 9/25/15.
//  Copyright (c) 2015 Brandon Nguyen. All rights reserved.
//

 #include <OpenGL/gl.h>
 #include <OpenGL/glu.h>
 #include <GLUT/glut.h>
//#include <GL/glut.h>
#include "Vector2i.h"
#include "Renderer.h"
#include "ObjectEditor.h"
#include "InputOutputUtility.h"
#include "Matrix.h"

int main(int argc, char *argv[])
{
    
    Renderer::Instance()->InitWindow(600, 600);
    Vector2i screenSize = Renderer::Instance()->ScreenSize();
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(screenSize.mX, screenSize.mY);
    glutInitWindowPosition(100, 100);
    
    Renderer::sMainWindow = glutCreateWindow("Project 2");
    glutDisplayFunc(Renderer::DisplayPixelBuffer);
    glutKeyboardFunc(InputOutputUtility::DetectInput);
    
    //bottom left
    Renderer::sSubWindow1 = glutCreateSubWindow(Renderer::sMainWindow, 0, screenSize.mY/2, screenSize.mX/2, screenSize.mY/2);
    glutDisplayFunc(Renderer::DisplayPixelBuffer1);
    glutKeyboardFunc(InputOutputUtility::DetectInput);
    
    //bottom right
    Renderer::sSubWindow2 = glutCreateSubWindow(Renderer::sMainWindow, screenSize.mX/2, screenSize.mY/2, screenSize.mX/2, screenSize.mY/2);
    glutDisplayFunc(Renderer::DisplayPixelBuffer2);
    glutKeyboardFunc(InputOutputUtility::DetectInput);
    
    //top left
    Renderer::sSubWindow3 = glutCreateSubWindow(Renderer::sMainWindow, 0, 0, screenSize.mX/2, screenSize.mY/2);
    glutDisplayFunc(Renderer::DisplayPixelBuffer3);
    glutKeyboardFunc(InputOutputUtility::DetectInput);
    
//    glutIdleFunc(Renderer::IdleAnimation);
    
    glClearColor(0, 0, 0, 0);

    glutMainLoop();//main display loop, will display until terminate
    
    return 0;
}
