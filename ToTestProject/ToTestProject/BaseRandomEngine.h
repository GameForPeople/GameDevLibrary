#pragma once

#ifndef _BASE_RANDOM_ENGINE_
#define _BASE_RANDOM_ENGINE_

#include <iostream>
#include <random>
#include <ctime>

#define ClampNumber 3.0f // that mean 0.000 float only three! -> change ok!


namespace RANDOM {
	// std::default_random_engine defaultRandomEngine;
	// std::uniform_int_distribution<int> uniformInt (-10000, 10000);

	static void InitRandomEngine() 
	{
		srand((unsigned)time(NULL));
	}

	// Function return Value is 0 ~ 1 random float
	static float ClampFloat(float inFloat)
	{
		return ((int)(inFloat * pow(10.0, ClampNumber))) / pow(10.0, ClampNumber);
	}

	static float RandomNormalizeFloat()
	{
		return ClampFloat(rand() / (float)RAND_MAX);
	}

	static float RandomFloat() 
	{
		return ClampFloat(rand() / (float)RAND_MAX) + rand();
	}

}
#endif