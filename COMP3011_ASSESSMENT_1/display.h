#pragma once
#ifndef DISPLAY_H
#define DISPLAY_H

#include "maths.h"

#define PIXEL_W 1000
#define PIXEL_H 500

vec3 display_buffer[PIXEL_W][PIXEL_H];


void CopyBufferToDisiplayBuffer(vec3 bfr[PIXEL_W][PIXEL_H])
{
    for (int pixel_y = 0; pixel_y < PIXEL_H; pixel_y++)
    {
        for (int pixel_x = 0; pixel_x < PIXEL_W; pixel_x++)
        {
            display_buffer[pixel_x][pixel_y].x = bfr[pixel_x][pixel_y].x;
            display_buffer[pixel_x][pixel_y].y = bfr[pixel_x][pixel_y].y;
            display_buffer[pixel_x][pixel_y].z = bfr[pixel_x][pixel_y].z;
        }
    }
}

#endif //DISPLAY_H
