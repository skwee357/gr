/**
* @file Vector.hpp
* @author Dmitri Koudriavtsev
* @brief Defenition of vector class.
*/

#ifndef VECTOR_HPP_INCLUDED
#define VECTOR_HPP_INCLUDED

const unsigned short int cVectorSize = 4;

class Vector{
  public:
    /** Default constructor. Create Zero lenth vector. */
    Vector();

    /** Copy constructor.
    * Create copy of vector <c>v</c>.
    * @param v Vector to copy.
    */
    Vector(const Vector& v);

    /** Copy constructor.
    * Create copy of vector <c>v</c>.
    * @param v Vector to copy.
    */
    Vector(const float v[cVectorSize]);

    /** Create vector.
    * @param vx X component of vector.
    * @param vy Y component of vector.
    * @param vz Z component of vector.
    * @param vw W component of vector.
    */
    Vector(float vx, float vy, float vz, float vw = 1.0f);

    /** Destructor. */
    ~Vector();

    /** @{ */
    /** Copy Vector.
    * @param v Vector to copy.
    */
    void copy(const Vector& v);
    void copy(const float v[cVectorSize]);
    /** @} */

    /** @defgroup Vector Algebra
    * @{
    */
    float length() const;

    void normalize();

    Vector cross(const Vector& vec) const;

    float dot(const Vector& vec) const;

    /** @} */

    /** @defgroup Vector Operators
    * @{
    */
    Vector& operator =(const Vector& v);

    Vector operator -(const Vector& v) const;

    const float& operator [](const int place) const;
    float& operator [](const int place);
    /** @} */

  private:
    float _v[cVectorSize]; /**< The vector it self. */
};

#endif // VECTOR_HPP_INCLUDED
