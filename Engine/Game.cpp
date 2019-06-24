/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd )
{
}

void Game::Go()
{
	gfx.BeginFrame();
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void DrawCell(float x, float y, float width, float height, int c, Graphics& gfx)
{
	for (int Y = y; Y < y + height; Y++)
	{
		for (int X = x; X < x + width; X++)
		{
			gfx.PutPixel(X, Y, c,c,c);
		}
	}
}

void Game::UpdateModel()
{
	if (wnd.kbd.KeyIsPressed(VK_SPACE))
	{
		inc += 0.015625f;
	}
	if (wnd.kbd.KeyIsPressed('W'))
	{
		ANGLE += 0.015625f;
	}
	if (wnd.kbd.KeyIsPressed('S'))
	{
		ANGLE -= 0.015625f;
	}

	float yoff = 0.0f;
	for (int j = 0; j < v.GetRows(); j++, yoff += inc)
	{
		float xoff = 0.0f;
		for (int i = 0; i < v.GetCollumns(); i++, xoff += inc)
		{
			//int c = noise.PerlinNoise_2D(xoff, yoff) * 255;

			//DrawCell(i*v.patch[0].Dimension, j*v.patch[0].Dimension, v.patch[0].Dimension, v.patch[0].Dimension, c, gfx);
			float angle = noise.PerlinNoise_3D(xoff, yoff, time) * 6.2831853f;
			assert(angle > 0.001f);
			float vLenght = 10.0f;

			v.Update(Vec2(cos(angle) * vLenght, sin(angle) * vLenght), i + j * v.GetCollumns());
		}
	}

	time += 0.5f;
}

void Game::ComposeFrame()
{	
	gfx.DrawLine(Vec2(Graphics::ScreenWidth / 2, Graphics::ScreenHeight / 2), 
		Vec2((Graphics::ScreenWidth/2) + cos(ANGLE)* (-1 + Graphics::ScreenWidth/2),
		(Graphics::ScreenHeight / 2) + sin(ANGLE)* (-1 + Graphics::ScreenHeight / 2)), Color(0, 255, 0));
	v.DrawVectorsWithSameLenghts(gfx);
}
