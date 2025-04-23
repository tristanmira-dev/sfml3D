#include <SFML/Graphics.hpp>
#include "tests.h"
#include "Matrix.h"
#include "Mesh.h"
#include "Graphics.h"
#include "CommonUtils.h"
#include "FileManager.h"
#include <iostream>
#include <initializer_list>
#include <array>

class SortCriterion {
    public:
        bool operator()(utils::Mesh::Vertices const& prev, utils::Mesh::Vertices const& next) {
            float prevMidZ{};
            float nextMidZ{};
            for (int i{}; i < 3; ++i) {
                prevMidZ += prev[i].coordinates.z;
                nextMidZ += next[i].coordinates.z;
            }

            return prevMidZ / 2.f > nextMidZ / 2.f;
        }
};

int main()
{


    
    tests::runTests();

    utils::Matrix4x4 mtx{};

    utils::Matrix4x4 rotationX{};
    utils::Matrix4x4 rotationY{};


    utils::Mesh tris{};

    manager::FileManager::readVertex("./Assets/knight(b3_6).obj", tris);

    //tris = {

    //    // SOUTH
    //    { 0.0f, 0.0f, 0.0f,    0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 0.0f },
    //    { 0.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0f, 0.0f, 0.0f },

    //    // EAST                                                      
    //    { 1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0f, 1.0f, 1.0f },
    //    { 1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 0.0f, 1.0f },

    //    // NORTH                                                     
    //    { 1.0f, 0.0f, 1.0f,    1.0f, 1.0f, 1.0f,    0.0f, 1.0f, 1.0f },
    //    { 1.0f, 0.0f, 1.0f,    0.0f, 1.0f, 1.0f,    0.0f, 0.0f, 1.0f },

    //    // WEST                                                      
    //    { 0.0f, 0.0f, 1.0f,    0.0f, 1.0f, 1.0f,    0.0f, 1.0f, 0.0f },
    //    { 0.0f, 0.0f, 1.0f,    0.0f, 1.0f, 0.0f,    0.0f, 0.0f, 0.0f },

    //    // TOP                                                       
    //    { 0.0f, 1.0f, 0.0f,    0.0f, 1.0f, 1.0f,    1.0f, 1.0f, 1.0f },
    //    { 0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 1.0f, 0.0f },

    //    // BOTTOM                                                    
    //    { 1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f },
    //    { 1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f,    1.0f, 0.0f, 0.0f },

    //};


    // create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");


    mtx.setProjectionMatrix(window, 0.1f, 1000.0f, 90.0f);

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


        //currentAngle += 0.5f;

        utils::Mesh::VerticesContainer trianglesToDraw;

        for (utils::Mesh::Vertices const& vertices : tris.verticesContainer) {

            utils::Mesh::Vertices translated = vertices;
            utils::Mesh::Vertices projected;

            /*SET ROTATION MATRIX*/
            rotationX.setRotationX(currentXAngle);
            rotationY.setRotationY(currentYAngle);


            /*ROTATION AROUND X TRANSFORMATION*/
            translated[0].coordinates = rotationX * translated[0].coordinates;
            translated[1].coordinates = rotationX * translated[1].coordinates;
            translated[2].coordinates = rotationX * translated[2].coordinates;
            /*-------------------------------*/

            /*ROTATION AROUND Y TRANSFORMATION*/
            translated[0].coordinates = rotationY * translated[0].coordinates;
            translated[1].coordinates = rotationY * translated[1].coordinates;
            translated[2].coordinates = rotationY * translated[2].coordinates;
            /*-------------------------------*/

            /*TRANSLATE OBJECT to +2 IN THE Z AXIS TO BE SEEN IN THE SCREEN SPACE*/
            translated[0].coordinates.z += 2.0f;
            translated[1].coordinates.z += 2.0f;
            translated[2].coordinates.z += 2.0f;
            /*------------------------------------------------------------------*/

            utils::Vector3D vec1, vec2, normal;

            /*CALCULATE THE NORMAL OF EACH TRIANGLE FACE IN THE PLANE*/
            vec1 = translated[1].coordinates - translated[0].coordinates;
            vec2 = translated[2].coordinates - translated[0].coordinates;
            normal = vec1.cross(vec2); //CROSS PRODUCT BETWEEN TWO VECTORS TO GET THE NORMAL VECTOR
            /*------------------------------------------------------*/

            currentYAngle += (currentYAngle > 360.f) ? (currentYAngle = 0.f) : 0.0001f;

            /*SET THE VECTOR FROM TRIANGLE PT TO CAMERA(0,0,0) IN ORDER TO DO 'CULLING'*/
            utils::Vector3D lineFromCam = translated[0].coordinates;

            /*CHECK IF THE ANGLE BETWEEN THE NORMAL AND VECTOR FROM CAM IS NEGATIVE(IN FRONT OF THE BACK) THEN CONTINUE WITH PERSPECTIVE PROJECTION*/
            if (lineFromCam.dot(normal) < 0.0f) {

                projected.push_back(
                    {
                        mtx.pMultiply(translated[0].coordinates)
                    }
                );
                projected.push_back({ mtx.pMultiply(translated[1].coordinates) });
                projected.push_back({ mtx.pMultiply(translated[2].coordinates) });

                normal.normalize();
                

                utils::Vector3D light{
                    0.f,
                    0.f,
                    1.0f
                };
                //light.normalize();

                float dist{ std::fabs(normal.dot(light)) };

                /*SCALE UP TO WINDOW DIMENSIONS*/
                projected[0].coordinates.x *= window.getSize().x; projected[0].coordinates.y *= window.getSize().y;
                projected[1].coordinates.x *= window.getSize().x; projected[1].coordinates.y *= window.getSize().y;
                projected[2].coordinates.x *= window.getSize().x; projected[2].coordinates.y *= window.getSize().y;

                projected[0].coordinates.x *= 4.0f; projected[0].coordinates.y *= 4.0f;
                projected[1].coordinates.x *= 4.0f; projected[1].coordinates.y *= 4.0f;
                projected[2].coordinates.x *= 4.0f; projected[2].coordinates.y *= 4.0f;

                /*TRANSLATE TO MIDDLE OF THE SCREEN*/
                projected[0].coordinates.x += window.getSize().x * 0.5f; projected[0].coordinates.y += window.getSize().y * 0.5f;
                projected[1].coordinates.x += window.getSize().x * 0.5f; projected[1].coordinates.y += window.getSize().y * 0.5f;
                projected[2].coordinates.x += window.getSize().x * 0.5f; projected[2].coordinates.y += window.getSize().y * 0.5f;

                projected[0].coordinates.y += 150.0f;
                projected[1].coordinates.y += 150.0f;
                projected[2].coordinates.y += 150.0f;
                
                projected[0].colorVal = dist * 255.f;
                projected[1].colorVal = dist * 255.f;
                projected[2].colorVal = dist * 255.f;



                Render::Graphics::drawTriangle(window, projected, static_cast<sf::Uint8>(projected[0].colorVal));

                trianglesToDraw.push_back(projected);

            }

            


        }

        std::sort(trianglesToDraw.begin(), trianglesToDraw.end(), SortCriterion{});

        for (const utils::Mesh::Vertices& vertices : trianglesToDraw) {
            Render::Graphics::drawTriangle(window, vertices, vertices[0].colorVal);
        }

        window.display();
    }

    return 0;
}