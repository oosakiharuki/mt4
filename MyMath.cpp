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

//lhs = p / rhs = r
Quaternion Multiply(const Quaternion& lhs, const Quaternion& rhs) {
	Quaternion result;//pr

	result.w = lhs.w * rhs.w - lhs.x * rhs.x - lhs.y * rhs.y - lhs.z * rhs.z;

	result.x = lhs.y * rhs.z - lhs.z * rhs.y + rhs.w * lhs.x + lhs.w * rhs.x;

	result.y = lhs.z * rhs.x - lhs.x * rhs.z + rhs.w * lhs.y + lhs.w * rhs.y;

	result.z = lhs.x * rhs.y - lhs.y * rhs.x + rhs.w * lhs.z + lhs.w * rhs.z;

	return result;
}

Quaternion IdentityQuaternion() {
	Quaternion result;//pr

	result.w = 1.0f;
	
	result.x = 0.0f;

	result.y = 0.0f;

	result.z = 0.0f;

	return result;
}

Quaternion Conjugate(const Quaternion& quaternion) {
	Quaternion result;//pr

	result.w = quaternion.w;

	result.x = -quaternion.x;

	result.y = -quaternion.y;

	result.z = -quaternion.z;

	return result;
}

float Norm(const Quaternion& quaternion) {

	float result;

	result = (float)sqrt((quaternion.w * quaternion.w) + (quaternion.x * quaternion.x) + (quaternion.y * quaternion.y) + (quaternion.z * quaternion.z));

	return result;
}


Quaternion Normalize(const Quaternion& quaternion) {
	Quaternion result;

	result.w = quaternion.w / (float)sqrt((quaternion.w * quaternion.w) + (quaternion.x * quaternion.x) + (quaternion.y * quaternion.y) + (quaternion.z * quaternion.z));
	result.x = quaternion.x / (float)sqrt((quaternion.w * quaternion.w) + (quaternion.x * quaternion.x) + (quaternion.y * quaternion.y) + (quaternion.z * quaternion.z));
	result.y = quaternion.y / (float)sqrt((quaternion.w * quaternion.w) + (quaternion.x * quaternion.x) + (quaternion.y * quaternion.y) + (quaternion.z * quaternion.z));
	result.z = quaternion.z / (float)sqrt((quaternion.w * quaternion.w) + (quaternion.x * quaternion.x) + (quaternion.y * quaternion.y) + (quaternion.z * quaternion.z));

	return result;
}

Quaternion Inverse(const Quaternion& quaternion) {
	Quaternion result;

	result.w = Conjugate(quaternion).w / (Norm(quaternion) * Norm(quaternion));
	result.x = Conjugate(quaternion).x / (Norm(quaternion) * Norm(quaternion));
	result.y = Conjugate(quaternion).y / (Norm(quaternion) * Norm(quaternion));
	result.z = Conjugate(quaternion).z / (Norm(quaternion) * Norm(quaternion));

	return result;
}


Quaternion MakeRotateAxisAngleQuaternion(const Vector3& axis, float angle) {
	Quaternion r = { axis.x,axis.y, axis.z, 0 };
	
	r.w = cos(angle / 2) * Norm(r);
	r.x = sin(angle / 2) * axis.x;
	r.y = sin(angle / 2) * axis.y;
	r.z = sin(angle / 2) * axis.z;

	return r;
}


//Vector3 RotateVector(const Vector3& vector, const Quaternion& quaternion) {
//
//}
//
//Matrix4x4 MakeRotateMatrix(const Quaternion& quaternion) {
//
//}