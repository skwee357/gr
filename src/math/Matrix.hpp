/**
* @file Matrix.hpp
* @author Dmitri Koudriavtsev
* @brief Defenition of matrix class.
*/

#ifndef MATRIX_HPP_INCLUDED
#define MATRIX_HPP_INCLUDED

#include "Vector.hpp"

const unsigned short int cMatrixSize = 16;

class Matrix{
  public:
    /** Default constructor. Create Identity matrix. */
    Matrix();

    /** Copy constructor.
    * Create copy of matrix <c>m</c>.
    * @param m Matrix to copy.
    */
    Matrix(const Matrix& m);

    /** Copy constructor.
    * Create copy of matrix <c>m</c>.
    * @param m Matrix to copy.
    */
    Matrix(const float m[cMatrixSize]);

    /** Destructor. */
    ~Matrix();


    /** Create identity matrix. */
    void identity();

    /** @{ */
    /** Copy matrix.
    * @param m Matrix to copy.
    */
    void copy(const Matrix& m);
    void copy(const float m[cMatrixSize]);
    /** @} */

    /** @{ */
    /** Create Rotation matrix.
    * @param angle Angle of rotation in degrees.
    */
    void createRotationX(float angle);
    void createRotationY(float angle);
    void createRotationZ(float angle);
    /** @} */

    /** Create translation matrix.
    * @param x Translation in x axis.
    * @param y Translation in y axis.
    * @param z Translation in z axis.
    */
    void createTranslation(float x, float y, float z);

    /** Create projection matrix.
    * @param fovy Filed of view angle.
    * @param aspect Aspect ratio.
    * @param znear Near plane.
    * @param zfar Far plane.
    */
    void createProjection(float fovy, float aspect, float znear, float zfar);


    /** @defgroup Matrix Operators
    * @{
    */
    Matrix& operator =(const Matrix& m);

    const float& operator [](const int place) const;
    float& operator [](const int place);

    Matrix operator *(const Matrix& rhs) const;

    Vector operator *(const Vector& rhs) const;
    /** @} */

  private:
    float _m[cMatrixSize]; /**< The matrix it self. */
};

#endif // MATRIX_HPP_INCLUDED
