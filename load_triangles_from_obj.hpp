#include <array>
#include <string>
#include <vector>

#include <assimp/cimport.h>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

class Mesh {
  public:
    Mesh(std::string file);
    ~Mesh();

    std::vector<std::array<float, 9>> triangles();
    std::vector<float> bounding_box();

  private:
    void process_();

    const aiScene* scene_;
    std::vector<std::array<float, 9>> triangles_;
    std::vector<float> bounding_box_;
};
