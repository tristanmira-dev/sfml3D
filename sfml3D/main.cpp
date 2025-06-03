#include <SFML/Graphics.hpp>
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
#include <iostream>
#include <initializer_list>
#include <array>


/**/

int main() {

    tests::runTests();

    Main::EventLoop eventLoop{};

    utils::Matrix4x4 mtx{};

    utils::Matrix4x4 rotationX{};
    utils::Matrix4x4 rotationY{};

    utils::Camera camera{ utils::Vector3D{0.f, 0.f, 0.f} };

    // create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");


    mtx.setProjectionMatrix(window, 0.1f, 1000.0f, 30.0f);

    eventLoop.addGameObject(
        Entity::GameObject<1> {
            std::initializer_list<Entity::EntityInitializer>{
                Entity::EntityInitializer{
                    "./Assets/Suzanne.obj" ,
                    utils::Color{255.f, 255.f, 255.f, 255.f}
                }
            },
            camera
        }
    );

    eventLoop.addGameObject(Entity::GameObject<1>{
        std::initializer_list<Entity::EntityInitializer> {
            Entity::EntityInitializer{
                "./Assets/Suzanne.obj" ,
                utils::Color{255.f, 255.f, 255.f, 255.f}
            }
        },
        camera
        });

    eventLoop.addGameObject(Entity::GameObject<1>{
        std::initializer_list<Entity::EntityInitializer>{
            Entity::EntityInitializer{
                "./Assets/Suzanne.obj" ,
                utils::Color{255.f, 0.f, 255.f, 255.f}
            }
        },
            camera
    });

    eventLoop.addGameObject({
        std::initializer_list<Entity::EntityInitializer>{
            Entity::EntityInitializer{
                "./Assets/Suzanne.obj" ,
                utils::Color{255.f, 0.f, 255.f, 255.f}
            }
        },
        camera
       });

    /*float currentXAngle = 50.0f;
    float currentYAngle = 0.0f;*/



    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        utils::Vector3D currentCameraLoc{ camera.getPosition() };

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D)) {
            camera.translateRight(0.5f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A)) {
            camera.translateRight(-0.5f);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::W)) {
            camera.translateForward(0.5f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::S)) {
            camera.translateForward(-0.5f);
        } if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Up)) {
            camera.incDecPitch(2.5f);
        } if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Down)) {
            camera.incDecPitch(-2.5f);
        } if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Left)) {
            camera.incDecYaw(-2.5f);
        } if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Right)) {
            camera.incDecYaw(2.5f);
        }

        utils::Matrix4x4 translate3{
            {1.f, 0.f, 0.f, 6.f},
            {0.f, 1.f, 0.f, 0.f},
            {0.f, 0.f, 1.f, 8.f},
            {0.f, 0.f, 0.f, 1.f}
        };

        utils::Matrix4x4 translate4{
            {1.f, 0.f, 0.f, 9.f},
            {0.f, 1.f, 0.f, 0.f},
            {0.f, 0.f, 1.f, 8.f},
            {0.f, 0.f, 0.f, 1.f}
        };

        utils::Matrix4x4 translateGameObj = {
            {1,0,0,0.f}, {0,1,0,0.f}, {0,0,1,8.f}, {0,0,0,1}
        };

        utils::Matrix4x4 translateGameObj2 = {
            {1,0,0,3.f}, {0,1,0,0.f}, {0,0,1,8.f}, {0,0,0,1}
        };

        rotationY.setRotationX(180.f);
        eventLoop.clear();

        eventLoop[0][0].setTransform(translateGameObj * rotationY);

        eventLoop[1][0].setTransform(translateGameObj2 * rotationY);

        eventLoop[2][0].setTransform(translate3 * rotationY);

        eventLoop[3][0].setTransform(translate4 * rotationY);

        eventLoop.draw(window, mtx);




      

        window.display();
    }

    return 0;
}