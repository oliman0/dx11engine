#include "engine_math.h"

Math::Vector2::Vector2(float x, float y) : x(x), y(y) {}
Math::Vector2::Vector2(float a) : x(a), y(a) {}
Math::Vector2::~Vector2() {}

DirectX::XMVECTOR Math::Vector2::GetXMVector() { return DirectX::XMVectorSet(x, y, 0, 0); }

bool Math::Vector2::operator==(Vector2 a) { return (x == a.x) && (y == a.y); }
bool Math::Vector2::operator!=(Vector2 a) { return (x != a.x) && (y != a.y); }

Math::Vector2& Math::Vector2::operator=(float a) { x = a; y = a; return *this; }

Math::Vector2 Math::Vector2::operator+(Vector2 a) { return Vector2(x + a.x, y + a.y); }
Math::Vector2& Math::Vector2::operator+=(Vector2 a) { x += a.x; y += a.y; return *this; }

Math::Vector2 Math::Vector2::operator-(Vector2 a) { return Vector2(x - a.x, y - a.y); }
Math::Vector2 Math::Vector2::operator-() { return Vector2(-x, -y); }
Math::Vector2& Math::Vector2::operator-=(Vector2 a) { x -= a.x; y -= a.y; return *this; }

Math::Vector2 Math::Vector2::operator*(float a) { return Vector2(x * a, y * a); }
Math::Vector2& Math::Vector2::operator*=(float a) { x *= a; y *= a; return *this; }

Math::Vector2 Math::Vector2::operator/(float a) { return Vector2(x / a, y / a); }
Math::Vector2& Math::Vector2::operator/=(float a) { x /= a; y /= a; return *this; }

////////////////////////////////////////////////////////////////////////////////////////////////

Math::Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
Math::Vector3::Vector3(float a) : x(a), y(a), z(a) {}
Math::Vector3::~Vector3() {}

DirectX::XMVECTOR Math::Vector3::GetXMVector() { return DirectX::XMVectorSet(x, y, z, 0); }

bool Math::Vector3::operator==(Vector3 a) { return (x == a.x) && (y == a.y) && (z == a.z); }
bool Math::Vector3::operator!=(Vector3 a) { return (x != a.x) && (y != a.y) && (z != a.z); }

Math::Vector3& Math::Vector3::operator=(float a) { x = a; y = a; z = a; return *this; }

Math::Vector3 Math::Vector3::operator+(Vector3 a) { return Vector3(x + a.x, y + a.y, z + a.z); }
Math::Vector3& Math::Vector3::operator+=(Vector3 a) { x += a.x; y += a.y; z += a.z; return *this; }

Math::Vector3 Math::Vector3::operator-(Vector3 a) { return Vector3(x - a.x, y - a.y, z - a.z); }
Math::Vector3 Math::Vector3::operator-() { return Vector3(-x, -y, -z); }
Math::Vector3& Math::Vector3::operator-=(Vector3 a) { x -= a.x; y -= a.y; z -= a.z; return *this; }

Math::Vector3 Math::Vector3::operator*(float a) { return Vector3(x * a, y * a, z * a); }
Math::Vector3& Math::Vector3::operator*=(float a) { x *= a; y *= a; z *= a; return *this; }

Math::Vector3 Math::Vector3::operator/(float a) { return Vector3(x / a, y / a, z / a); }
Math::Vector3& Math::Vector3::operator/=(float a) { x /= a; y /= a; z /= a; return *this; }

////////////////////////////////////////////////////////////////////////////////////////////////

Math::Vector4::Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
Math::Vector4::Vector4(float a) : x(a), y(a), z(a), w(a) {}
Math::Vector4::~Vector4() {}

DirectX::XMVECTOR Math::Vector4::GetXMVector() { return DirectX::XMVectorSet(x, y, z, w); }

bool Math::Vector4::operator==(Vector4 a) { return (x == a.x) && (y == a.y) && (z == a.z) && (w == a.w); }
bool Math::Vector4::operator!=(Vector4 a) { return (x != a.x) && (y != a.y) && (z != a.z) && (w != a.w); }

Math::Vector4& Math::Vector4::operator=(float a) { x = a; y = a; z = a; w = a; return *this; }

Math::Vector4 Math::Vector4::operator+(Vector4 a) { return Vector4(x + a.x, y + a.y, z + a.z, w + a.w); }
Math::Vector4& Math::Vector4::operator+=(Vector4 a) { x += a.x; y += a.y; z += a.z; w += a.w; return *this; }

Math::Vector4 Math::Vector4::operator-(Vector4 a) { return Vector4(x - a.x, y - a.y, z - a.z, w - a.w); }
Math::Vector4 Math::Vector4::operator-() { return Vector4(-x, -y, -z, -w); }
Math::Vector4& Math::Vector4::operator-=(Vector4 a) { x -= a.x; y -= a.y; z -= a.z; w -= a.w; return *this; }

Math::Vector4 Math::Vector4::operator*(float a) { return Vector4(x * a, y * a, z * a, w * a); }
Math::Vector4& Math::Vector4::operator*=(float a) { x *= a; y *= a; z *= a; w *= a; return *this; }

Math::Vector4 Math::Vector4::operator/(float a) { return Vector4(x / a, y / a, z / a, w / a); }
Math::Vector4& Math::Vector4::operator/=(float a) { x /= a; y /= a; z /= a; w /= a; return *this; }

////////////////////////////////////////////////////////////////////////////////////////////////

float Math::Dot(Math::Vector2 a, Math::Vector2 b) { return (a.x * b.x) + (a.y * b.y); }
float Math::Dot(Math::Vector3 a, Math::Vector3 b) { return (a.x * b.x) + (a.y * b.y) + (a.z * b.z); }
float Math::Dot(Math::Vector4 a, Math::Vector4 b) { return (a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w); }

Math::Vector3 Math::Cross(Math::Vector3 a, Math::Vector3 b) { return Math::Vector3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x); }

float Math::Length(Math::Vector2 v) { return sqrt((v.x * v.x) + (v.y * v.y)); }
float Math::Length(Math::Vector3 v) { return sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z)); }
float Math::Length(Math::Vector4 v) { return sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z) + (v.w * v.w)); }

Math::Vector2 Math::Normalize(Math::Vector2 v) { float n = Math::Length(v); if (n == 0) return v; return Math::Vector2(v.x / n, v.y / n); }
Math::Vector3 Math::Normalize(Math::Vector3 v) { float n = Math::Length(v); if (n == 0) return v; return Math::Vector3(v.x / n, v.y / n, v.z / n); }
Math::Vector4 Math::Normalize(Math::Vector4 v) { float n = Math::Length(v); if (n == 0) return v; return Math::Vector4(v.x / n, v.y / n, v.z / n, v.w / n); }

float Math::Distance(Vector2 a, Vector2 b) { return std::abs(Length(a - b)); }
float Math::Distance(Vector3 a, Vector3 b) { return std::abs(Length(a - b)); }
float Math::Distance(Vector4 a, Vector4 b) { return std::abs(Length(a - b)); }

Math::Vector2 Math::Reflect(Vector2 I, Vector2 normal) { return I - normal * 2.0f * Dot(normal, I); }
Math::Vector3 Math::Reflect(Vector3 I, Vector3 normal) { return I - normal * 2.0f * Dot(normal, I); }
Math::Vector4 Math::Reflect(Vector4 I, Vector4 normal) { return I - normal * 2.0f * Dot(normal, I); }

float Math::Radians(float degrees) { return degrees * (PI / 180.0f); }

float Math::Pi() { return PI; }