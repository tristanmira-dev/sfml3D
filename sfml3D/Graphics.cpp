#include "Graphics.h"
#include "Vertices.h"
#include <algorithm>
#include <iostream>
#include <chrono>
#include <math.h>

namespace {
    utils::VertexData const*& min(utils::VertexData const *&point1, utils::VertexData const*&point2) {
        return (point1->coordinates.y < point2->coordinates.y) ? point1 : point2;
    }

    /*template<typename T>
    float min(T const &p0, T const& p1, T const& p2) {
        return p0 < p1 && p0 < p2 ? p0 : (p1 < p0 && p1 < p2) ? p1 : (p2 < p1 && p2 < p0) ? p2 : p0 == p1 ? p0 : p2 == p1 ? p1 : p0;
    }
    template<typename T>
    float max(T const& p0, T const& p1, T const& p2) {
        return p0 > p1 && p0 > p2 ? p0 : (p1 > p0 && p1 > p2) ? p1 : (p2 > p1 && p2 > p0) ? p2 : p0 == p1 ? p0 : p2 == p1 ? p1 : p0;
    }*/

    void drawFlatTopTri(SDL_Renderer *&context, utils::VertexData const * const &v0, utils::VertexData const * const &v1, utils::VertexData const * const &v2) {

        float slope0{ (v2->coordinates.x - v0->coordinates.x) / (v2->coordinates.y - v0->coordinates.y) };
        float slope1{ (v2->coordinates.x - v1->coordinates.x) / (v2->coordinates.y - v1->coordinates.y) };


        int startY{ static_cast<int>(ceilf(v0->coordinates.y - 0.5f)) };
        int endY{ static_cast<int>(ceilf(v2->coordinates.y - 0.5f)) };


        SDL_SetRenderDrawColor(context, 255, 255, 255, 255);

        for (int y{ startY }; y < endY; ++y) {
            float newStartXVal{ ((y + 0.5f) - v0->coordinates.y) * slope0 + v0->coordinates.x};
            float newEndXVal{ ((y + 0.5f) - v1->coordinates.y) * slope1 + v1->coordinates.x};


            int startX{static_cast<int>(ceilf(newStartXVal - 0.5f))};
            int endX{static_cast<int>(ceilf(newEndXVal - 0.5f)) };

            for (int x{ startX }; x < endX; ++x) {
                SDL_RenderPoint(context, x, y);
            }
        }

        


    }

    void drawFlatBottomTri(SDL_Renderer*& context, utils::VertexData const* const& v0, utils::VertexData const* const& v1, utils::VertexData const* const& v2) {
        float slope0{ (v1->coordinates.x - v0->coordinates.x) / (v1->coordinates.y - v0->coordinates.y) };
        float slope1{ (v2->coordinates.x - v0->coordinates.x) / (v2->coordinates.y - v0->coordinates.y) };


        int startY{ static_cast<int>(ceilf(v0->coordinates.y - 0.5f)) };
        int endY{ static_cast<int>(ceilf(v2->coordinates.y - 0.5f)) };


        SDL_SetRenderDrawColor(context, 255, 255, 255, 255);

        for (int y{ startY }; y < endY; ++y) {
            float newStartXVal{ ((y + 0.5f) - v0->coordinates.y) * slope0 + v0->coordinates.x };
            float newEndXVal{ ((y + 0.5f) - v0->coordinates.y) * slope1 + v0->coordinates.x };


            int startX{ static_cast<int>(ceilf(newStartXVal - 0.5f)) };
            int endX{ static_cast<int>(ceilf(newEndXVal - 0.5f)) };

            for (int x{ startX }; x < endX; ++x) {
                SDL_RenderPoint(context, x, y);
            }
        }
    }
}

namespace Render {
    void Graphics::drawTriangle(SDL_Renderer*& renderer, utils::Vertices const &vertices, DrawMode mode) {
        

        std::chrono::system_clock::time_point currentTime{ std::chrono::system_clock::now() };

        utils::VertexData const* v0{ &vertices.container[0] };
        utils::VertexData const* v1{ &vertices.container[1] };
        utils::VertexData const* v2{ &vertices.container[2] };

        std::swap(v0, min(min(v0, v1), v2)); std::swap(v1, min(v1, v2));

        
        if (v0->coordinates.y == v1->coordinates.y) {
            if (v0->coordinates.x > v1->coordinates.x) {
                std::swap(v0, v1);
            }
            drawFlatTopTri(renderer,v0,v1,v2);
            return;
        } 
        
        if (v1->coordinates.y == v2->coordinates.y) {
            if (v1->coordinates.x > v2->coordinates.x) {
                std::swap(v1, v2);
            }
            drawFlatBottomTri(renderer, v0, v1, v2);
            return;
        }

        float alpha{ (v1->coordinates.y - v0->coordinates.y) / (v2->coordinates.y - v0->coordinates.y) };

        utils::VertexData vi{ v0->coordinates + alpha * (v2->coordinates - v0->coordinates) };
        
        /*2 LEFT EDGE TRIANGLE*/
        if (v1->coordinates.x < vi.coordinates.x) {
            drawFlatBottomTri(renderer,v0, v1, &vi);
            drawFlatTopTri(renderer,v1, &vi, v2);
        }
        else { /*2 RIGHT EDGE TRIANGLE*/
            drawFlatBottomTri(renderer,v0, &vi, v1);
            drawFlatTopTri(renderer,&vi, v1, v2);
        }
        
    }
}

