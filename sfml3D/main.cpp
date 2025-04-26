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

    manager::FileManager::readVertex("./Assets/kindred_sketchfab1.obj", tris);

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



        currentYAngle += 20.f;

        utils::Mesh::VerticesContainer trianglesToDraw;

        for (utils::Mesh::Vertices const& vertices : tris.verticesContainer) {

            utils::Mesh::Vertices translated = vertices;
            utils::Mesh::Vertices projected;

            /*SET ROTATION MATRIX*/
            rotationX.setRotationX(currentXAngle);
            rotationY.setRotationY(currentYAngle);

            /*ROTATION AROUND Y THEN TRANSLATION BY Z AXIS*/
            utils::Matrix4x4 finalTransform = utils::Matrix4x4{ {1,0,0,0}, {0,1,0,0}, {0,0,1,1.f}, {0,0,0,1} } * rotationY;
            utils::Mesh::transformVertice(finalTransform, translated);
            /*-------------------------------*/

            utils::Vector3D vec1, vec2, normal;

            /*CALCULATE THE NORMAL OF EACH TRIANGLE FACE IN THE PLANE*/
            vec1 = translated[1].coordinates - translated[0].coordinates;
            vec2 = translated[2].coordinates - translated[0].coordinates;
            normal = vec1.cross(vec2); //CROSS PRODUCT BETWEEN TWO VECTORS TO GET THE NORMAL VECTOR
            /*------------------------------------------------------*/


            /*SET THE VECTOR FROM TRIANGLE PT TO CAMERA(0,0,0) IN ORDER TO DO 'CULLING'*/
            utils::Vector3D lineFromCam = translated[0].coordinates;

            /*CHECK IF THE ANGLE BETWEEN THE NORMAL AND VECTOR FROM CAM IS NEGATIVE(IN FRONT OF THE BACK) THEN CONTINUE WITH PERSPECTIVE PROJECTION*/
            if (lineFromCam.dot(normal) < 0.0f) {

                projected.push_back({ mtx.pMultiply(translated[0].coordinates) });
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
                
                float halfDistX{ window.getSize().x * 0.5f };
                float halfDistY{ window.getSize().y * 0.5f };

                /*SCALE UP TO WINDOW DIMENSIONS AND THEN TRANSLATE TO MIDDLE OF SCREEN*/
                utils::Matrix4x4 transform2 = utils::Matrix4x4{
                    {1, 0, 0, halfDistX},
                    {0, 1, 0, halfDistY},
                    {0, 0, 1, 0},
                    {0, 0, 0, 1}
                } * utils::Matrix4x4 {
                    {4.f*static_cast<float>(window.getSize().x), 0, 0, 0}, 
                    {0, 4.f*static_cast<float>(window.getSize().y), 0, 0}, 
                    {0, 0, 1, 0}, 
                    {0,0,0,1} 
                };

                utils::Mesh::transformVertice(transform2, projected);

                
                projected[0].colorVal = dist * 255.f;
                projected[1].colorVal = dist * 255.f;
                projected[2].colorVal = dist * 255.f;

                trianglesToDraw.push_back(projected);

            }

        }

        /*SORT THE PROJECTED VERTICES STARTING FROM THE VERTICES WITH A LARGER Z VALUE(GOING FURTHER FROM PLAYER) 
        TO THE VERTICES WITH THE SMALLER Z VALUE(GOING TOWARDS PLAYER) TO DRAW THE VERTICES BEHIND FIRST*/
        std::sort(trianglesToDraw.begin(), trianglesToDraw.end(), SortCriterion{});

        for (const utils::Mesh::Vertices& vertices : trianglesToDraw) {
            Render::Graphics::drawTriangle(window, vertices, static_cast<sf::Uint8>(vertices[0].colorVal));
        }

        window.display();
    }

    return 0;
}