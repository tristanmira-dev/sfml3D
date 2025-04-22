#include <SFML/Graphics.hpp>
#include "tests.hpp"
#include "Matrix.h"
#include "Mesh.h"
#include "Graphics.hpp"
#include <iostream>
#include <initializer_list>
#include <array>

int main()
{
    
    tests::runTests();

    utils::Matrix4x4 mtx{};

    utils::Matrix4x4 rotationX{};


    utils::Mesh tris{};

    tris = {

        // SOUTH
        { 0.0f, 0.0f, 0.0f,    0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0f, 0.0f, 0.0f },

        // EAST                                                      
        { 1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0f, 1.0f, 1.0f },
        { 1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 0.0f, 1.0f },

        // NORTH                                                     
        { 1.0f, 0.0f, 1.0f,    1.0f, 1.0f, 1.0f,    0.0f, 1.0f, 1.0f },
        { 1.0f, 0.0f, 1.0f,    0.0f, 1.0f, 1.0f,    0.0f, 0.0f, 1.0f },

        // WEST                                                      
        { 0.0f, 0.0f, 1.0f,    0.0f, 1.0f, 1.0f,    0.0f, 1.0f, 0.0f },
        { 0.0f, 0.0f, 1.0f,    0.0f, 1.0f, 0.0f,    0.0f, 0.0f, 0.0f },

        // TOP                                                       
        { 0.0f, 1.0f, 0.0f,    0.0f, 1.0f, 1.0f,    1.0f, 1.0f, 1.0f },
        { 0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 1.0f, 0.0f },

        // BOTTOM                                                    
        { 1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f },
        { 1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f,    1.0f, 0.0f, 0.0f },

    };


    // create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");


    mtx.setProjectionMatrix(window, 0.1f, 1000.0f, 90.0f);

    float currentAngle = 20.0f;

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


        currentAngle += 0.05f;

        for (utils::Mesh::Vertices const& vertices : tris.verticesContainer) {

            utils::Mesh::Vertices projected;

            utils::Mesh::Vertices translated = vertices;


            /*SET ROTATION MATRIX*/
            rotationX.setRotationX(currentAngle);


            /*ROTATION AROUND X TRANSFORMATION*/
            translated[0] = rotationX * translated[0];
            translated[1] = rotationX * translated[1];
            translated[2] = rotationX * translated[2];
            /*-------------------------------*/

            /*TRANSLATE OBJECT to +2 IN THE Z AXIS TO BE SEEN IN THE SCREEN SPACE*/
            translated[0].z += 2.0f;
            translated[1].z += 2.0f;
            translated[2].z += 2.0f;
            /*------------------------------------------------------------------*/

            utils::Vector3D vec1, vec2, normal;

            /*CALCULATE THE NORMAL OF EACH TRIANGLE FACE IN THE PLANE*/
            vec1 = translated[1] - translated[0];
            vec2 = translated[2] - translated[0];
            normal = vec1.cross(vec2); //CROSS PRODUCT BETWEEN TWO VECTORS TO GET THE NORMAL VECTOR
            /*------------------------------------------------------*/

            /*SET THE VECTOR FROM TRIANGLE PT TO CAMERA(0,0,0) IN ORDER TO DO 'CULLING'*/
            utils::Vector3D lineFromCam = translated[0];

            /*CHECK IF THE ANGLE BETWEEN THE NORMAL AND VECTOR FROM CAM IS NEGATIVE(IN FRONT OF THE BACK) THEN CONTINUE WITH PERSPECTIVE PROJECTION*/
            if (lineFromCam.dot(normal) < 0.0f) {

                projected.push_back(mtx.pMultiply(translated[0]));
                projected.push_back(mtx.pMultiply(translated[1]));
                projected.push_back(mtx.pMultiply(translated[2]));


                normal.normalize();

                utils::Vector3D light{
                    0.f,
                    0.f,
                    1.0f
                };
                //light.normalize();

                float dist{ std::fabs(normal.dot(light)) };

                /*SCALE UP TO WINDOW DIMENSIONS*/
                projected[0].x *= window.getSize().x; projected[0].y *= window.getSize().y;
                projected[1].x *= window.getSize().x; projected[1].y *= window.getSize().y;
                projected[2].x *= window.getSize().x; projected[2].y *= window.getSize().y;

                projected[0].x *= 2.0f; projected[0].y *= 2.0f;
                projected[1].x *= 2.0f; projected[1].y *= 2.0f;
                projected[2].x *= 2.0f; projected[2].y *= 2.0f;

                /*TRANSLATE TO MIDDLE OF THE SCREEN*/
                projected[0].x += window.getSize().x * 0.5f; projected[0].y += window.getSize().y * 0.5f;
                projected[1].x += window.getSize().x * 0.5f; projected[1].y += window.getSize().y * 0.5f;
                projected[2].x += window.getSize().x * 0.5f; projected[2].y += window.getSize().y * 0.5f;

                Render::Graphics::drawTriangle(window, projected, static_cast<sf::Uint8>(dist*255.f), Render::TRIANGLE);

            }

            
            

            


        }


        // draw everything here...
        // window.draw(...);

        // end the current frame
        window.display();
    }

    return 0;
}