#pragma once
#include "display.h"
#include "maths.h"
#include "vertices.h"

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

/*Note- Currently limited to only position and color attributes per vertex for simplicity. Adding more attributes will fail.*/
triangle* AssembleTriangles(float* verts, int num_verts, int* num_tris, int vertArrSize)
{
	//Create a new dynamic array of triangle objects and initialize all their components to 0.0f.
	triangle* arr_assembledTris = new triangle[*num_tris];

	for (int i = 0; i < *num_tris; i++)
	{
		arr_assembledTris[i].v1.col.x = 0.0f;
		arr_assembledTris[i].v1.col.y = 0.0f;
		arr_assembledTris[i].v1.col.z = 0.0f;

		arr_assembledTris[i].v1.pos.x = 0.0f;
		arr_assembledTris[i].v1.pos.y = 0.0f;
		arr_assembledTris[i].v1.pos.z = 0.0f;

		/*-------------------------------*/

		arr_assembledTris[i].v2.col.x = 0.0f;
		arr_assembledTris[i].v2.col.y = 0.0f;
		arr_assembledTris[i].v2.col.z = 0.0f;

		arr_assembledTris[i].v2.pos.x = 0.0f;
		arr_assembledTris[i].v2.pos.y = 0.0f;
		arr_assembledTris[i].v2.pos.z = 0.0f;

		/*-------------------------------*/

		arr_assembledTris[i].v3.col.x = 0.0f;
		arr_assembledTris[i].v3.col.y = 0.0f;
		arr_assembledTris[i].v3.col.z = 0.0f;

		arr_assembledTris[i].v3.pos.x = 0.0f;
		arr_assembledTris[i].v3.pos.y = 0.0f;
		arr_assembledTris[i].v3.pos.z = 0.0f;
	}
	
	/*Assemble each triangle*/
	int plusCount = 0;
	for (int triNum = 0; triNum < *num_tris; triNum++)
	{
		for (int i = plusCount; i < vertArrSize; i += vertArrSize)
		{
			/*Vertex 1*/
			arr_assembledTris[triNum].v1.pos.x = verts[i + 0];
			arr_assembledTris[triNum].v1.pos.y = verts[i + 1];
			arr_assembledTris[triNum].v1.pos.z = verts[i + 2];

			arr_assembledTris[triNum].v1.col.x = verts[i + 3];
			arr_assembledTris[triNum].v1.col.y = verts[i + 4];
			arr_assembledTris[triNum].v1.col.z = verts[i + 5];

			/*Vertex 2*/
			arr_assembledTris[triNum].v2.pos.x = verts[i + 6];
			arr_assembledTris[triNum].v2.pos.y = verts[i + 7];
			arr_assembledTris[triNum].v2.pos.z = verts[i + 8];

			arr_assembledTris[triNum].v2.col.x = verts[i + 9];
			arr_assembledTris[triNum].v2.col.y = verts[i + 10];
			arr_assembledTris[triNum].v2.col.z = verts[i + 11];

			/*Vertex 3*/
			arr_assembledTris[triNum].v3.pos.x = verts[i + 12];
			arr_assembledTris[triNum].v3.pos.y = verts[i + 13];
			arr_assembledTris[triNum].v3.pos.z = verts[i + 14];

			arr_assembledTris[triNum].v3.col.x = verts[i + 15];
			arr_assembledTris[triNum].v3.col.y = verts[i + 16];
			arr_assembledTris[triNum].v3.col.z = verts[i + 17];
		}
		plusCount += 18;
	}
	return arr_assembledTris;
}

void TransformToScreenSpace(float w, float h, triangle* t)
{
	t->v1.pos.x = float((t->v1.pos.x + 1.0) * (w / 2));
	t->v1.pos.y = float((t->v1.pos.y + 1.0) * (h / 2));
	
	t->v2.pos.x = float((t->v2.pos.x + 1.0) * (w / 2));
	t->v2.pos.y = float((t->v2.pos.y + 1.0) * (h / 2));

	t->v3.pos.x = float((t->v3.pos.x + 1.0) * (w / 2));
	t->v3.pos.y = float((t->v3.pos.y + 1.0) * (h / 2));
}

void ComputeBarycentricCoordinates(int px, int py, triangle t, float& alpha, float& beta, float& gamma)
{	
	/*Alpha*/
	float lineBCP = ((t.v3.pos.y - t.v2.pos.y) * px) + ((t.v2.pos.x - t.v3.pos.x) * py) + (t.v3.pos.x * t.v2.pos.y) - (t.v2.pos.x * t.v3.pos.y);
	
	float lineBCA = ((t.v3.pos.y - t.v2.pos.y) * t.v1.pos.x) + ((t.v2.pos.x - t.v3.pos.x) * t.v1.pos.y) + (t.v3.pos.x * t.v2.pos.y) - (t.v2.pos.x * t.v3.pos.y);

	alpha = lineBCP / lineBCA;

	/*Beta*/
	float lineACP = ((t.v3.pos.y - t.v1.pos.y) * px) + ((t.v1.pos.x - t.v3.pos.x) * py) + (t.v3.pos.x * t.v1.pos.y) - (t.v1.pos.x * t.v3.pos.y);

	float lineACB = ((t.v3.pos.y - t.v1.pos.y) * t.v2.pos.x) + ((t.v1.pos.x - t.v3.pos.x) * t.v2.pos.y) + (t.v3.pos.x * t.v1.pos.y) - (t.v1.pos.x * t.v3.pos.y);

	beta = lineACP / lineACB;

	/*Gamma*/
	float lineABP = ((t.v2.pos.y - t.v1.pos.y) * px) + ((t.v1.pos.x - t.v2.pos.x) * py) + (t.v2.pos.x * t.v1.pos.y) - (t.v1.pos.x * t.v2.pos.y);

	float lineABC = ((t.v2.pos.y - t.v1.pos.y) * t.v3.pos.x) + ((t.v1.pos.x - t.v2.pos.x) * t.v3.pos.y) + (t.v2.pos.x * t.v1.pos.y) - (t.v1.pos.x * t.v2.pos.y);
	
	gamma = lineABP / lineABC;

}

void ShadeFragment(triangle t, float& alpha, float& beta, float& gamma, float& r, float& g, float& b)
{
	r = alpha * t.v1.col.x * 255;
	g = beta * t.v2.col.y * 255;
	b = gamma * t.v3.col.z * 255;
}

/*DONE*/
void Rasterise(triangle* tris, int num_tris)
{
	float alpha = 0;
	float beta = 0;
	float gamma = 0;

	/*For every pixel in y.*/
	for (int pY = 0; pY < BUFFER_H; pY++)
	{
		/*For every pixel in x.*/
		for (int pX = 0; pX < BUFFER_W; pX++)
		{
			for (int triNum = 0; triNum < num_tris; triNum++)
			{
				/*Compute their barycentric coordinates.*/
				ComputeBarycentricCoordinates(pX, pY, tris[triNum], alpha, beta, gamma);

				/*If 0 <= ABG <= 1, point in triangle.*/
				if (alpha >= 0 && alpha <= 1 && beta >= 0 && beta <= 1 && gamma >= 0 && gamma <= 1)
				{
					/*Shade that pixel / write to colour buffer.*/
					ShadeFragment(tris[triNum], alpha, beta, gamma, colour_buffer[pX][pY].x, colour_buffer[pX][pY].y, colour_buffer[pX][pY].z);
				}
			}
		}
	}
	/*After writing to colour buffer, copy to display buffer to swap.*/
	CopyBufferToDisiplayBuffer(colour_buffer);
}

/*DONE*/
void Draw(int num_verts)
{
	/*Extrapolating number of triangles from vertices.*/
	int numTris = num_verts / 3;
	/*Extracting size of the vertices array using the base variable in vertices.h*/
	int vertexArraySize = sizeof(verts) / sizeof(verts[0]);
	
	/*Assemble a list of triangles.*/
	triangle* triList = AssembleTriangles(verts, num_verts, &numTris, vertexArraySize);

	/*For each triangle...*/
	for (int triNum = 0; triNum < numTris; triNum++)
	{
		/*Transform to screen space*/
		TransformToScreenSpace(BUFFER_W, BUFFER_H, &triList[triNum]);
	}

	/*Rasterise*/
	Rasterise(triList, numTris);

	/*Handle mem.*/
	delete[] triList;
	triList = nullptr;
}
