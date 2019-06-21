//http://www.arendpeter.com/Perlin_Noise.html
#pragma once

#include <cmath>

class Noise
{
public:
	//Perlin Noise
	static float PerlinNoise_1D(float x, float freq, float ampl) // 1 octave!
	{
		int frequency = int(freq);
		int amplitude = int(ampl);
		return InterpolatedNoise(x * float(frequency)) * float(amplitude);
	}
	static float PerlinNoiseWithOctaves_1D(float x, int nOctaves, float ampl)
	{
		float total = 0.0f;
		float n = nOctaves - 1;

		for (int i = 0; i < n; i++)
		{
			float frequency = 2 * i;
			float amplitude = ampl;
			total += InterpolatedNoise(x * frequency) * amplitude;

		}

		return total;
	}
	static float PerlinNoise_2D(float x, float y, float freq, float ampl) // 1 octave!
	{
		int frequency = int(freq);
		int amplitude = int(ampl);
		return InterpolatedNoise(x * frequency, y * frequency) * amplitude;
	}

	float map(float value, float minA, float maxA, float minB, float maxB)
	{
		return (1 - ((value - minA) / (maxA - minA))) * minB + ((value - minA) / (maxA - minA)) * maxB;
	}
private:
	//Noise
	static float IntNoise(int x)
	{
		x = (x << 13) ^ x;
		return (1.0f - ((x * (x * x * 15731 + 789221) + 1376312589)) / 1073741824);
	}
	static float IntNoise(int x, int y)
	{
		int n = x + y * 57;
		n = (n << 13) ^ n;
		return (1.0f - ((n * (n * n * 15731 + 789221) + 1376312589)) / 1073741824);
	}
	static float SmoothNoise(float x)
	{
		return IntNoise(int(x)) / 2 + IntNoise(int(x) - 1) / 4 + IntNoise(int(x) + 1) / 4;
	}
	static float SmoothNoise(float x, float y)
	{
		float corners = (IntNoise(x - 1, y - 1) + IntNoise(x + 1, y - 1) + IntNoise(x - 1, y + 1) + IntNoise(x + 1, y + 1)) / 16;
		float sides = (IntNoise(x - 1, y) + IntNoise(x + 1, y) + IntNoise(x, y - 1) + IntNoise(x, y + 1)) / 8;
		float center = IntNoise(x, y) / 4;
		return corners + sides + center;
	}

	//Interpolation
	static float Cosine_Interpolate(float a, float b, float x)
	{
		float ft = x * 3.1415927f;
		float f = (1 - cos(ft)) * 0.5f;

		return  a * (1 - f) + b * f;
	}
	static float InterpolatedNoise(float x)
	{
		int integer_X = int(x);
		float fractional_X = x - integer_X;

		float v1 = SmoothNoise(float(integer_X));
		float v2 = SmoothNoise(float(integer_X + 1));

		return Cosine_Interpolate(v1, v2, fractional_X);
	}
	static float InterpolatedNoise(float x, float y)
	{
		int integer_X = int(x);
		float fractional_X = x - integer_X;

		int integer_Y = int(y);
		float fractional_Y = y - integer_Y;

		float v1 = SmoothNoise(integer_X, integer_Y);
		float v2 = SmoothNoise(integer_X + 1, integer_Y);
		float v3 = SmoothNoise(integer_X, integer_Y + 1);
		float v4 = SmoothNoise(integer_X + 1, integer_Y + 1);

		float i1 = Cosine_Interpolate(v1, v2, fractional_X);
		float i2 = Cosine_Interpolate(v3, v4, fractional_X);

		return Cosine_Interpolate(i1, i2, fractional_Y);
	}
};