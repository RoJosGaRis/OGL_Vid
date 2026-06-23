#include "config.h"
#include "triangle_mesh.h"
#include "material.h"


unsigned int make_module(const std::string& filepath, unsigned int module_type);
unsigned int make_shader(const std::string& vertex_filepath, const std::string& fragment_filepath);

int main() {
  
  GLFWwindow* window;

  if (!glfwInit()) {
    std::cout << "GLFW couldn't start" << std::endl;
    return -1;
  }

  window = glfwCreateWindow(640, 480, "My Window", NULL, NULL);
  glfwMakeContextCurrent(window);

  if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    glfwTerminate();
    return -1;
  }

  glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

  int w, h;
  glfwGetFramebufferSize(window, &w, &h);
  glViewport(0,0, w, h);

  TriangleMesh* triangle = new TriangleMesh;
  Material* material = new Material("img/lol2-img.jpg");
  Material* mask = new Material("img/vignette-img.jpg");

  unsigned int shader = make_shader(
    "src/shaders/vertex.txt",
    "src/shaders/fragment.txt"
  );

  glUseProgram(shader);
  glUniform1i(glGetUniformLocation(shader, "material"), 0);
  glUniform1i(glGetUniformLocation(shader, "mask"), 1);

  glm::vec3 quad_position = {0.1f, -0.2f, 0.0f};
  glm::vec3 camera_position = {-5.0f, 0.0f, 3.0f};
  glm::vec3 camera_target = {0.0f, 0.0f, 0.0f};
  glm::vec3 up = {0.0f, 0.0f, 1.0f};

  unsigned int model_location = glGetUniformLocation(shader, "model");
  unsigned int view_location = glGetUniformLocation(shader, "view");
  unsigned int proj_location = glGetUniformLocation(shader, "projection");

  glm::mat4 view = glm::lookAt(camera_position, camera_target, up);
  glUniformMatrix4fv(view_location, 1, GL_FALSE, glm::value_ptr(view));

  glm::mat4 projection = glm::perspective(45.0f, 640.0f/480.0f, 0.1f, 10.0f);
  glUniformMatrix4fv(proj_location, 1, GL_FALSE, glm::value_ptr(projection));

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  while(!glfwWindowShouldClose(window) )
  {
    glfwPollEvents();

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, quad_position);
    model = glm::rotate(model, (float) glfwGetTime(), {0.0f, 0.0f, 1.0f});
    glUniformMatrix4fv(model_location, 1, GL_FALSE, glm::value_ptr(model));

    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(shader);
    material->use(0);
    mask->use(1);
    triangle->draw();
    glfwSwapBuffers(window);
  }

  glDeleteProgram(shader);
  delete triangle;
  delete material;
  delete mask;

  glfwTerminate();

  return 0;
}



