#pragma once

#ifndef _BASE_RANDOM_ENGINE_
#define _BASE_RANDOM_ENGINE_

#include <iostream>
#include <random>
#include <ctime>

#define			___UNIFORM_RANDOM_ENGINE // If you use a lot of getrandomValue Function, you can get a speed benefit by annotating this line;

#define			ClampNumber				3.0f  // that mean 0.000 float only three! -> change ok!
#define			RANDOM_ENGINE_MAX_INT	10000

#define			INLINE		__inline

namespace RANDOM {

	static float ClampFloat(float inFloat)
	{
		return ((int)(inFloat * pow(10.0, ClampNumber))) / pow(10.0, ClampNumber);
	}

	static float RandomFloat()
	{
		return ClampFloat(rand() / (float)RAND_MAX) + rand();
	}

	static float RandomNormalizeFloat()
	{
		return ClampFloat(rand() / (float)RAND_MAX);
	}

}

class URandomEngine
	{
	private:
#ifdef ___UNIFORM_RANDOM_ENGINE
		std::default_random_engine* defaultRandomEngine;
		std::uniform_int_distribution<int>* uniformInt;
#endif // ___UNIFORM_RANDOM_ENGINE

	public:
		INLINE URandomEngine()
		{
			InitRandomEngine();
		}

		INLINE ~URandomEngine()
		{
#ifdef UNIFORM_RANDOM_ENGINE
			delete defaultRandomEngine;
			delete uniformInt;
#endif // UNIFORM_RANDOM_ENGINE
		}

		INLINE void InitRandomEngine()
		{
			srand((unsigned)time(NULL));

#ifdef ___UNIFORM_RANDOM_ENGINE
			defaultRandomEngine = new std::default_random_engine((unsigned)time(NULL));
			uniformInt = new std::uniform_int_distribution<int>(-RANDOM_ENGINE_MAX_INT, RANDOM_ENGINE_MAX_INT);
#endif // ___UNIFORM_RANDOM_ENGINE
		}

	public:
		// Function return Value is 0 ~ 1 random float
		INLINE float ClampFloat(float inFloat)
		{
			return ((int)(inFloat * pow(10.0, ClampNumber))) / pow(10.0, ClampNumber);
		}

		INLINE float RandomNormalizeFloat()
		{
#ifdef ___UNIFORM_RANDOM_ENGINE
			return ClampFloat((*uniformInt)(*defaultRandomEngine) / (float)RANDOM_ENGINE_MAX_INT);
#else
			return ClampFloat(rand() / (float)RAND_MAX);
#endif //___UNIFORM_RANDOM_ENGINE
		}

		INLINE float RandomFloat()
		{
#ifdef ___UNIFORM_RANDOM_ENGINE
			return ClampFloat((*uniformInt)(*defaultRandomEngine) / (float)RANDOM_ENGINE_MAX_INT) + (*uniformInt)(*defaultRandomEngine);
#else
			return ClampFloat(rand() / (float)RAND_MAX) + rand();
#endif //___UNIFORM_RANDOM_ENGINE
		}
	};

#endif // _BASE_RANDOM_ENGINE_
