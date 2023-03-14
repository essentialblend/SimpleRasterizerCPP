#pragma once
#ifndef MATHS_H
#define MATHS_H


struct vec3
{
    float x, y, z;
};


struct vertex
{
    vec3 pos;
    vec3 col;
};

struct triangle
{
    vertex v1, v2, v3;
};

#endif //MATHS_H
