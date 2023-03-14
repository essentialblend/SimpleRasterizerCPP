#pragma once
#include "display.h"
#include "maths.h"

#define BUFFER_W PIXEL_W
#define BUFFER_H PIXEL_H
vec3 colour_buffer[BUFFER_W][BUFFER_H];

/*DONE!*/
void ClearColourBuffer(float col[4])
{
	/*Convert between 0-255 and fill the colour_buffer array.*/
	for (int pixelX = 0; pixelX < BUFFER_W; pixelX++)
	{
		for (int pixelY = 0; pixelY < BUFFER_H; pixelY++)
		{
			colour_buffer[pixelX][pixelY].x = col[0] * 255;
			colour_buffer[pixelX][pixelY].y = col[1] * 255;
			colour_buffer[pixelX][pixelY].z = col[2] * 255;
		}
	}
	/*Copy this data to the display buffer which will get used later.*/
	CopyBufferToDisiplayBuffer(colour_buffer);
}

triangle* AssembleTriangles(float* verts, int num_verts, int* num_tris)
{
	return NULL;
}

void TransformToScreenSpace(int w, int h, triangle* t)
{

}

void ComputeBarycentricCoordinates(int px, int py, triangle t, float& alpha, float& beta, float& gamma)
{

}

void ShadeFragment(triangle t, float& alpha, float& beta, float& gamma, float& r, float& g, float& b)
{

}

void Rasterise(triangle* tris, int num_tris)
{
	/*Pseudo code*/
	/*
	for each pixel y in Y dimension
	{
		for each pixel x in X dimension
		{
			for each triangle t
			{
				if pixel x,y is inside triangle t
				{
					calculate the fragment colour
				}
			}
		}
	}
	*/


}

void Draw(int num_verts)
{
}
