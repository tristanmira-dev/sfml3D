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

//class SortCriterion {
//    public:
//        bool operator()(utils::Mesh::Vertices const& prev, utils::Mesh::Vertices const& next) {
//            float prevMidZ{};
//            float nextMidZ{};
//            for (int i{}; i < 3; ++i) {
//                prevMidZ += prev[i].coordinates.z;
//                nextMidZ += next[i].coordinates.z;
//            }
//
//            return prevMidZ / 2.f > nextMidZ / 2.f;
//        }
//};

int main()
{

    tests::runTests();

    utils::Matrix4x4 mtx{};

    utils::Matrix4x4 rotationX{};
    utils::Matrix4x4 rotationY{};

    // create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");


    mtx.setProjectionMatrix(window, 0.1f, 1000.0f, 90.0f);

    Entity::GameObject<1> model1{ {"./Assets/kindred_sketchfab1.obj" , utils::Color{255.f, 0.f, 0.f, 255.f}} };

    float currentXAngle = 180.0f;
    float currentYAngle = 0.0f;

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

        model1.draw(window, mtx);

        window.display();
    }

    return 0;
}