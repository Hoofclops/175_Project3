//
//  Matrix.cpp
//  Source
//
//  Created by Brandon Nguyen on 10/21/15.
//  Copyright © 2015 Brandon Nguyen. All rights reserved.
//
//  4x4Inverse code taken from: http://stackoverflow.com/questions/1148309/inverting-a-4x4-matrix

#include "Matrix.h"

Matrix::Matrix(int rows, int cols)
{
    mRows = rows;
    mCols = cols;
    
    mMatrix.resize(mRows);
    for(int i = 0; i < mRows; i++)
    {
        for(int j = 0; j < mCols; j++)
        {
            mMatrix[i].push_back(0);
        }
    }
}

Matrix::Matrix(int rows, int cols, deque<float> values)
{
    mRows = rows;
    mCols = cols;
    
    mMatrix.resize(mRows);
    for(int i = 0; i < mRows; i++)
    {
        mMatrix[i].resize(mCols);
    }
    
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            float val = values[0];
            mMatrix[i][j] = val;
            values.pop_front();
        }
    }
}

Matrix::Matrix(Vector3 vector)
{
    mRows = 4;
    mCols = 1;
    
    mMatrix.resize(mRows);
    for(int i = 0; i < mRows; i++)
    {
        mMatrix[i].resize(mCols);
    }
    mMatrix[0][0] = vector.mX;
    mMatrix[1][0] = vector.mY;
    mMatrix[2][0] = vector.mZ;
    mMatrix[3][0] = 1;
}

Matrix Matrix::Identity(int rows, int cols)
{
    Matrix identity = Matrix(rows, cols);
    
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            if(j == 0)
            {
                identity.mMatrix[i][j] = 1;
            }
            else
            {
                identity.mMatrix[i][j] = 0;
            }
        }
    }
    
    return identity;
}

void Matrix::SetValues(deque<float> values)
{
    for(int i = 0; i < mRows; i++)
    {
        for(int j = 0; j < mCols; j++)
        {
            float val = values[0];
            mMatrix[i][j] = val;
            values.pop_front();
        }
    }

}


Matrix Matrix::Multiply(Matrix other)
{
    if(mCols != other.mRows)
    {
        throw exception();
    }
    
    Matrix ret = Matrix(mRows, other.mCols);
    
    for(int i = 0; i < mRows; i++)
    {
        for(int j = 0; j < other.mCols; j++)
        {
            float sum = 0;
            for(int k = 0; k < mCols; k++)
            {
                sum += mMatrix[i][k] * other.mMatrix[k][j];
            }
            ret.mMatrix[i][j] = sum;
        }
    }
    
    return ret;
}

Vector3 Matrix::MultiplyVector(Vector3 vect)
{
    Matrix other = Matrix(vect);
    
    if(mCols != other.mRows)
    {
        throw exception();
    }
    
    Matrix ret = Matrix(mRows, other.mCols);
    
    for(int i = 0; i < mRows; i++)
    {
        for(int j = 0; j < other.mCols; j++)
        {
            float sum = 0;
            for(int k = 0; k < mCols; k++)
            {
                sum += mMatrix[i][k] * other.mMatrix[k][j];
            }
            ret.mMatrix[i][j] = sum;;
        }
    }
    
    return Vector3(ret.mMatrix[0][0], ret.mMatrix[1][0], ret.mMatrix[2][0]);
}


bool Matrix::Invert4by4(Matrix *out)
{
    Matrix in = *this;
    if(in.mRows != 4 || in.mCols != 4)
    {
        throw new exception();
    }
    
    float m[16], inv[16], invOut[16], det;
    
    int counter = 0;
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            m[counter] = in.mMatrix[i][j];
            counter++;
        }
    }
    
    inv[0] = m[5]  * m[10] * m[15] -
    m[5]  * m[11] * m[14] -
    m[9]  * m[6]  * m[15] +
    m[9]  * m[7]  * m[14] +
    m[13] * m[6]  * m[11] -
    m[13] * m[7]  * m[10];
    
    inv[4] = -m[4]  * m[10] * m[15] +
    m[4]  * m[11] * m[14] +
    m[8]  * m[6]  * m[15] -
    m[8]  * m[7]  * m[14] -
    m[12] * m[6]  * m[11] +
    m[12] * m[7]  * m[10];
    
    inv[8] = m[4]  * m[9] * m[15] -
    m[4]  * m[11] * m[13] -
    m[8]  * m[5] * m[15] +
    m[8]  * m[7] * m[13] +
    m[12] * m[5] * m[11] -
    m[12] * m[7] * m[9];
    
    inv[12] = -m[4]  * m[9] * m[14] +
    m[4]  * m[10] * m[13] +
    m[8]  * m[5] * m[14] -
    m[8]  * m[6] * m[13] -
    m[12] * m[5] * m[10] +
    m[12] * m[6] * m[9];
    
    inv[1] = -m[1]  * m[10] * m[15] +
    m[1]  * m[11] * m[14] +
    m[9]  * m[2] * m[15] -
    m[9]  * m[3] * m[14] -
    m[13] * m[2] * m[11] +
    m[13] * m[3] * m[10];
    
    inv[5] = m[0]  * m[10] * m[15] -
    m[0]  * m[11] * m[14] -
    m[8]  * m[2] * m[15] +
    m[8]  * m[3] * m[14] +
    m[12] * m[2] * m[11] -
    m[12] * m[3] * m[10];
    
    inv[9] = -m[0]  * m[9] * m[15] +
    m[0]  * m[11] * m[13] +
    m[8]  * m[1] * m[15] -
    m[8]  * m[3] * m[13] -
    m[12] * m[1] * m[11] +
    m[12] * m[3] * m[9];
    
    inv[13] = m[0]  * m[9] * m[14] -
    m[0]  * m[10] * m[13] -
    m[8]  * m[1] * m[14] +
    m[8]  * m[2] * m[13] +
    m[12] * m[1] * m[10] -
    m[12] * m[2] * m[9];
    
    inv[2] = m[1]  * m[6] * m[15] -
    m[1]  * m[7] * m[14] -
    m[5]  * m[2] * m[15] +
    m[5]  * m[3] * m[14] +
    m[13] * m[2] * m[7] -
    m[13] * m[3] * m[6];
    
    inv[6] = -m[0]  * m[6] * m[15] +
    m[0]  * m[7] * m[14] +
    m[4]  * m[2] * m[15] -
    m[4]  * m[3] * m[14] -
    m[12] * m[2] * m[7] +
    m[12] * m[3] * m[6];
    
    inv[10] = m[0]  * m[5] * m[15] -
    m[0]  * m[7] * m[13] -
    m[4]  * m[1] * m[15] +
    m[4]  * m[3] * m[13] +
    m[12] * m[1] * m[7] -
    m[12] * m[3] * m[5];
    
    inv[14] = -m[0]  * m[5] * m[14] +
    m[0]  * m[6] * m[13] +
    m[4]  * m[1] * m[14] -
    m[4]  * m[2] * m[13] -
    m[12] * m[1] * m[6] +
    m[12] * m[2] * m[5];
    
    inv[3] = -m[1] * m[6] * m[11] +
    m[1] * m[7] * m[10] +
    m[5] * m[2] * m[11] -
    m[5] * m[3] * m[10] -
    m[9] * m[2] * m[7] +
    m[9] * m[3] * m[6];
    
    inv[7] = m[0] * m[6] * m[11] -
    m[0] * m[7] * m[10] -
    m[4] * m[2] * m[11] +
    m[4] * m[3] * m[10] +
    m[8] * m[2] * m[7] -
    m[8] * m[3] * m[6];
    
    inv[11] = -m[0] * m[5] * m[11] +
    m[0] * m[7] * m[9] +
    m[4] * m[1] * m[11] -
    m[4] * m[3] * m[9] -
    m[8] * m[1] * m[7] +
    m[8] * m[3] * m[5];
    
    inv[15] = m[0] * m[5] * m[10] -
    m[0] * m[6] * m[9] -
    m[4] * m[1] * m[10] +
    m[4] * m[2] * m[9] +
    m[8] * m[1] * m[6] -
    m[8] * m[2] * m[5];
    
    det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];
    
    if (det == 0)
        return false;
    
    det = 1.0 / det;
    
    for (int i = 0; i < 16; i++)
        invOut[i] = inv[i] * det;
    
    counter = 0;
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            out->mMatrix[i][j] = invOut[counter];
            counter++;
        }
    }
    
    return true;
}