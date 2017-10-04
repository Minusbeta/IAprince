#include "stdafx.h"
#include "MATRIX4D.h"
#include <cmath>
MATRIX4D::MATRIX4D()
{
}
MATRIX4D::MATRIX4D(const MATRIX4D& A)
{
	*this = A;
}
MATRIX4D::MATRIX4D(
	float a00, float a01, float a02, float a03,
	float a10, float a11, float a12, float a13,
	float a20, float a21, float a22, float a23,
	float a30, float a31, float a32, float a33)
{
	m00 = a00; m01 = a01; m02 = a02; m03 = a03;
	m10 = a10; m11 = a11; m12 = a12; m13 = a13;
	m20 = a20; m21 = a21; m22 = a22; m23 = a23;
	m30 = a30; m31 = a31; m32 = a32; m33 = a33;
}
MATRIX4D::MATRIX4D(
	VECTOR4D &row0,
	VECTOR4D &row1,
	VECTOR4D &row2,
	VECTOR4D &row3)
{
	*(VECTOR4D*)&m00 = row0;
	*(VECTOR4D*)&m10 = row1;
	*(VECTOR4D*)&m20 = row2;
	*(VECTOR4D*)&m30 = row3;
}
MATRIX4D::~MATRIX4D()
{
}
MATRIX4D operator*(MATRIX4D& A, MATRIX4D& B)
{
	MATRIX4D R = Zero();
	for (int j = 0; j < 4; j++)
		for (int i = 0; i < 4; i++)
			for (int k = 0; k < 4; k++)
				R.m[j][i] += A.m[j][k] * B.m[k][i];
	return R;
}
VECTOR4D operator*(VECTOR4D& V, MATRIX4D& M)
{
	VECTOR4D R(0, 0, 0, 0);
	for (int j = 0; j < 4; j++)
		for (int i = 0; i < 4; i++)
			R.v[j] += V.v[i] * M.m[i][j];
	return R;

}
VECTOR4D operator*(MATRIX4D& M, VECTOR4D& V)
{
	return VECTOR4D(
		Dot(*(VECTOR4D*)&M.m00, V),
		Dot(*(VECTOR4D*)&M.m10, V),
		Dot(*(VECTOR4D*)&M.m20, V),
		Dot(*(VECTOR4D*)&M.m30, V)
		);
}
MATRIX4D Zero()
{
	MATRIX4D Z;
	memset(&Z, 0, sizeof(MATRIX4D));
	return Z;
}
MATRIX4D Identity()
{
	MATRIX4D I = Zero();
	for (int i = 0; i < 4; i++) I.m[i][i] = 1.0f;
	return I;
}
MATRIX4D Translation(float dx, float dy, float dz)
{
	MATRIX4D T = Identity();
	T.m03 = dx;
	T.m13 = dy;
	T.m23 = dz;
	return T;
}
MATRIX4D RotationX(float theta)
{
	MATRIX4D R = Identity();

	R.m11 = std::cos(theta);
	R.m22 = R.m11;
	R.m21 = std::sin(theta);
	R.m12 = -R.m21;
	return R;
}
MATRIX4D RotationY(float theta)
{
	MATRIX4D R = Identity();
	R.m22 = R.m00 = std::cos(theta);
	R.m20 = -std::sin(theta);
	R.m02 = -R.m20;
	return R;
}
MATRIX4D RotationZ(float theta)
{
	MATRIX4D R = Identity();
	R.m00 = std::cos(theta);
	R.m11 = R.m00;
	R.m10 = std::sin(theta);
	R.m01 = -R.m10;
	return R;
}
MATRIX4D Scaling(float sx, float sy, float sz)
{
	MATRIX4D S = Identity();
	S.m00 = sx;
	S.m11 = sy;
	S.m22 = sz;
	return S;
}
float Det(MATRIX4D& M);
MATRIX4D Transpose(MATRIX4D& M);
MATRIX4D Cofactors(MATRIX4D& M);
MATRIX4D Inverse(MATRIX4D& M);
MATRIX4D LookAtLH(VECTOR4D& EyePos, VECTOR4D& Target, VECTOR4D& Up)
{
	MATRIX4D View;
	VECTOR4D xDir, yDir, zDir;
	zDir = Normalize(Target - EyePos);
	xDir = Normalize(Cross3(Up, zDir));
	yDir = Cross3(zDir, xDir);
	*(VECTOR4D*)&View.m00 = VECTOR4D(xDir.x, yDir.x, zDir.x, 0);
	*(VECTOR4D*)&View.m10 = VECTOR4D(xDir.y, yDir.y, zDir.y, 0);
	*(VECTOR4D*)&View.m20 = VECTOR4D(xDir.z, yDir.z, zDir.z, 0);
	*(VECTOR4D*)&View.m30 = VECTOR4D(-Dot(xDir, EyePos), -Dot(yDir, EyePos), -Dot(zDir, EyePos), 1);
	return View;
}

