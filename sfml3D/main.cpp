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



/**/

int main(int argc, char *argv[]) {

    SDL_Window* window{ nullptr };
    SDL_Renderer* renderer{ nullptr };

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
                    "./Assets/test.obj",
                    utils::Color{255, 255, 255, 255}
                }
            }, camera
        }
    );

    std::chrono::system_clock::time_point currentTime{ std::chrono::system_clock::now() };
    std::chrono::duration<float> deltaTime{};
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

        eventLoop.draw(renderer,window, mtx);
        
        //SDL_RenderLine
        SDL_RenderPresent(renderer);
    }
    


    

    /*float currentXAngle = 50.0f;
    float currentYAngle = 0.0f;*/

   /* std::chrono::system_clock::time_point currentTime{ std::chrono::system_clock::now() };
    std::chrono::duration<float> deltaTime{};*/
    


    // run the program as long as the window is open
    //while (window.isOpen())
    //{

    //    
    //    // check all the window's events that were triggered since the last iteration of the loop
    //    sf::Event event;
    //    while (window.pollEvent(event))
    //    {
    //        // "close requested" event: we close the window
    //        if (event.type == sf::Event::Closed)
    //            window.close();
    //    }

    //    std::chrono::system_clock::time_point newTime{ std::chrono::system_clock::now() };
    //    deltaTime = newTime - currentTime;
    //    currentTime = newTime;




    //    /*utils::Vector3D currentCameraLoc{ camera.getPosition() };

    //    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D)) {
    //        camera.translateRight(20.5f * deltaTime.count());
    //    }
    //    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A)) {
    //        camera.translateRight(-20.5f * deltaTime.count());
    //    }

    //    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::W)) {
    //        camera.translateForward(20.5f * deltaTime.count());
    //    }
    //    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::S)) {
    //        camera.translateForward(-20.5f * deltaTime.count());
    //    } if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Up)) {
    //        camera.incDecPitch(100.f * deltaTime.count());
    //    } if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Down)) {
    //        camera.incDecPitch(-100.f * deltaTime.count());
    //    } if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Left)) {
    //        camera.incDecYaw(-100.f * deltaTime.count());
    //    } if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Right)) {
    //        camera.incDecYaw(100.f * deltaTime.count());
    //    }

    //    utils::Matrix4x4 translate3{
    //        {1.f, 0.f, 0.f, 6.f},
    //        {0.f, 1.f, 0.f, 0.f},
    //        {0.f, 0.f, 1.f, 8.f},
    //        {0.f, 0.f, 0.f, 1.f}
    //    };

    //    utils::Matrix4x4 translate4{
    //        {1.f, 0.f, 0.f, 9.f},
    //        {0.f, 1.f, 0.f, 0.f},
    //        {0.f, 0.f, 1.f, 8.f},
    //        {0.f, 0.f, 0.f, 1.f}
    //    };

    //    utils::Matrix4x4 translate5{
    //       {1.f, 0.f, 0.f, 12.f},
    //       {0.f, 1.f, 0.f, 0.f},
    //       {0.f, 0.f, 1.f, 8.f},
    //       {0.f, 0.f, 0.f, 1.f}
    //    };

    //    utils::Matrix4x4 translate6{
    //       {1.f, 0.f, 0.f, 15.f},
    //       {0.f, 1.f, 0.f, 0.f},
    //       {0.f, 0.f, 1.f, 8.f},
    //       {0.f, 0.f, 0.f, 1.f}
    //    };

    //    utils::Matrix4x4 translateGameObj = {
    //        {1,0,0,0.f}, {0,1,0,0.f}, {0,0,1,8.f}, {0,0,0,1}
    //    };

    //    utils::Matrix4x4 translateGameObj2 = {
    //        {1,0,0,3.f}, {0,1,0,0.f}, {0,0,1,8.f}, {0,0,0,1}
    //    };

    //    rotationY.setRotationX(180.f);
    //    eventLoop.clear();

    //    eventLoop[0][0].setTransform(translateGameObj * rotationY);

    //    eventLoop[1][0].setTransform(translateGameObj2 * rotationY);

    //    eventLoop[2][0].setTransform(translate3 * rotationY);

    //    eventLoop[3][0].setTransform(translate4 * rotationY);
    //    eventLoop[4][0].setTransform(translate5 * rotationY);
    //    eventLoop[5][0].setTransform(translate6 * rotationY);

    //    eventLoop.draw(window, mtx);

    //    currentTime = newTime;*/
    //    
    //    window.display();

    //    window.draw(wow);
    //}

    return 0;
}