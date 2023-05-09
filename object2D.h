#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


namespace object2D
{

    // Create square with given bottom left corner, length and color
    Mesh* CreateSquare(const std::string &name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
    Mesh* CreateTriangle(const std::string& name, glm::vec3 leftBottomCorner, float side, glm::vec3 color, bool fill = false);
    Mesh* CreateTriangleFromVertexList(const std::string& name, std::vector<VertexFormat> vertices);
    Mesh* CreateCircle(const std::string& name, glm::vec3 centerPos, float radius, glm::vec3 color, bool fill = false);
    Mesh* CreateQuad(const std::string& name, std::vector<VertexFormat> vertices, bool fill = false);
    Mesh* CreateHeart(const std::string& name, glm::vec3 centerPos, float radius, glm::vec3 color, bool fill);
}
