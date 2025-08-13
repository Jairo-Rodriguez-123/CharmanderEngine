#include "Utilities/CVector2.h"

// Constructores
CVector2::CVector2() : x(0.f), y(0.f) {}
CVector2::CVector2(float x_, float y_) : x(x_), y(y_) {}

// Operadores
CVector2
CVector2::operator+(const CVector2& v) const {
  return {
    x + v.x,
    y + v.y
  };
}

CVector2
CVector2::operator-(const CVector2& v) const {
  return {
    x - v.x,
    y - v.y
  };
}

CVector2
CVector2::operator*(float s) const {
  return {
    x * s,
    y * s
  };
}

CVector2
CVector2::operator/(float s) const {
  return {
    x / s,
    y / s
  };
}

CVector2&
CVector2::operator+=(const CVector2& v) {
  x += v.x;
  y += v.y;
  return *this;
}

CVector2&
CVector2::operator-=(const CVector2& v) {
  x -= v.x;
  y -= v.y;
  return *this;
}

CVector2&
CVector2::operator*=(float s) {
  x *= s;
  y *= s;
  return *this;
}

CVector2&
CVector2::operator/=(float s) {
  x /= s;
  y /= s;
  return *this;
}

// Comparaciones
bool
CVector2::operator==(const CVector2& v) const {
  return x == v.x && y == v.y;
}
bool
CVector2::operator!=(const CVector2& v) const {
  return !(*this == v);
}

// Acceso por �ndice
float&
CVector2::operator[](std::size_t i) {
  return (i == 0) ? x : y;
}

const float&
CVector2::operator[](std::size_t i) const {
  return (i == 0) ? x : y;
}

// Funciones geom�tricas
float CVector2::length() const {
  return std::sqrt(x * x + y * y);
}

float CVector2::lengthSquared() const {
  return x * x + y * y;
}

float CVector2::dot(const CVector2& v) const {
  return x * v.x + y * v.y;
}

float CVector2::cross(const CVector2& v) const {
  return x * v.y - y * v.x;
}

CVector2 CVector2::normalized() const {
  float len = length();
  return (len != 0.f) ? CVector2{ x / len, y / len } : CVector2{ 0.f,0.f };
}

void CVector2::normalize() {
  float len = length();
  if (len != 0.f) { x /= len; y /= len; }
}

// M�todos est�ticos
float
CVector2::distance(const CVector2& a, const CVector2& b) {
  return (a - b).length();
}

CVector2
CVector2::lerp(const CVector2& a, const CVector2& b, float t) {
  return a + (b - a) * t;
}

CVector2
CVector2::zero() {
  return { 0.f, 0.f };
}
CVector2
CVector2::one() {
  return { 1.f, 1.f };
}

// Depuraci�n
std::ostream&
operator<<(std::ostream& os, const CVector2& v) {
  return os << "(" << v.x << ", " << v.y << ")";
}