#ifndef MATHS_H
#define MATHS_H
#include "stdafx.h"
#include "Vector2f.h"

constexpr float PI = 3.14159265f;

template <typename T>
T toRadians(T degrees)
{
    return (degrees * PI / 180);
}

template <typename T>
T toDegrees(T radians)
{
    return ((radians * 180) / PI);
}

// Test functions
void DrawCircle(SDL_Renderer& renderer, const int centreX, const int centreY, const int radius)
{
    const int diameter = (radius * 2);

    int x = (radius - 1);
    int y = 0;
    int tx = 1;
    int ty = 1;
    int error = (tx - diameter);

    while (x >= y)
    {
        //  Each of the following renders an octant of the circle
        SDL_RenderDrawPoint(&renderer, centreX + x, centreY - y);
        SDL_RenderDrawPoint(&renderer, centreX + x, centreY + y);
        SDL_RenderDrawPoint(&renderer, centreX - x, centreY - y);
        SDL_RenderDrawPoint(&renderer, centreX - x, centreY + y);
        SDL_RenderDrawPoint(&renderer, centreX + y, centreY - x);
        SDL_RenderDrawPoint(&renderer, centreX + y, centreY + x);
        SDL_RenderDrawPoint(&renderer, centreX - y, centreY - x);
        SDL_RenderDrawPoint(&renderer, centreX - y, centreY + x);

        if (error <= 0)
        {
            ++y;
            error += ty;
            ty += 2;
        }

        if (error > 0)
        {
            --x;
            tx += 2;
            error += (tx - diameter);
        }
    }
}

#endif
