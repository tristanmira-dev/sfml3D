#include "Graphics.hpp"
#include <SFML/Graphics.hpp>

void Render::Graphics::drawTriangle(sf::RenderWindow &context, utils::Mesh::Vertices const& vertices, sf::Uint8 colVal, DrawMode mode) {
    std::vector<sf::Vertex> triangleVertices = {
        sf::Vertex{sf::Vector2f(vertices[0].x, vertices[0].y)},
        sf::Vertex{sf::Vector2f(vertices[1].x, vertices[1].y)},
        sf::Vertex{sf::Vector2f(vertices[2].x, vertices[2].y)}
    };

    triangleVertices[0].color = sf::Color{ colVal, colVal, colVal, 255 };
    triangleVertices[1].color = sf::Color{ colVal, colVal, colVal, 255 };
    triangleVertices[2].color = sf::Color{ colVal, colVal, colVal, 255 };

    switch (mode) {
        case TRIANGLE:
            context.draw(triangleVertices.data(), triangleVertices.size(), sf::PrimitiveType::Triangles);
            break;
        case WIREFRAME:
            std::vector<sf::Vertex> lineVertices = {
                sf::Vertex{sf::Vector2f(vertices[0].x, vertices[0].y)},
                sf::Vertex{sf::Vector2f(vertices[1].x, vertices[1].y)},
                sf::Vertex{sf::Vector2f(vertices[1].x, vertices[1].y)},
                sf::Vertex{sf::Vector2f(vertices[2].x, vertices[2].y)},
                sf::Vertex{sf::Vector2f(vertices[2].x, vertices[2].y)},
                sf::Vertex{sf::Vector2f(vertices[0].x, vertices[0].y)}
            };


            context.draw(lineVertices.data(), lineVertices.size(), sf::PrimitiveType::Lines);
            break;
    }


    
}
