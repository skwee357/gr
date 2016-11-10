/**
* @file Vector.cpp
* @author Dmitri Koudriavtsev
* @brief Realization of vector class.
*/

#include <cmath>

#include "Vector.hpp"
#include "../utils/Exception.hpp"

Vector::Vector()
{
  _v[0] = _v[1] = _v[2] = 0.0f;
  _v[3] = 1.0f;
}

Vector::Vector(const Vector& v)
{
  this->copy(v);
}

Vector::Vector(const float v[cVectorSize])
{
  this->copy(v);
}

Vector::Vector(float vx, float vy, float vz, float vw)
{
  _v[0] = vx;
  _v[1] = vy;
  _v[2] = vz;
  _v[3] = vw;
}

Vector::~Vector()
{
}

void Vector::copy(const Vector& v)
{
  for(int i = 0; i < cVectorSize; i++)
    _v[i] = v[i];
}

void Vector::copy(const float v[cVectorSize])
{
  for(int i = 0; i < cVectorSize; i++)
    _v[i] = v[i];
}

float Vector::length() const
{
  return sqrt(_v[0] * _v[0] + _v[1] * _v[1] + _v[2] * _v[2]);
}

void Vector::normalize()
{
  float l = this->length();

  if(l == 0.0f)
    return;

  _v[0] /= l;
  _v[1] /= l;
  _v[2] /= l;
}

Vector Vector::cross(const Vector& vec) const
{
  float rx, ry, rz;

  rx = _v[1] * vec[2] - _v[2] * vec[1];
  ry = _v[2] * vec[0] - _v[0] * vec[2];
  rz = _v[0] * vec[1] - _v[1] * vec[0];

  return Vector(rz, ry, rz);
}

float Vector::dot(const Vector& vec) const
{
  return (_v[0] * vec[0] + _v[1] * vec[1] + _v[2] * vec[2]);
}

Vector& Vector::operator =(const Vector& v)
{
  if(this == &v)
    return *this;

  for(int i = 0; i < cVectorSize; i++)
    _v[i] = v[i];

  return *this;
}

Vector Vector::operator -(const Vector& v) const
{
  return Vector(_v[0] - v[0], _v[1] - v[1], _v[2] - v[2]);
}

const float& Vector::operator [](const int place) const
{
  if((place < 0) || (place > cVectorSize))
    throw Exception("Trying to access to invalid vector value");
  else
    return _v[place];
}

float& Vector::operator [](const int place)
{
  if((place < 0) || (place > cVectorSize))
    throw Exception("Trying to access to invalid vector value");
  else
    return _v[place];
}
