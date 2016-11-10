/**
* @file Matrix.cpp
* @author Dmitri Koudriavtsev
* @brief Realization of matrix class.
*/

#include <cmath>

#include "Matrix.hpp"
#include "Math.hpp"
#include "../utils/Exception.hpp"

Matrix::Matrix()
{
  this->identity();
}

Matrix::Matrix(const Matrix& m)
{
  this->copy(m);
}

Matrix::Matrix(const float m[cMatrixSize])
{
  this->copy(m);
}

Matrix::~Matrix()
{
}

void Matrix::identity()
{
  _m[0] = 1.0f; _m[4] = 0.0f; _m[ 8] = 0.0f; _m[12] = 0.0f;
  _m[1] = 0.0f; _m[5] = 1.0f; _m[ 9] = 0.0f; _m[13] = 0.0f;
  _m[2] = 0.0f; _m[6] = 0.0f; _m[10] = 1.0f; _m[14] = 0.0f;
  _m[3] = 0.0f; _m[7] = 0.0f; _m[11] = 0.0f; _m[15] = 1.0f;
}

void Matrix::copy(const Matrix& m)
{
  for(int i = 0; i < cMatrixSize; i++)
    _m[i] = m[i];
}

void Matrix::copy(const float m[cMatrixSize])
{
  for(int i = 0; i < cMatrixSize; i++)
    _m[i] = m[i];
}

void Matrix::createRotationX(float angle)
{
  float rad = degToRad(angle);
  float s = sin(rad);
  float c = cos(rad);

  _m[0] = 1.0f; _m[4] = 0.0f; _m[ 8] = 0.0f; _m[12] = 0.0f;
  _m[1] = 0.0f; _m[5] = c;    _m[ 9] = -s;   _m[13] = 0.0f;
  _m[2] = 0.0f; _m[6] = s;    _m[10] =  c;   _m[14] = 0.0f;
  _m[3] = 0.0f; _m[7] = 0.0f; _m[11] = 0.0f; _m[15] = 1.0f;
}

void Matrix::createRotationY(float angle)
{
  float rad = degToRad(angle);
  float s = sin(rad);
  float c = cos(rad);

  _m[0] =  c;   _m[4] = 0.0f; _m[ 8] = s;    _m[12] = 0.0f;
  _m[1] = 0.0f; _m[5] = 1.0f; _m[ 9] = 0.0f; _m[13] = 0.0f;
  _m[2] = -s;   _m[6] = 0.0f; _m[10] = c;    _m[14] = 0.0f;
  _m[3] = 0.0f; _m[7] = 0.0f; _m[11] = 0.0f; _m[15] = 1.0f;
}

void Matrix::createRotationZ(float angle)
{
  float rad = degToRad(angle);
  float s = sin(rad);
  float c = cos(rad);

  _m[0] = c;    _m[4] = -s;   _m[ 8] = 0.0f; _m[12] = 0.0f;
  _m[1] = s;    _m[5] =  c;   _m[ 9] = 0.0f; _m[13] = 0.0f;
  _m[2] = 0.0f; _m[6] = 0.0f; _m[10] = 1.0f; _m[14] = 0.0f;
  _m[3] = 0.0f; _m[7] = 0.0f; _m[11] = 0.0f; _m[15] = 1.0f;
}

void Matrix::createTranslation(float x, float y, float z)
{
  _m[0] = 1.0f; _m[4] = 0.0f; _m[ 8] = 0.0f; _m[12] = x;
  _m[1] = 0.0f; _m[5] = 1.0f; _m[ 9] = 0.0f; _m[13] = y;
  _m[2] = 0.0f; _m[6] = 0.0f; _m[10] = 1.0f; _m[14] = z;
  _m[3] = 0.0f; _m[7] = 0.0f; _m[11] = 0.0f; _m[15] = 1.0f;
}

void Matrix::createProjection(float fovy, float aspect, float znear, float zfar)
{
  float a = degToRad(fovy);
  float cotA = 1.0f / tan(a / 2.0f);

  float v1 = cotA / aspect;
  float v2 = cotA;
  float v3 = (zfar + znear) / (znear - zfar);
  float v4 = ((2.0 * zfar * znear) / (znear - zfar));

  _m[0] =   v1; _m[4] = 0.0f; _m[ 8] = 0.0f; _m[12] = 0.0f;
  _m[1] = 0.0f; _m[5] =   v2; _m[ 9] = 0.0f; _m[13] = 0.0f;
  _m[2] = 0.0f; _m[6] = 0.0f; _m[10] =   v3; _m[14] =   v4;
  _m[3] = 0.0f; _m[7] = 0.0f; _m[11] = -1.0f; _m[15] = 0.0f;
}

Matrix& Matrix::operator =(const Matrix& m)
{
  if(this == &m)
    return *this;

  for(int i = 0; i < cMatrixSize; i++)
    _m[i] = m[i];

  return *this;
}

const float& Matrix::operator [](const int place) const
{
  if((place < 0) || (place > cMatrixSize))
    throw Exception("Trying to access to invalid matrix value");
  else
    return _m[place];
}

float& Matrix::operator [](const int place)
{
  if((place < 0) || (place > cMatrixSize))
    throw Exception("Trying to access to invalid matrix value");
  else
    return _m[place];
}

Matrix Matrix::operator *(const Matrix& rhs) const
{
  float rm[cMatrixSize];

  rm[ 0] = _m[0] * rhs[ 0] + _m[4] * rhs[ 1] + _m[ 8] * rhs[ 2] + _m[12] * rhs [ 3];
  rm[ 1] = _m[1] * rhs[ 0] + _m[5] * rhs[ 1] + _m[ 9] * rhs[ 2] + _m[13] * rhs [ 3];
  rm[ 2] = _m[2] * rhs[ 0] + _m[6] * rhs[ 1] + _m[10] * rhs[ 2] + _m[14] * rhs [ 3];
  rm[ 3] = _m[3] * rhs[ 0] + _m[7] * rhs[ 1] + _m[11] * rhs[ 2] + _m[15] * rhs [ 3];
  rm[ 4] = _m[0] * rhs[ 4] + _m[4] * rhs[ 5] + _m[ 8] * rhs[ 6] + _m[12] * rhs [ 7];
  rm[ 5] = _m[1] * rhs[ 4] + _m[5] * rhs[ 5] + _m[ 9] * rhs[ 6] + _m[13] * rhs [ 7];
  rm[ 6] = _m[2] * rhs[ 4] + _m[6] * rhs[ 5] + _m[10] * rhs[ 6] + _m[14] * rhs [ 7];
  rm[ 7] = _m[3] * rhs[ 4] + _m[7] * rhs[ 5] + _m[11] * rhs[ 6] + _m[15] * rhs [ 7];
  rm[ 8] = _m[0] * rhs[ 8] + _m[4] * rhs[ 9] + _m[ 8] * rhs[10] + _m[12] * rhs [11];
  rm[ 9] = _m[1] * rhs[ 8] + _m[5] * rhs[ 9] + _m[ 9] * rhs[10] + _m[13] * rhs [11];
  rm[10] = _m[2] * rhs[ 8] + _m[6] * rhs[ 9] + _m[10] * rhs[10] + _m[14] * rhs [11];
  rm[11] = _m[3] * rhs[ 8] + _m[7] * rhs[ 9] + _m[11] * rhs[10] + _m[15] * rhs [11];
  rm[12] = _m[0] * rhs[12] + _m[4] * rhs[13] + _m[ 8] * rhs[14] + _m[12] * rhs [15];
  rm[13] = _m[1] * rhs[12] + _m[5] * rhs[13] + _m[ 9] * rhs[14] + _m[13] * rhs [15];
  rm[14] = _m[2] * rhs[12] + _m[6] * rhs[13] + _m[10] * rhs[14] + _m[14] * rhs [15];
  rm[15] = _m[3] * rhs[12] + _m[7] * rhs[13] + _m[11] * rhs[14] + _m[15] * rhs [15];

  return Matrix(rm);
}

Vector Matrix::operator *(const Vector& rhs) const
{
  return Vector(_m[0] * rhs[0] + _m[4] * rhs[1] + _m[ 8] * rhs[2] + _m[12] * rhs[3],
                _m[1] * rhs[0] + _m[5] * rhs[1] + _m[ 9] * rhs[2] + _m[13] * rhs[3],
                _m[2] * rhs[0] + _m[6] * rhs[1] + _m[10] * rhs[2] + _m[14] * rhs[3]);
}
