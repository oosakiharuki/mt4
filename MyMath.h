#include "Vector3.h"
#include "Matrix4x4.h"

Vector3 operator-(const Vector3& v1);
Vector3 operator*(const Vector3& v1, const Vector3& v2);
float Mulcty(const Vector3& vewsf, const Vector3& v2);

Vector3 Normalize(const Vector3& v);
Vector3 Cross(const Vector3& v1, const Vector3& v2);

Matrix4x4 MakeRotateAxisAngle(const Vector3& axis, float angle);
Matrix4x4 DirectionToDirection(const Vector3& from,const Vector3& to);
