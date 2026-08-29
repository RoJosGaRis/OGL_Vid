#include "factory.h"
#include "../stb_image.h"

Factory::Factory (
  std::unordered_map<unsigned int, PhysicsComponent> &physicsComponents,
  std::unordered_map<unsigned int, RenderComponent> &renderComponents,
  std::unordered_map<unsigned int, TransformComponent> &transformComponents
): physicsComponents(physicsComponents), renderComponents(renderComponents), transformComponents(transformComponents){}
  
Factory::~Factory() {
  glDeleteBuffers(VBOs.size(), VBOs.data());
  glDeleteVertexArrays(VAOs.size(), VAOs.data());
  glDeleteTextures(textures.size(), textures.data());
}
  
  unsigned int Factory::make_camera(glm::vec3 position, glm::vec3 eulers){
    TransformComponent transform;
    transform.position = position;
    transform.eulers = eulers;

    transformComponents[entities_made] = transform;

    return entities_made++;
  }
  
  void Factory::make_cube(glm::vec3 position, glm::vec3 eulers, glm::vec3 eulerVelocity){

    TransformComponent transform;
    transform.position= position;
    transform.eulers = eulers;

    transformComponents[entities_made] = transform;

    PhysicsComponent physics;
    physics.velocity = {0.0f, 0.0f, 0.0f};
    physics.eulerVelocity = eulerVelocity;
    physicsComponents[entities_made] = physics;

    RenderComponent render;
    render.mesh = make_cube_mesh({0.25f, 0.25f, 0.25f});
    render.material = make_texture("../img/lol2-img.jpg");
    renderComponents[entities_made] = render;

    entities_made++;
  }

  unsigned int Factory::make_cube_mesh(glm::vec3 size) {
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

  unsigned int Factory::make_texture(const char* filename) {
    int width, height, channels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(filename, &width, &height, &channels, STBI_rgb_alpha);

    unsigned int texture;
    glGenTextures(1, &texture);
    textures.push_back(texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    stbi_image_free(data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return texture;
  }