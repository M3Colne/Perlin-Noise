#pragma once

#include "Graphics.h"
#include <assert.h>

class VectorField
{
private:
	//Variables
	static constexpr int Rows = 33; //It must be odd so that It can have a center
	static constexpr int Collumns = 33; //It must be odd so that It can have a center

	struct VectorField_Patch
	{
		Vec2 direction = { 0.0000000f, 0.0000000f };
		static constexpr int Dimension = Graphics::ScreenWidth / Rows;
	};

	float maxL = 0.0f;
	float minL = 0.0f;
	//Variables
public:
	//Variables
	VectorField_Patch patch[Rows * Collumns];
	//Variables
private:
	//Functions
	//I found out about this function here http://p5js.org/examples/math-map.html
	//Press CTRL + F and type "Numero7 Mojeagering". I got the formula from this guy's comment
	float map(float value, float minA, float maxA, float minB, float maxB)
	{
		return (1 - ((value - minA) / (maxA - minA))) * minB + ((value - minA) / (maxA - minA)) * maxB;
	}

	int GetIdFromPos(int x, int y)
	{
		return y * VectorField::Collumns + x;
	}
	Vec2 GetPosFromId(int id)
	{
		assert(0 <= id && id < Collumns * Rows);

		for (int i = 0; i < Collumns; i++)
		{
			if (i * Collumns <= id && id < (i + 1) * Collumns)
			{
				return Vec2(float(id - i * Collumns), float(i)); //This vector will be in screen graph not in math graph
			}
		}
	}
	Vec2 TransformScreenToGraph(Vec2 v)
	{
		return Vec2(v.x - int(Collumns / 2), -(v.y - int(Rows / 2)));
	}
	//Functions
public:
	//Functions
	void Update()
	{
		for (int j = 0; j < Rows; j++)
		{
			for (int i = 0; i < Collumns; i++)
			{
				Vec2 patchInGraph = TransformScreenToGraph(Vec2(float(i), float(j)));
				Vec2 VALUE = Function(patchInGraph.x, patchInGraph.y);
				patch[GetIdFromPos(i, j)].direction = VALUE;

				//Finding the extremes of the function
				float L = VALUE.GetLength();
				if (L > maxL)
				{
					maxL = L;
				}
				if (L < minL)
				{
					minL = L;
				}
			}
		}
	}
	void Update(Vec2 VALUE, int i)
	{
		patch[i].direction = VALUE;

		//Finding the extremes of the function
		float L = VALUE.GetLength();
		if (L > maxL)
		{
			maxL = L;
		}
		if (L < minL)
		{
			minL = L;
		}
	}
	void DrawTheFieldPatchesBoxes(Graphics& gfx)
	{
		for (int i = VectorField_Patch::Dimension - 1; i < Graphics::ScreenWidth; i += VectorField_Patch::Dimension)
		{
			gfx.DrawLine(Vec2(float(i), 0), Vec2(float(i), Graphics::ScreenHeight), Colors::MakeRGB(255, 255, 255));
		}

		for (int j = VectorField_Patch::Dimension - 1; j < Graphics::ScreenHeight; j += VectorField_Patch::Dimension)
		{
			gfx.DrawLine(Vec2(0, float(j)), Vec2(Graphics::ScreenWidth, float(j)), Colors::MakeRGB(255, 255, 255));
		}
	}
	void DrawVectorsWithDifLengths(Graphics& gfx)
	{
		for (int j = 0; j < Rows; j++)
		{
			for (int i = 0; i < Collumns; i++)
			{
				Vec2 center(float(i * VectorField_Patch::Dimension + VectorField_Patch::Dimension / 2),
					float(j * VectorField_Patch::Dimension + VectorField_Patch::Dimension / 2));
				float newLenght = map(patch[GetIdFromPos(i, j)].direction.GetLength(), minL, maxL, 0, VectorField_Patch::Dimension / 2);
				//Transform them into screen coordonates so I can draw them
				gfx.DrawLine(center, center +
					Vec2(patch[GetIdFromPos(i, j)].direction.x, -patch[GetIdFromPos(i, j)].direction.y).GetNormalizedTo(
						map(patch[GetIdFromPos(i, j)].direction.GetLength(), minL, maxL, 0, VectorField_Patch::Dimension / 2))
					, Colors::White);
			}
		}
	}
	void DrawVectorsWithSameLenghts(Graphics& gfx)
	{
		for (int j = 0; j < Rows; j++)
		{
			for (int i = 0; i < Collumns; i++)
			{
				Vec2 center(float(i * VectorField_Patch::Dimension + VectorField_Patch::Dimension / 2),
					float(j * VectorField_Patch::Dimension + VectorField_Patch::Dimension / 2));
				//Transform them into screen coordonates so I can draw them
				gfx.DrawLine(center, center +
					Vec2(patch[GetIdFromPos(i, j)].direction.x, -patch[GetIdFromPos(i, j)].direction.y).GetNormalizedTo(
						VectorField_Patch::Dimension / 2), Colors::White);
			}
		}
	}

	int GetRows()
	{
		return Rows;
	}
	int GetCollumns()
	{
		return Collumns;
	}
	float GetmaxLength()
	{
		return maxL;
	}
	float GetminLength()
	{
		return minL;
	}
	Vec2 Function(float x, float y)
	{
		return Vec2(y, -x);
	}

	//Del operations
	//Del operations
	//Functions
};