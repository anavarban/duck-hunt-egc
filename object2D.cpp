#include "object2D.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"


Mesh* object2D::CreateSquare(
    const std::string &name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, length, 0), color),
        VertexFormat(corner + glm::vec3(0, length, 0), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    } else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* object2D::CreateTriangle(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float side,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(side, 0, 0), color),
        VertexFormat(corner + glm::vec3(side * 0.5, side * 0.5 * sqrt(3), 0), color)
    };

    Mesh* triangle = new Mesh(name);
    std::vector<unsigned int> indices = {0, 1, 2};

    triangle->SetDrawMode(GL_TRIANGLES);

    triangle->InitFromData(vertices, indices);
    return triangle;
}

Mesh* object2D::CreateTriangleFromVertexList(
    const std::string& name,
    std::vector<VertexFormat> vertices)
{
    Mesh* triangle = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2 };

    triangle->SetDrawMode(GL_TRIANGLES);

    triangle->InitFromData(vertices, indices);
    return triangle;
}

Mesh* object2D::CreateCircle(
    const std::string& name,
    glm::vec3 centerPos,
    float radius,
    glm::vec3 color,
    bool fill)
{
    Mesh* circle = new Mesh(name);
    std::vector<VertexFormat> vertices = {VertexFormat(centerPos + glm::vec3(0, radius, 0), color) };
    std::vector<unsigned int> indices = { 0 };

    float angle = 0;
    float angleIncrease = 3.1415926 * 2 / 360;
    glm::vec3 crtPoint = centerPos + glm::vec3(0, radius, 0);

    for (int i = 1; i < 360; i++) {
        angle += angleIncrease;
        crtPoint += glm::vec3(cos(angle), sin(angle), 0);
        vertices.push_back(VertexFormat(crtPoint, color));
        indices.push_back(i);
    }

    if (!fill) {
        circle->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        circle->SetDrawMode(GL_TRIANGLE_FAN);
    }
    
    circle->InitFromData(vertices, indices);

    return circle;

}

Mesh* object2D::CreateQuad(
    const std::string& name,
    std::vector<VertexFormat> vertices, bool fill)
{
    Mesh* quad = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };
    if (!fill) {
        quad->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);

        quad->SetDrawMode(GL_TRIANGLES);
    }


    quad->InitFromData(vertices, indices);
    return quad;
}


//x	=	16sin^3t	
//y = 13cost - 5cos(2t) - 2cos(3t) - cos(4t).
Mesh* object2D::CreateHeart(
    const std::string& name,
    glm::vec3 centerPos,
    float radius,
    glm::vec3 color,
    bool fill)
{
    Mesh* circle = new Mesh(name);
    std::vector<VertexFormat> vertices = { 
        VertexFormat(centerPos, color),
        VertexFormat(centerPos + glm::vec3(20, 20, 0), color),
        VertexFormat(centerPos + glm::vec3(40, 20, 0), color),
        VertexFormat(centerPos + glm::vec3(60, 0, 0), color),
        VertexFormat(centerPos + glm::vec3(60, -20, 0), color),
        VertexFormat(centerPos + glm::vec3(0, -80, 0), color),
        VertexFormat(centerPos + glm::vec3(-60, -20, 0), color),
        VertexFormat(centerPos + glm::vec3(-60, 0, 0), color),
        VertexFormat(centerPos + glm::vec3(-40, 20, 0), color),
        VertexFormat(centerPos + glm::vec3(-20, 20, 0), color),
        VertexFormat(centerPos)
    
    };
    std::vector<unsigned int> indices = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    /*float angle = 0;
    float angleIncrease = 3.1415926 * 2 / 360;
    glm::vec3 crtPoint = centerPos;
    float x, y;

    for (int i = 1; i < 360; i++) {
        angle += angleIncrease;
        x = 16 * pow(sin(angle), 3);
        y = 13 * cos(angle) - 5 * cos(2 * angle) - 2 * cos(3 * angle) - cos(4 * angle);
        crtPoint += glm::vec3(x, y, 0);
        vertices.push_back(VertexFormat(crtPoint, color));
        indices.push_back(i);
    }*/

    if (!fill) {
        circle->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        circle->SetDrawMode(GL_TRIANGLE_FAN);
    }

    circle->InitFromData(vertices, indices);

    return circle;

}