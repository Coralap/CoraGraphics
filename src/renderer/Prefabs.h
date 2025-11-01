#pragma once
#include <vector>
#include <string>
#include "./Mesh.h"

namespace Prefabs {

    // Creates a cube mesh with optional texture
    inline Mesh* Cube(const std::string& texturePath = "") {
        std::vector<float> vertices = {
            // positions         // normals          // texcoords
            // back face
            -0.5f,-0.5f,-0.5f,   0.0f,0.0f,-1.0f,   0.0f,0.0f,
             0.5f,-0.5f,-0.5f,   0.0f,0.0f,-1.0f,   1.0f,0.0f,
             0.5f, 0.5f,-0.5f,   0.0f,0.0f,-1.0f,   1.0f,1.0f,
            -0.5f, 0.5f,-0.5f,   0.0f,0.0f,-1.0f,   0.0f,1.0f,

            // front face
            -0.5f,-0.5f, 0.5f,   0.0f,0.0f,1.0f,    0.0f,0.0f,
             0.5f,-0.5f, 0.5f,   0.0f,0.0f,1.0f,    1.0f,0.0f,
             0.5f, 0.5f, 0.5f,   0.0f,0.0f,1.0f,    1.0f,1.0f,
            -0.5f, 0.5f, 0.5f,   0.0f,0.0f,1.0f,    0.0f,1.0f,

            // left face
            -0.5f, 0.5f, 0.5f,  -1.0f,0.0f,0.0f,    1.0f,0.0f,
            -0.5f, 0.5f,-0.5f,  -1.0f,0.0f,0.0f,    1.0f,1.0f,
            -0.5f,-0.5f,-0.5f,  -1.0f,0.0f,0.0f,    0.0f,1.0f,
            -0.5f,-0.5f, 0.5f,  -1.0f,0.0f,0.0f,    0.0f,0.0f,

            // right face
             0.5f, 0.5f, 0.5f,   1.0f,0.0f,0.0f,    1.0f,0.0f,
             0.5f, 0.5f,-0.5f,   1.0f,0.0f,0.0f,    1.0f,1.0f,
             0.5f,-0.5f,-0.5f,   1.0f,0.0f,0.0f,    0.0f,1.0f,
             0.5f,-0.5f, 0.5f,   1.0f,0.0f,0.0f,    0.0f,0.0f,

            // bottom face
            -0.5f,-0.5f,-0.5f,   0.0f,-1.0f,0.0f,   0.0f,1.0f,
             0.5f,-0.5f,-0.5f,   0.0f,-1.0f,0.0f,   1.0f,1.0f,
             0.5f,-0.5f, 0.5f,   0.0f,-1.0f,0.0f,   1.0f,0.0f,
            -0.5f,-0.5f, 0.5f,   0.0f,-1.0f,0.0f,   0.0f,0.0f,

            // top face
            -0.5f, 0.5f,-0.5f,   0.0f,1.0f,0.0f,    0.0f,1.0f,
             0.5f, 0.5f,-0.5f,   0.0f,1.0f,0.0f,    1.0f,1.0f,
             0.5f, 0.5f, 0.5f,   0.0f,1.0f,0.0f,    1.0f,0.0f,
            -0.5f, 0.5f, 0.5f,   0.0f,1.0f,0.0f,    0.0f,0.0f
        };

        std::vector<unsigned int> indices = {
            0,1,2, 2,3,0,        // back
            4,5,6, 6,7,4,        // front
            8,9,10,10,11,8,      // left
            12,13,14,14,15,12,   // right
            16,17,18,18,19,16,   // bottom
            20,21,22,22,23,20    // top
        };

        return new Mesh(vertices, indices, texturePath);
    }

    // Creates a pyramid mesh with optional texture
    inline Mesh* Pyramid(const std::string& texturePath = "") {
        std::vector<float> vertices = {
            // positions          // normals         // texcoords
            -0.5f, 0.0f, -0.5f,   0.0f,-1.0f,0.0f,  0.0f,0.0f,
             0.5f, 0.0f, -0.5f,   0.0f,-1.0f,0.0f,  1.0f,0.0f,
             0.5f, 0.0f,  0.5f,   0.0f,-1.0f,0.0f,  1.0f,1.0f,
            -0.5f, 0.0f,  0.5f,   0.0f,-1.0f,0.0f,  0.0f,1.0f,
             0.0f, 0.8f,  0.0f,   0.0f,1.0f,0.0f,   0.5f,0.5f
        };

        std::vector<unsigned int> indices = {
            0,1,2, 2,3,0, // base
            0,1,4,
            1,2,4,
            2,3,4,
            3,0,4
        };
        if(texturePath ==""){
           return new Mesh(vertices, indices);
        }
        return new Mesh(vertices, indices, texturePath);
    }

} // namespace Prefab
