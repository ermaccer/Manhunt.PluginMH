#pragma once
#include <math.h>
struct CVector2D {
	float x, y;
};

inline float RecipSqrt(float x, float y) { return (float)(x / sqrt(y)); }
inline float RecipSqrt(float x) { return (float)RecipSqrt(1.0f, x); }

class CVector
{
public:
	float x, y, z;
	CVector(void) {}
	CVector(float a, float b, float c)
	{
		x = a;
		y = b;
		z = c;
	}
	float Heading(void) const { return (float)atan2(-x, y); }
	float Magnitude(void) const { return (float)sqrt(x*x + y * y + z * z); }
	float MagnitudeSqr(void) const { return x * x + y * y + z * z; }
	float Magnitude2D(void) const { return (float)sqrt(x*x + y * y); }
	float MagnitudeSqr2D(void) const { return x * x + y * y; }
	void Normalise(void) {
		float sq = MagnitudeSqr();
		if (sq > 0.0f) {
			float invsqrt = RecipSqrt(sq);
			x *= invsqrt;
			y *= invsqrt;
			z *= invsqrt;
		}
		else
			x = 1.0f;
	}

	void Normalise2D(void) {
		float sq = MagnitudeSqr2D();
		float invsqrt = RecipSqrt(sq);
		x *= invsqrt;
		y *= invsqrt;
	}

	const CVector &operator+=(CVector const &right) {
		x += right.x;
		y += right.y;
		z += right.z;
		return *this;
	}

	const CVector &operator+=(float const &right) {
		x += right;
		y += right;
		z += right;
		return *this;
	}

	const CVector &operator-=(CVector const &right) {
		x -= right.x;
		y -= right.y;
		z -= right.z;
		return *this;
	}

	const CVector &operator*=(float right) {
		x *= right;
		y *= right;
		z *= right;
		return *this;
	}

	const CVector &operator/=(float right) {
		x /= right;
		y /= right;
		z /= right;
		return *this;
	}

	CVector operator-() const {
		return CVector(-x, -y, -z);
	}

	const bool operator==(CVector const &right) {
		return x == right.x && y == right.y && z == right.z;
	}

	const bool operator!=(CVector const &right) {
		return x != right.x || y != right.y || z != right.z;
	}

	bool IsZero(void) const { return x == 0.0f && y == 0.0f && z == 0.0f; }
};

inline CVector operator+(const CVector &left, const CVector &right)
{
	return CVector(left.x + right.x, left.y + right.y, left.z + right.z);
}

inline CVector operator-(const CVector &left, const CVector &right)
{
	return CVector(left.x - right.x, left.y - right.y, left.z - right.z);
}

inline CVector operator*(const CVector &left, float right)
{
	return CVector(left.x * right, left.y * right, left.z * right);
}

inline CVector operator*(float left, const CVector &right)
{
	return CVector(left * right.x, left * right.y, left * right.z);
}

inline CVector operator/(const CVector &left, float right)
{
	return CVector(left.x / right, left.y / right, left.z / right);
}

inline float
DotProduct(const CVector &v1, const CVector &v2)
{
	return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}

CVector CrossProduct(const CVector &v1, const CVector &v2);

inline float
Distance(const CVector &v1, const CVector &v2)
{
	return (v2 - v1).Magnitude();
}

inline float
Distance2D(const CVector &v1, const CVector &v2)
{
	float x = v2.x - v1.x;
	float y = v2.y - v1.y;
	return (float)sqrt(x*x + y * y);
}