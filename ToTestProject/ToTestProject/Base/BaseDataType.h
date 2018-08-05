#pragma once

#include <iostream>
#include <cmath>

#include <string>
#include "BaseRandomEngine.h"

#define			INLINE		__inline
#define			PI			3.141592f

/*
BaseDataType
	- Vectors;

*/

//struct FVector2D
//{
//	float x;
//	float y;
//};

struct FVector3D
{
public:
	// Vector's X Value
	float x;

	// Vector's Y Value
	float y;

	// Vector's Z Value
	float z;

public:
	FVector3D() = default;
	~FVector3D() = default;

	INLINE FVector3D(const float inX = 0.f, const float inY = 0.f, const float inZ = 0.f)
		: x(inX), y(inY), z(inZ)
	{}

	INLINE FVector3D(const FVector3D& inVector)
		: x(inVector.x), y(inVector.y), z(inVector.z)
	{}

	INLINE FVector3D(const float inValue = 0.f)
		: x(inValue), y(inValue), z(inValue)
	{}

#ifdef _BASE_RANDOM_ENGINE_
	INLINE FVector3D(const bool isGenerateRandomFloat)
	{
		if (isGenerateRandomFloat)
		{
			x = RANDOM::RandomFloat();
			y = RANDOM::RandomFloat();
			z = RANDOM::RandomFloat();
		}
	}

#endif
	
public:
	void PrintAll() const 
	{
		std::cout << "VectorInfo X : " << x << "  Y : " << y << "  Z : " << z << " Size : " << this->Size();
	}

#ifdef _STRING_
	void PrintAll(const std::string inVectorName) const 
	{
		std::cout << " бс " << inVectorName << " ||   X : " << x << ",  Y : " << y << ",  Z : " << z << ", Size : " << this->Size();
	}
#else
	void PrintAll(const char* inVectorName) const
	{
		std::cout << " бс " << inVectorName << " ||   X : " << x << ",  Y : " << y << ",  Z : " << z << ", Size : " << this->Size();
	}
#endif // std::string

public:
	INLINE FVector3D GetZeroVector() const
	{
		//FVector3D ZeroVector = { 0,0,0 };
		//return ZeroVector; 
		return { 0, 0, 0 };
	}

	INLINE FVector3D GetUpVector() const
	{
		return { 0, 0, z };
	}

	INLINE FVector3D GetForwardVector() const
	{
		return { x, 0, 0 };
	}

	INLINE FVector3D GetRightVector() const
	{
		return { 0, y, 0};
	}

	INLINE FVector3D GetReverseVector() const
	{
		return { -x, -y, -z };
	}

	INLINE FVector3D GetNormalVector() const
	{
		const float vectorSize = sqrt((x*x) + (y * y) + (z * z)); //this->Size();
		
		if (vectorSize == 1.f)
		{
			return *this;
		}
		else
		{
			//return (*this / vectorSize);
			const float bufferValue = 1.f / vectorSize;
			return FVector3D(x * bufferValue, y * bufferValue, z * bufferValue);
		}
	}

public:
	//INLINE FVector3D GetSignVector() const
	
	INLINE FVector3D GetZProjectionVector() const
	{
		const float reverseZ = 1.f / z;
		return { x*reverseZ, y*reverseZ, 1};
	}

public:
	INLINE FVector3D operator+(const FVector3D& inV) const
	{
		return FVector3D(x + inV.x, y + inV.y, z + inV.z);
	}

	INLINE FVector3D operator+(const float inValue) const
	{
		return FVector3D(x + inValue, y + inValue, z + inValue);
	}

	INLINE FVector3D operator-(const FVector3D& inV) const
	{
		return FVector3D(x - inV.x, y - inV.y, z - inV.z);
	}

	INLINE FVector3D operator-(const float inValue) const
	{
		return FVector3D(x - inValue, y - inValue, z - inValue);
	}

	INLINE FVector3D operator*(const FVector3D& inV) const
	{
		return FVector3D(x * inV.x, y * inV.y, z * inV.z);
	}

	INLINE FVector3D operator*(const float inValue) const
	{
		return FVector3D(x * inValue, y * inValue, z * inValue);
	}

	INLINE FVector3D operator/(const FVector3D& inV) const
	{
		return FVector3D(x / inV.x, y / inV.y, z / inV.z);
	}

	INLINE FVector3D operator/(const float inValue) const
	{
		const float bufferValue = 1.f / inValue;
		return FVector3D(x * bufferValue, y * bufferValue, z * bufferValue);
	}

	INLINE bool operator==(const FVector3D& inV) const
	{
		return x == inV.x && y == inV.y && z == inV.z;
	}

	INLINE bool operator!=(const FVector3D& inV) const
	{
		return x != inV.x || y != inV.y || z != inV.z;
	}

	INLINE float& operator[](const int index)
	{
		if (index == 0)
		{
			return x;
		}
		else if (index == 1)
		{
			return y;
		}
		else if (index == 2)
		{
			return z;
		}
	}

	INLINE float operator[](const int index) const
	{
		if (index == 0)
		{
			return x;
		}
		else if (index == 1)
		{
			return y;
		}
		else if (index == 2)
		{
			return z;
		}
	}

public:
	INLINE void Set(const float inX, const float inY, const float inZ)
	{
		x = inX;
		y = inY;
		z = inZ;
	}

	// Same Function is length()
	INLINE float Size() const
	{
		return sqrt( (x*x) + (y * y) + (z * z) );
	}

	// Same Function is Size()
	INLINE float Length() const
	{
		return sqrt((x*x) + (y * y) + (z * z));
	}

	INLINE float SizeSquared() const
	{
		return x * x + y * y + z * z;
	}

public:

public:
	INLINE FVector3D RadiansToDegrees(const FVector3D& radianVector) const
	{
		return radianVector * (180.f / PI);
	}

	INLINE FVector3D DegreesToRadians(const FVector3D& degreeVector) const
	{
		return degreeVector * (PI / 180.f);
	}
};
