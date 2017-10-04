#include "stdafx.h"
#include "VECTOR4D.h"
#include <cmath>
VECTOR4D::VECTOR4D()
{
}

VECTOR4D::VECTOR4D(const VECTOR4D& V)
{
	x = V.x;
	y = V.y;
	z = V.z;
	w = V.w;
}
VECTOR4D::VECTOR4D(const float fx, const float fy, const float fz, const float fw)
{
	x = fx;
	y = fy;
	z = fz;
	w = fw;
}

VECTOR4D::~VECTOR4D()
{
}
VECTOR4D operator* (const VECTOR4D  &A, const VECTOR4D &B)
{
	return VECTOR4D(A.x*B.x, A.y*B.y, A.z*B.z, A.w*B.w);
}
VECTOR4D operator* (float s, const VECTOR4D &A)
{
	return VECTOR4D(A.x*s, A.y*s, A.z*s, A.w*s);
}
VECTOR4D operator* (const VECTOR4D &A, float s)
{
	return s*A;
}
VECTOR4D operator/ (const VECTOR4D &A, float s)
{
	return A*(1 / s);
}
VECTOR4D operator+(const VECTOR4D& A, const VECTOR4D& B)
{
	return VECTOR4D(A.x + B.x, A.y + B.y, A.z + B.z, A.w + B.w);
}
VECTOR4D operator-(const VECTOR4D& A, const VECTOR4D& B)
{
	return VECTOR4D(A.x - B.x, A.y - B.y, A.z - B.z, A.w - B.w);

}
float Dot(const VECTOR4D &A, const VECTOR4D &B)
{
	return A.x*B.x + A.y*B.y + A.z*B.z + A.w*B.w;
}
VECTOR4D Cross3(const VECTOR4D& A, const VECTOR4D& B)
{
	return VECTOR4D(
		A.y*B.z - A.z*B.y,
		A.z*B.x - A.x*B.z,
		A.x*B.y - A.y*B.x, 0);
}
float Magnity(const VECTOR4D& A)
{
	return std::sqrt(Dot(A, A));
}
VECTOR4D Normalize(const VECTOR4D& A)
{
	return A / Magnity(A);
}

bool RayCastOnPlane(VECTOR4D& RayOrigin, VECTOR4D& RayDir,
	VECTOR4D& Plane, VECTOR4D& Intersection)
{
	float d = Dot(Plane, RayDir);
	if (fabsf(d) < 0.001f) return false;
	float n = -Dot(Plane, RayOrigin);
	float u = n / d;
	if (u < 0.0f) return false;
	Intersection = RayOrigin + RayDir*u;
	return true;
}
bool PtInTriangle(VECTOR4D& V0, VECTOR4D& V1, VECTOR4D& V2, VECTOR4D& P,
	float& w1, float& w2)
{
	VECTOR4D D0 = V1 - V0;
	VECTOR4D D1 = V2 - V0;
	float A = Dot(P - V0, D0);
	float B = Dot(D0, D0);
	float C = Dot(D1, D0);
	float D = Dot(P - V0, D1);
	//float E = C;
	float F = Dot(D1, D1);
	float det = B*F - C*C;
	if (fabsf(det) < 0.001f) return false;
	det = 1 / det;
	w1 = (F*A - C*D)*det;
	w2 = (B*D - C*A)*det;
	return (w1 + w2 <= 1.0f) && (w1 >= 0.0f) && (w2 >= 0.0f);
}

VECTOR4D Truncate(VECTOR4D& F, float _max, float _min)
{
	if (F.x > _max)
	{
		F.x = _max;
	}

	if (F.y > _max)
	{
		F.y = _max;
	}

	if (F.z > _max)
	{
		F.z = _max;
	}

	if (F.x < _min)
	{
		F.x = _max;
	}

	if (F.y < _min)
	{
		F.y = _max;
	}

	if (F.z < _min)
	{
		F.z = _max;
	}


	return F;
}
