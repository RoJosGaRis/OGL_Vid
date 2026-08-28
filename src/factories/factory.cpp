#include "factory.h"
#include "../stb_image.h"

class Factory {
  public: 
    Factory::Factory (
      std::unordered_map<unsigned int, PhysicsComponent> &physicsComponents,
      std::unordered_map<unsigned int, RenderComponent> &renderComponents,
      std::unordered_map<unsigned int, TransformComponent> &transformComponents
    ): physicsComponents(physicsComponents), renderComponents(renderComponents), transformComponents(transformComponents){}
    
    ~Factory() {
      glDeleteBuffers(VBOs.size(), VBOs.data());
      glDeleteVertexArrays(VAOs.size(), VAOs.data());
      glDeleteTextures(textures.size(), textures.data());
    }
    
    unsigned int make_camera(glm::vec3 position, glm::vec3 eulers);
    
    void make_cube(glm::vec3 position, glm::vec3 eulers, glm::vec3 eulerVelocity);
    
    private:
    unsigned int entities_made = 0;
    
    std::unordered_map<unsigned int, PhysicsComponent> &physicsComponents;
    std::unordered_map<unsigned int, RenderComponent> &renderComponents;
    std::unordered_map<unsigned int, TransformComponent> &transformComponents;

    std::vector<unsigned int> VAOs;
    std::vector<unsigned int> VBOs;
    std::vector<unsigned int> textures;

    RenderComponent make_cube_mesh(glm::vec3 size);
    unsigned int make_texture(const char* filename);
  };