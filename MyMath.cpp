#include "MyMath.h"
#include <math.h>
#include <Novice.h>
#include <cmath>
#include <assert.h>

using namespace std;

Vector3 Normalize(const Vector3& v) {
	Vector3 result;
	result.x = v.x / (float)sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
	result.y = v.y / (float)sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
	result.z = v.z / (float)sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
	return result;
}

Vector3 Cross(const Vector3& v1, const Vector3& v2) {
	Vector3 result;

	result.x = v1.y * v2.z - v1.z * v2.y;
	result.y = v1.z * v2.x - v1.x * v2.z;
	result.z = v1.x * v2.y - v1.y * v2.x;

	return result;
}

Matrix4x4 MakeRotateAxisAngle(const Vector3& axis, float angle) {
	
	float Cos = (1 - (float)cos(angle));
	float Sin = -(float)sin(angle);

	
	Matrix4x4 result;
	result.m[0][0] = (axis.x * axis.x) * Cos + (float)cos(angle);
	result.m[0][1] = (axis.x * axis.y) * Cos + (Sin * -axis.z);
	result.m[0][2] = (axis.x * axis.z) * Cos + (Sin * axis.y);
	result.m[0][3] = 0.0f;

	result.m[1][0] = (axis.x * axis.y) * Cos + (Sin * axis.z);
	result.m[1][1] = (axis.y * axis.y) * Cos + (float)cos(angle);
	result.m[1][2] = (axis.y * axis.z) * Cos + (Sin * -axis.x);
	result.m[1][3] = 0.0f;

	result.m[2][0] = (axis.x * axis.z) * Cos + (Sin * -axis.y);
	result.m[2][1] = (axis.y * axis.z) * Cos + (Sin * axis.x);
	result.m[2][2] = (axis.z * axis.z) * Cos + (float)cos(angle);
	result.m[2][3] = 0.0f;

	result.m[3][0] = 0.0f;
	result.m[3][1] = 0.0f; 
	result.m[3][2] = 0.0f;
	result.m[3][3] = 1.0f;


	return result;
}

Matrix4x4 DirectionToDirection(const Vector3& from, const Vector3& to) {
	
	//Vector3 N = Cross(from, to);
	Vector3 cross = Cross(from, to);

	float Cos = Mulcty(from, to);

	float Sin = (float)sqrt((cross.x * cross.x) + (cross.y * cross.y) + (cross.z * cross.z));

	
	float epasilon = 1e-6f;
	Vector3 axis = {};

	if (abs(Cos + 1.0f) <= epasilon) {
		if (abs(from.x) > epasilon || abs(from.y) > epasilon) { // ux != 0 || uy != 0
			axis.x = from.y;
			axis.y = - from.x;
			axis.z = 0;
		}
		else if (abs(from.x) > epasilon || abs(from.z) > epasilon) {// ux != 0 || uz != 0
			axis.x = from.z;
			axis.y = 0;
			axis.z = -from.x;
		}
		else {
			assert(false);
		}
		axis = Normalize(axis);
	}
	else {
		axis = Normalize(cross);
	}

	Matrix4x4 result;
	result.m[0][0] = (axis.x * axis.x) * (1 - Cos) + Cos;
	result.m[0][1] = (axis.x * axis.y) * (1 - Cos) + (-Sin * -axis.z);
	result.m[0][2] = (axis.x * axis.z) * (1 - Cos) + (-Sin * axis.y);
	result.m[0][3] = 0.0f;

	result.m[1][0] = (axis.x * axis.y) * (1 - Cos) + (-Sin * axis.z);
	result.m[1][1] = (axis.y * axis.y) * (1 - Cos) + Cos;
	result.m[1][2] = (axis.y * axis.z) * (1 - Cos) + (-Sin * -axis.x);
	result.m[1][3] = 0.0f;

	result.m[2][0] = (axis.x * axis.z) * (1 - Cos) + (-Sin * -axis.y);
	result.m[2][1] = (axis.y * axis.z) * (1 - Cos) + (-Sin * axis.x);
	result.m[2][2] = (axis.z * axis.z) * (1 - Cos) + Cos;
	result.m[2][3] = 0.0f;

	result.m[3][0] = 0.0f;
	result.m[3][1] = 0.0f;
	result.m[3][2] = 0.0f;
	result.m[3][3] = 1.0f;


	return result;
}

Vector3 operator-(const Vector3& v1) {
	Vector3 result;

	result.x = -v1.x;
	result.y = -v1.y;
	result.z = -v1.z;

	return result;
}

Vector3 operator*(const Vector3& v1, const Vector3& v2) {
	Vector3 result;

	result.x = v1.x * v2.x;
	result.y = v1.y * v2.y;
	result.z = v1.z * v2.z;

	return result;
}

float Mulcty(const Vector3& v1, const Vector3& v2) {
	Vector3 r;

	r.x = v1.x * v2.x;
	r.y = v1.y * v2.y;
	r.z = v1.z * v2.z;

	float result;


	result = r.x + r.y + r.z;

	return result;
}