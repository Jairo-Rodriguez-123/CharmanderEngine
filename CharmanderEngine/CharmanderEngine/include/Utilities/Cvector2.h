#pragma once

#include "../Prerequisites.h"

/**
 * @class CVector2
 * @brief 2D vector class with basic vector operations.
 *
 * Provides utility for 2D mathematical operations such as addition, subtraction,
 * normalization, dot product, length, and interpolation.
 */
class
  CVector2 {
public:
  float x; ///< X component of the vector
  float y; ///< Y component of the vector

  /**
   * @brief Default constructor initializes vector to (0,0).
   */
  CVector2() : x(0), y(0) {}

  /**
   * @brief Constructor initializes vector with given components.
   * @param x X component.
   * @param y Y component.
   */
  CVector2(float x, float y) : x(x), y(y) {}

  /**
   * @brief Vector addition.
   * @param other Vector to add.
   * @return Resulting vector.
   */
  CVector2
    operator+(const CVector2& other) const;

  /**
   * @brief Vector subtraction.
   * @param other Vector to subtract.
   * @return Resulting vector.
   */
  CVector2
    operator-(const CVector2& other) const;

  /**
   * @brief Scalar multiplication.
   * @param scalar Value to multiply with.
   * @return Scaled vector.
   */
  CVector2
    operator*(float scalar) const;

  /**
   * @brief Scalar division.
   * @param scalar Value to divide by.
   * @return Scaled vector.
   */
  CVector2
    operator/(float scalar) const;

  /**
   * @brief Adds another vector to this vector.
   * @param other Vector to add.
   * @return Reference to this vector.
   */
  CVector2&
    operator+=(const CVector2& other);

  /**
   * @brief Subtracts another vector from this vector.
   * @param other Vector to subtract.
   * @return Reference to this vector.
   */
  CVector2&
    operator-=(const CVector2& other);

  /**
   * @brief Multiplies this vector by a scalar.
   * @param scalar Value to multiply with.
   * @return Reference to this vector.
   */
  CVector2&
    operator*=(float scalar);

  /**
   * @brief Divides this vector by a scalar.
   * @param scalar Value to divide by.
   * @return Reference to this vector.
   */
  CVector2&
    operator/=(float scalar);

  /**
   * @brief Equality comparison.
   * @param other Vector to compare with.
   * @return True if both components are equal.
   */
  bool
    operator==(const CVector2& other) const;

  /**
   * @brief Inequality comparison.
   * @param other Vector to compare with.
   * @return True if components are not equal.
   */
  bool
    operator!=(const CVector2& other) const;

  /**
   * @brief Access vector component by index.
   * @param index 0 for x, 1 for y.
   * @return Reference to component.
   */
  float&
    operator[](int index);

  /**
   * @brief Access vector component by index (const).
   * @param index 0 for x, 1 for y.
   * @return Const reference to component.
   */
  const float&
    operator[](int index) const;

  /**
   * @brief Returns the squared length of the vector.
   * @return Squared length.
   */
  float
    lengthSquare() const;

  /**
   * @brief Returns the length (magnitude) of the vector.
   * @return Length of the vector.
   */
  float
    length() const;

  /**
   * @brief Dot product with another vector.
   * @param other Vector to dot with.
   * @return Dot product result.
   */
  float
    dot(const CVector2& other) const;

  /**
   * @brief Returns a normalized copy of the vector.
   * @return Normalized vector.
   */
  CVector2
    normalized() const;

  /**
   * @brief Normalizes the vector in-place.
   */
  void
    normalize();

  /**
   * @brief Calculates squared distance between two vectors.
   * @param a First vector.
   * @param b Second vector.
   * @return Squared distance.
   */
  inline static float
    distance(const CVector2& a, const CVector2& b);

  /**
   * @brief Linearly interpolates between two vectors.
   * @param a Start vector.
   * @param b End vector.
   * @param t Interpolation factor (0.0 - 1.0).
   * @return Interpolated vector.
   */
  inline static CVector2
    lerp(const CVector2& a, const CVector2& b, float t);

  /**
   * @brief Returns a vector initialized to zero.
   * @return Vector (0,0).
   */
  inline static CVector2
    zero();

  /**
   * @brief Returns a vector initialized to one.
   * @return Vector (1,1).
   */
  inline static CVector2
    one();

  /**
   * @brief Stream output operator for printing vector.
   * @param os Output stream.
   * @param v Vector to print.
   * @return Reference to output stream.
   */
  friend std::ostream&
    operator<<(std::ostream& os, const CVector2& v) {
    os << "CVector2(" << v.x << ", " << v.y << ")";
    return os;
  }
};