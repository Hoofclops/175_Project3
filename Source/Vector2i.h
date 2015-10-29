//
//  Vector2i.h
//  Project1
//
//  Created by Brandon Nguyen on 9/26/15.
//  Copyright (c) 2015 Brandon Nguyen. All rights reserved.
//

#ifndef __Project1__Vector2i__
#define __Project1__Vector2i__

class Vector2i
{
public:
    int mX;
    int mY;
    
    Vector2i();
    Vector2i(int x, int y);
    void Add(Vector2i other);
    void Subtract(Vector2i other);
    void Multiply(Vector2i other);
    
};
#endif /* defined(__Project1__Vector2i__) */
