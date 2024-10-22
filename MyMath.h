#include "Vector3.h"
#include "Matrix4x4.h"


class MyMath {
public:
	Vector3 Normalize(const Vector3& v);

	Matrix4x4 MakeRotateAxisAngle(const Vector3& axis, float angle);

};