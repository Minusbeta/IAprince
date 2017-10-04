#pragma once
#pragma once

class VECTOR4D
{
public:
	union
	{
		struct
		{
			float x, y, z, w;
		};
		struct
		{
			float r, g, b, a;
		};
		struct
		{
			unsigned long ulx, uly, ulz, ulw;
		};
		struct
		{
			long lx, ly, lz, lw;
		};
		float v[4];
		unsigned long ul[4];
		long l[4];
	};
	VECTOR4D();
	VECTOR4D(const VECTOR4D& V);
	VECTOR4D(const float fx, const  float fy, const  float fz, const float fw);
	~VECTOR4D();
};
VECTOR4D operator* (const VECTOR4D  &A, const VECTOR4D &B);
VECTOR4D operator* (float s, const VECTOR4D &A);
VECTOR4D operator* (const VECTOR4D &A, float s);
VECTOR4D operator/ (const VECTOR4D &A, float s);
VECTOR4D operator+(const VECTOR4D& A, const VECTOR4D& B);
VECTOR4D operator-(const VECTOR4D& A, const VECTOR4D& B);
float Dot(const VECTOR4D &A, const VECTOR4D &B);
VECTOR4D Cross3(const VECTOR4D& A, const VECTOR4D& B);
float Magnity(const VECTOR4D& A);
VECTOR4D Normalize(const VECTOR4D& A);

bool RayCastOnPlane(VECTOR4D& RayOrigin, VECTOR4D& RayDir,
	VECTOR4D& Plane, VECTOR4D& Intersection);
bool PtInTriangle(VECTOR4D& V0, VECTOR4D& V1, VECTOR4D& V2, VECTOR4D& P,
	float& w1, float& w2);

VECTOR4D Truncate(VECTOR4D& F, float _max, float _min);

