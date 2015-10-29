//
//  Vector3i.h
//  Source
//
//  Created by Brandon Nguyen on 10/14/15.
//  Copyright © 2015 Brandon Nguyen. All rights reserved.
//

#ifndef Vector3i_h
#define Vector3i_h

class Vector3i
{
public:
    int mX;
    int mY;
    int mZ;
    
    Vector3i();
    Vector3i(int x, int y, int z);
    void Add(Vector3i other);
    void Subtract(Vector3i other);
    void Multiply(Vector3i other);
    
};

#endif /* Vector3i_h */
