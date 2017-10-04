#pragma once
#include "VECTOR4D.h"
#include <iostream>
using namespace std;
struct MATRIX4D
{
public:
	union
	{
		struct
		{
			float m00, m01, m02, m03;
			float m10, m11, m12, m13;
			float m20, m21, m22, m23;
			float m30, m31, m32, m33;
		};
		float m[4][4];
		float v[16];
	};
public:
	MATRIX4D();
	MATRIX4D(
		float a00, float a01, float a02, float a03,
		float a10, float a11, float a12, float a13,
		float a20, float a21, float a22, float a23,
		float a30, float a31, float a32, float a33);
	MATRIX4D(const MATRIX4D& M);
	MATRIX4D(VECTOR4D &row0,
		VECTOR4D &row1,
		VECTOR4D &row2,
		VECTOR4D &row3);
	~MATRIX4D();
};

ostream& operator<<(ostream &out, MATRIX4D &A);
istream& operator>>(istream &in, MATRIX4D &A);
MATRIX4D operator*(MATRIX4D& A, MATRIX4D& B);
VECTOR4D operator*(VECTOR4D& V, MATRIX4D& M);
VECTOR4D operator*(MATRIX4D& M, VECTOR4D& V);
MATRIX4D Zero();
MATRIX4D Identity();
MATRIX4D Translation(float dx, float dy, float dz);
MATRIX4D RotationX(float theta);
MATRIX4D RotationY(float theta);
MATRIX4D RotationZ(float theta);
MATRIX4D Scaling(float sx, float sy, float sz);
float Det(MATRIX4D& M);
MATRIX4D Transpose(MATRIX4D& M);
MATRIX4D Cofactors(MATRIX4D& M);
MATRIX4D Inverse(MATRIX4D& M);
MATRIX4D LookAtLH(VECTOR4D& EyePos, VECTOR4D& Target, VECTOR4D& Up);