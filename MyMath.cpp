#include "MyMath.h"
#include <math.h>

using namespace std;

Vector3 MyMath::Normalize(const Vector3& v) {
	Vector3 result;
	result.x = v.x / (float)sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
	result.y = v.y / (float)sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
	result.z = v.z / (float)sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
	return result;
}

Matrix4x4  MyMath::MakeRotateAxisAngle(const Vector3& axis, float angle) {
	

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