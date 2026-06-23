#include "triangle_mesh.h"
#include <vector>
#include <glad/glad.h>

TriangleMesh::TriangleMesh() {
    std::vector<float> position = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        -1.0f,  1.0f, 0.0f,
        1.0f,  1.0f, 0.0f
      };
    std::vector<int> colorIndices = {
      0, 1, 2, 3
    };
    std::vector<int> elementIndices = {
      0, 1, 2, 2, 1, 3
    };
    vertex_count = 6;

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    VBOs.resize(2);

    glGenBuffers(2, VBOs.data());
    glGenBuffers(1, &EBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    size_t positionSize = position.size() * sizeof(float);
    glBufferData(GL_ARRAY_BUFFER, positionSize, position.data(), 
            GL_STATIC_DRAW);
            
    //position
    glVertexAttribPointer(0, 3, GL_FLOAT, 
      GL_FALSE, 3 * sizeof(float), (void*)0);
      glEnableVertexAttribArray(0);
      
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    size_t colorIndicesSize = colorIndices.size() * sizeof(int);
    glBufferData(GL_ARRAY_BUFFER, colorIndicesSize, colorIndices.data(), 
            GL_STATIC_DRAW);
    //color
    glVertexAttribIPointer(1, 1, GL_INT, 
          sizeof(int), (void*)0);
    glEnableVertexAttribArray(1);

    //element
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    size_t elementsSize = elementIndices.size() * sizeof(int);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, elementsSize, elementIndices.data(), 
            GL_STATIC_DRAW);;
}

void TriangleMesh::draw() {
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, vertex_count, GL_UNSIGNED_INT, 0);
}

TriangleMesh::~TriangleMesh() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(2, VBOs.data());
    glDeleteBuffers(1, &EBO);
}