#include "Graphics.h"
#include <SFML/Graphics.hpp>

namespace Render {
    void Graphics::drawTriangle(sf::RenderWindow& context, utils::Mesh::Vertices const& vertices, DrawMode mode) {
        std::vector<sf::Vertex> triangleVertices = {
            sf::Vertex{sf::Vector2f(vertices[0].coordinates.x, vertices[0].coordinates.y)},
            sf::Vertex{sf::Vector2f(vertices[1].coordinates.x, vertices[1].coordinates.y)},
            sf::Vertex{sf::Vector2f(vertices[2].coordinates.x, vertices[2].coordinates.y)}
        };

        

        triangleVertices[0].color = static_cast<sf::Color>(vertices[0].colorVal);
        triangleVertices[1].color = static_cast<sf::Color>(vertices[1].colorVal);
        triangleVertices[2].color = static_cast<sf::Color>(vertices[2].colorVal);

        switch (mode) {
        case TRIANGLE:
            context.draw(triangleVertices.data(), triangleVertices.size(), sf::PrimitiveType::Triangles);
            break;
        case WIREFRAME:
            std::vector<sf::Vertex> lineVertices = {
                sf::Vertex{sf::Vector2f(vertices[0].coordinates.x, vertices[0].coordinates.y)},
                sf::Vertex{sf::Vector2f(vertices[1].coordinates.x, vertices[1].coordinates.y)},
                sf::Vertex{sf::Vector2f(vertices[1].coordinates.x, vertices[1].coordinates.y)},
                sf::Vertex{sf::Vector2f(vertices[2].coordinates.x, vertices[2].coordinates.y)},
                sf::Vertex{sf::Vector2f(vertices[2].coordinates.x, vertices[2].coordinates.y)},
                sf::Vertex{sf::Vector2f(vertices[0].coordinates.x, vertices[0].coordinates.y)}
            };


            context.draw(lineVertices.data(), lineVertices.size(), sf::PrimitiveType::Lines);
            break;
        }



    }
}

