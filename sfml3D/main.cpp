#include "tests.h"
#include "Matrix.h"
#include "Mesh.h"
#include "Graphics.h"
#include "Color.h"
#include "Camera.h"
#include "CommonUtils.h"
#include "GameObject.h"
#include "FileManager.h"
#include "EventLoop.h"
#include "Vertices.h"
#include <iostream>
#include <chrono>
#include <initializer_list>
#include <array>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <cstring>



/**/

int main(int argc, char *argv[]) {

    //SDL_Color* pixelBuffer{ new SDL_Color[800 * 600] };


    SDL_Window* window{ nullptr };
    SDL_Renderer* renderer{ nullptr };


    

    SDL_FRect rect{};

    Uint32* pixelBuff{ new Uint32[800 * 600] {0xFFFFFFFF} };

    std::fill(pixelBuff, pixelBuff + 800 * 600, 0xFFFFFFFF);

    

    tests::runTests();

    Main::EventLoop eventLoop{};

    utils::Matrix4x4 mtx{};

    utils::Matrix4x4 rotationX{};
    utils::Matrix4x4 rotationY{};

    utils::Camera camera{ utils::Vector3D{0.f, 0.f, 5.f} };

    SDL_CreateWindowAndRenderer("MyWindow", 800, 600, SDL_WINDOW_ALWAYS_ON_TOP, &window, &renderer);
    SDL_Event event;

    mtx.setProjectionMatrix(window, 0.1f, 1000.0f, 30.0f);

    

    

    eventLoop.addGameObject(
        Entity::GameObject<1> {
            std::initializer_list<Entity::EntityInitializer> {
                Entity::EntityInitializer{
                    "./Assets/Suzanne.obj",
                    utils::Color{255, 255, 255, 255}
                }
            }, camera
        }
    );

    std::chrono::system_clock::time_point currentTime{ std::chrono::system_clock::now() };
    std::chrono::duration<float> deltaTime{};

    SDL_Texture* texture{ SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, 800, 600) };
    while (true) {

        std::chrono::time_point newTime{ std::chrono::system_clock::now() };
        deltaTime = newTime - currentTime;
        currentTime = newTime;

        bool const* keystate = SDL_GetKeyboardState(NULL);

        if (keystate[SDL_SCANCODE_UP]) {
            camera.incDecPitch(100.f * deltaTime.count());
        }if (keystate[SDL_SCANCODE_DOWN]) {
            camera.incDecPitch(-100.f * deltaTime.count());
        }if (keystate[SDL_SCANCODE_LEFT]) {
            camera.incDecYaw(-100.f * deltaTime.count());
        }if (keystate[SDL_SCANCODE_RIGHT]) {
            camera.incDecYaw(100.f * deltaTime.count());
        }
        
        
        if (keystate[SDL_SCANCODE_W]) {
            camera.translateForward(20.f * deltaTime.count());
        }if (keystate[SDL_SCANCODE_A]) {
            camera.translateRight(-20.f * deltaTime.count());
        }if (keystate[SDL_SCANCODE_S]) {
            camera.translateForward(-20.f * deltaTime.count());
        }if (keystate[SDL_SCANCODE_D]) {
            camera.translateRight(20.f * deltaTime.count());
        }

        

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_EVENT_WINDOW_RESIZED:
                    std::cout << "Resized";
                    break;
                case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
                    std::cout << "closed";
                    return 0;
                
               
            }
        }

        /*CLEAR PIXEL BUFFER STORED IN RAM BEFORE DRAWING*/
        std::memset(pixelBuff, 0, sizeof(*pixelBuff) * 800 * 600);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        utils::Matrix4x4 translate{
            {1.f, 0.f, 0.f, 0.f},
            {0.f, 1.f, 0.f, 0.f},
            {0.f, 0.f, 1.f, 8.f},
            {0.f, 0.f, 0.f, 1.f}
        };

        eventLoop[0][0].setTransform(translate);

        eventLoop.clear();

        eventLoop.draw(renderer,window, mtx, pixelBuff);
        
        

        SDL_UpdateTexture(texture, nullptr, pixelBuff, 800*4);
        SDL_RenderTexture(renderer, texture, nullptr, nullptr);

        //SDL_RenderLine
        SDL_RenderPresent(renderer);
    }

    delete[] pixelBuff;

    return 0;
}