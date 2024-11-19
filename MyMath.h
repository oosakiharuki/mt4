#include "Vector3.h"
#include "Matrix4x4.h"

struct Quaternion {
	float x;
	float y;
	float z;
	float w;
};

Vector3 operator-(const Vector3& v1);
Vector3 operator*(const Vector3& v1, const Vector3& v2);
float Mulcty(const Vector3& vewsf, const Vector3& v2);

Vector3 Normalize(const Vector3& v);
Vector3 Cross(const Vector3& v1, const Vector3& v2);

Matrix4x4 MakeRotateAxisAngle(const Vector3& axis, float angle);
Matrix4x4 DirectionToDirection(const Vector3& from,const Vector3& to);

Quaternion Multiply(const Quaternion& lhs, const Quaternion& rhs);
Quaternion IdentityQuaternion();
Quaternion Conjugate(const Quaternion& quaternion);
float Norm(const Quaternion& quaternion);
Quaternion Normalize(const Quaternion& quaternion);
Quaternion Inverse(const Quaternion& quaternion);

Quaternion MakeRotateAxisAngleQuaternion(const Vector3& axis, float angle);

Vector3 RotateVector(const Vector3& vector, const Quaternion& quaternion);

Matrix4x4 MakeRotateMatrix(const Quaternion& quaternion);