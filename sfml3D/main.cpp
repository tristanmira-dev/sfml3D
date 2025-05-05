#include <SFML/Graphics.hpp>
#include "tests.h"
#include "Matrix.h"
#include "Mesh.h"
#include "Graphics.h"
#include "Color.h"
#include "CommonUtils.h"
#include "GameObject.h"
#include "FileManager.h"
#include <iostream>
#include <initializer_list>
#include <array>




int main() {

    tests::runTests();

    utils::Matrix4x4 mtx{};

    utils::Matrix4x4 rotationX{};
    utils::Matrix4x4 rotationY{};

    // create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");


    mtx.setProjectionMatrix(window, 0.1f, 1000.0f, 30.0f);

    Entity::GameObject<1> model1{ {"./Assets/Suzanne.obj" , utils::Color{255.f, 255.f, 255.f, 255.f}} };

    /*float currentXAngle = 50.0f;
    float currentYAngle = 0.0f;*/

    float currentXPos{ 0.f };
    float currentZPos{ 15.f };


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

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D)) {
            currentXPos -= 0.2f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A)) {
            currentXPos += 0.2f;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::W)) {
            currentZPos -= 0.2f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::S)) {
            currentZPos += 0.2f;
        }


        utils::Matrix4x4 translate = {
            {1,0,0,currentXPos}, {0,1,0,0.f}, {0,0,1,currentZPos}, {0,0,0,1}
        };

        rotationY.setRotationX(180.f);

        model1[0].setTransform(translate * rotationY);

        // clear the window with black color
        window.clear(sf::Color::Black);


        model1.draw(window, mtx);

        window.display();
    }

    return 0;
}