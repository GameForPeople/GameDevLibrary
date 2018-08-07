#pragma once

#include "_DefineHeader.h"
#include "Vector3D.h"

#ifndef ___Quaternion___
#define ___Quaternion___

class FQuaternion {
public:
	// FQuaternion's W Value
	float w;

	// FQuaternion's X Value
	float x;

	// FQuaternion's Y Value
	float y;

	// FQuaternion's Z Value
	float z;
	
public:
	INLINE FQuaternion() = default;
	
	INLINE~FQuaternion() = default;

	INLINE FQuaternion(const float inW = 0, const float inX = 0, const float inY = 0, const float inZ = 0)
		: w(inW), x(inX), y(inY), z(inZ)
	{
	}

	INLINE FQuaternion(const FQuaternion& inQuaternion)
		: w(inQuaternion.w), x(inQuaternion.x), y(inQuaternion.y), z(inQuaternion.z)
	{
	}

public:
	INLINE FQuaternion GetNormalQuaternion() const
	{
		float sizeBuffer = 1 / sqrtf(w * w + x * x + y * y + z * z);
		return FQuaternion(w * sizeBuffer, x * sizeBuffer, y * sizeBuffer, z *sizeBuffer);
	}

	INLINE void SelfNormalize()
	{
		float sizeBuffer = 1 / sqrtf(w * w + x * x + y * y + z * z);

		w *= sizeBuffer;
		x *= sizeBuffer;
		y *= sizeBuffer;
		z *= sizeBuffer;
	}
	
	// Quaternion = s(w) + V  Conjugate --> s(w) - V
	INLINE FQuaternion GetConjugate() const
	{
		return FQuaternion(w, -x, -y, -z);
	}

	INLINE void SelfConjugate() 
	{
		x = -x;
		y = -y;
		z = -z;
	}

	INLINE void SelfEuler(float inX, float inY, float inZ)
	{
		inX *= 0.0174532925f; // To radians!
		inY *= 0.0174532925f; // To radians!
		inZ *= 0.0174532925f; // To radians!

		inX *= 0.5f;
		inY *= 0.5f;
		inZ *= 0.5f;

		float sinx = sinf(inX);
		float siny = sinf(inY);
		float sinz = sinf(inZ);
		float cosx = cosf(inX);
		float cosy = cosf(inY);
		float cosz = cosf(inZ);

		w = cosx * cosy * cosz + sinx * siny * sinz;
		x = sinx * cosy * cosz + cosx * siny * sinz;
		y = cosx * siny * cosz - sinx * cosy * sinz;
		z = cosx * cosy * sinz - sinx * siny * cosz;
	}

public:
	INLINE float Dot(FQuaternion& inQuaternion) // IN ENEMY!
	{
		return (w * inQuaternion.w + x * inQuaternion.x * y * inQuaternion.y + z * inQuaternion.z);
	}
	
	INLINE float Dot(FQuaternion& aQuaternion, FQuaternion& bQuaternion) {
		return (aQuaternion.w * bQuaternion.w + 
			aQuaternion.x * bQuaternion.x * aQuaternion.y * bQuaternion.y 
			+ aQuaternion.z * bQuaternion.z);
	}

public:
	INLINE bool operator==(const FQuaternion& inQuaternion) const
	{
		return (w == inQuaternion.w && x == inQuaternion.x && y == inQuaternion.y && z == inQuaternion.z);
	}

	INLINE bool operator!=(const FQuaternion& inQuaternion) const
	{
		return (w != inQuaternion.w || x != inQuaternion.x || y != inQuaternion.y || z != inQuaternion.z);
	}

	INLINE FQuaternion& operator=(const FQuaternion& inQuaternion)
	{
		if (this == &inQuaternion) return *this;
		w = inQuaternion.w;
		x = inQuaternion.x;
		y = inQuaternion.y;
		z = inQuaternion.z;
		return *this;
	}

	INLINE FQuaternion& operator*=(const FQuaternion& inQuaternion)
	{
		FQuaternion newQuaternion;

		newQuaternion.w = w * inQuaternion.w - x * inQuaternion.x - y * inQuaternion.y - z * inQuaternion.z;
		newQuaternion.x = w * inQuaternion.x + x * inQuaternion.w + y * inQuaternion.z - z * inQuaternion.y;
		newQuaternion.y = w * inQuaternion.y - x * inQuaternion.z + y * inQuaternion.w + z * inQuaternion.x;
		newQuaternion.z = w * inQuaternion.z + x * inQuaternion.y - y * inQuaternion.x + z * inQuaternion.w;

		*this = newQuaternion;
		return *this;
	}

	INLINE FQuaternion operator*(const FQuaternion& inQuaternion)
	{
		FQuaternion newQuaternion;

		newQuaternion.w = w * inQuaternion.w - x * inQuaternion.x - y * inQuaternion.y - z * inQuaternion.z;
		newQuaternion.x = w * inQuaternion.x + x * inQuaternion.w + y * inQuaternion.z - z * inQuaternion.y;
		newQuaternion.y = w * inQuaternion.y - x * inQuaternion.z + y * inQuaternion.w + z * inQuaternion.x;
		newQuaternion.z = w * inQuaternion.z + x * inQuaternion.y - y * inQuaternion.x + z * inQuaternion.w;

		return newQuaternion;
	}

	INLINE FQuaternion operator*(const float inFloat)
	{
		return FQuaternion(w * inFloat, x * inFloat, y * inFloat, z * inFloat);
	}
	
	INLINE FQuaternion operator+(const FQuaternion& inQuaternion)
	{
		return FQuaternion(w + inQuaternion.w, x + inQuaternion.x, y + inQuaternion.y, z + inQuaternion.z);
	}
	
	INLINE FVector3D operator*(const FVector3D& inVector)
	{
		return FQuaternion::ToMatrix(*this) * inVector;
	}
	
public:
	INLINE void ToAngleAxis(float* retAngle, FVector3D* retAxis)
	{
		*retAngle = acosf(w);
		float sinz = sinf(*retAngle);

		if (fabsf(sinz) > 1e-4f) {
			sinz = 1.0f / sinz;

			retAxis->x = x * sinz;
			retAxis->y = y * sinz;
			retAxis->z = z * sinz;

			*retAngle *= 2.0f * 57.2957795f;
			if (*retAngle > 180.0f)
				*retAngle = 360.0f - *retAngle;
		}
		else {
			*retAngle = 0.0f;
			retAxis->x = 1.0f;
			retAxis->y = 0.0f;
			retAxis->z = 0.0f;
		}
	}

	INLINE void SetLookRotation(FVector3D& lookAt)
	{
		//FVector3D upVector = upVector.GetUpVector();
		//FVector3D forwardVector = lookAt;
		//FVector3D::OrthoNormalize(&forward, &up);
		//Vector right = Vector::Cross(up, forward);
		//
		//w = sqrtf(1.0f + m00 + m11 + m22) * 0.5f;
		//float w4_recip = 1.0f / (4.0f * w);
		//x = (m21 - m12) * w4_recip;
		//y = (m02 - m20) * w4_recip;
		//z = (m10 - m01) * w4_recip;
	}

	// void SetLookRotation(Vector& lookAt, Vector& upDirection);
	// 
	// static Quaternion LookRotation(Vector& lookAt);
	// static Quaternion LookRotation(Vector& lookAt, Vector& upDirection);
	// static Quaternion Slerp(Quaternion& from, Quaternion& to, float t);
	// static Quaternion Lerp(Quaternion& from, Quaternion& to, float t);
	// static float Angle(Quaternion& a, Quaternion& b);
	// static float Dot(Quaternion& a, Quaternion& b);
	// static Quaternion AngleAxis(float angle, Vector& axis);
	// static Quaternion Inverse(Quaternion& rotation);
	// static Quaternion Euler(float X, float Y, float Z);
	// static Matrix ToMatrix(Quaternion& q);
	// 
	// static const Quaternion identity;
};

#endif // ___Quaternion___
