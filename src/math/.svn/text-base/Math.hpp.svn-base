/**
* @file Math.hpp
* @author Dmitri Koudriavtsev
* @brief Defenition of helper functions.
*/

#ifndef MATH_HPP_INCLUDED
#define MATH_HPP_INCLUDED

const float cDegToRad = 0.0174532925199432957693f;
const float cRadToAng = 57.297469361769855164730f;
const float cEpsilon = 0.0001;

inline float radToDeg(float radians)
{
  return (radians * cRadToAng);
}

inline float degToRad(float degrees)
{
  return (degrees * cDegToRad);
}

inline float sqr(float a)
{
  return a*a;
}

inline bool floatEquals(float f1, float f2)
{
  return (((f1 - cEpsilon) < f2) && (f2 < (f1 + cEpsilon)));
}

#endif // MATH_HPP_INCLUDED
