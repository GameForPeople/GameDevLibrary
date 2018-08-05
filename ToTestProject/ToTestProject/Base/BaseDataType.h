#pragma once

#include <math.h>

/*
BaseDataType
	- Vectors;

*/

struct FVector2D
{
	float x;
	float y;
};

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
	FVector3D GetZeroVector() const
	{
		//FVector3D ZeroVector = { 0,0,0 };
		//return ZeroVector; 
		return { 0, 0, 0 };
	}

	FVector3D GetUpVector() const
	{
		return { 0, 0, z };
	}

	FVector3D GetForwardVector() const
	{
		return { x, 0, 0 };
	}

	FVector3D GetRightVector() const
	{
		return { 0, y, 0};
	}

public:
	void Set(const float inX, const float inY, const float inZ)
	{
		x = inX;
		y = inY;
		z = inZ;
	}

	float Size() const
	{
		sqrt( (x*x) + (y * y) + (z * z) );
	}
};

namespace Vector2
{

}

namespace Vector3
{

}