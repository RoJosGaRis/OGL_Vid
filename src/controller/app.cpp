#include "app.h"
#include "../stb_image.h"

App::App() {
  set_up_glfw();
}

App::~App() {
  glDeleteBuffers(VBOs.size(), VBOs.data());
  glDeleteVertexArrays(VAOs.size(), VAOs.data());
  glDeleteTextures(textures.size(), textures.data());
  glDeleteProgram(shader);

  delete motionSystem;
  delete cameraSystem;
  delete renderSystem;

  glfwTerminate();
}

unsigned int App::make_entity() {
  return entity_count++;
}

unsigned int App::make_cube_mesh(glm::vec3 size) {
  float l = size.x;
  float w = size.y;
  float h = size.z;

  std::vector<float> vertices = {
      l,  w, -h, 1.0f, 1.0f,
      l, -w, -h, 1.0f, 0.0f,
      -l, -w, -h, 0.0f, 0.0f,
      -l, -w, -h, 0.0f, 0.0f,
      -l,  w, -h, 0.0f, 1.0f,
      l,  w, -h, 1.0f, 1.0f,

      -l, -w,  h, 0.0f, 0.0f,
      l, -w,  h, 1.0f, 0.0f,
      l,  w,  h, 1.0f, 1.0f,
      l,  w,  h, 1.0f, 1.0f,
      -l,  w,  h, 0.0f, 1.0f,
      -l, -w,  h, 0.0f, 0.0f,

      -l,  w,  h, 1.0f, 1.0f,
      -l,  w, -h, 1.0f, 0.0f,
      -l, -w, -h, 0.0f, 0.0f,
      -l, -w, -h, 0.0f, 0.0f,
      -l, -w,  h, 0.0f, 1.0f,
      -l,  w,  h, 1.0f, 1.0f,

      l, -w, -h, 0.0f, 0.0f,
      l,  w, -h, 1.0f, 0.0f,
      l,  w,  h, 1.0f, 1.0f,
      l,  w,  h, 1.0f, 1.0f,
      l, -w,  h, 0.0f, 1.0f,
      l, -w, -h, 0.0f, 0.0f,

      -l, -w, -h, 0.0f, 0.0f,
      l, -w, -h, 1.0f, 0.0f,
      l, -w,  h, 1.0f, 1.0f,  
      l, -w,  h, 1.0f, 1.0f,
      -l, -w,  h, 0.0f, 1.0f,
      -l, -w, -h, 0.0f, 0.0f,

      l,  w,  h, 1.0f, 1.0f,
      l,  w, -h, 1.0f, 0.0f,
      -l,  w, -h, 0.0f, 0.0f, 
      -l,  w, -h, 0.0f, 0.0f,
      -l,  w,  h, 0.0f, 1.0f,
      l,  w,  h, 1.0f, 1.0f
  };

  unsigned int VAO;
  glGenVertexArrays(1, &VAO);
  VAOs.push_back(VAO);
  glBindVertexArray(VAO);

  unsigned int VBO;
  glGenBuffers(1, &VBO);
  VBOs.push_back(VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 20, (void*)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 20, (void*)12);
  glEnableVertexAttribArray(1);

  return VAO;
}

unsigned int App::make_texture(const char* filename) {
  
}