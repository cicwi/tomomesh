#include <cassert>
#include <iostream>
#include <limits>

#include "load_triangles_from_obj.hpp"

Mesh::Mesh(std::string file) {
    scene_ = aiImportFile(file.c_str(), aiProcessPreset_TargetRealtime_Fast);

    process_();
}

Mesh::~Mesh() {
    if (scene_) {
        aiReleaseImport(scene_);
    }
}

std::vector<std::array<float, 9>> Mesh::triangles() { return triangles_; }
std::vector<float> Mesh::bounding_box() { return bounding_box_; }

void Mesh::process_() {
    // find largest mesh in scene, ignore the others
    size_t maxVertices = 0;
    int best = -1;
    for (size_t i = 0; i < scene_->mNumMeshes; ++i) {
        if (scene_->mMeshes[i]->mNumVertices > maxVertices) {
            best = i;
            maxVertices = scene_->mMeshes[i]->mNumVertices;
        }
    }
    if (best < 0) {
        std::cerr << "No viable mesh found!\n";
        return;
    }
    auto mesh = scene_->mMeshes[best];

    std::cout << "vertices: " << mesh->mNumVertices << "\n";
    std::cout << "faces: " << mesh->mNumFaces << "\n";

    struct BoundingBox {
        void insert(aiVector3D v) {
            auto update = [](std::array<float, 2>& b, float x) {
                if (x < b[0]) {
                    b[0] = x;
                }
                if (x > b[1]) {
                    b[1] = x;
                }
            };
            update(bounds[0], v.x);
            update(bounds[1], v.y);
            update(bounds[2], v.z);
        }

        std::vector<float> packed() {
            return {bounds[0][0], bounds[1][0], bounds[2][0],
                    bounds[0][1], bounds[1][1], bounds[2][1]};
        }

        std::array<std::array<float, 2>, 3> bounds = {
            {std::numeric_limits<float>::max(),
             std::numeric_limits<float>::min()}};
    };

    BoundingBox box;

    for (size_t i = 0; i < mesh->mNumFaces; ++i) {
        assert(mesh->mFaces[i].mNumIndices == 3);
        std::array<float, 9> tri;
        int j = 0;
        for (size_t k = 0; k < mesh->mFaces[i].mNumIndices; ++k) {
            auto vertex = mesh->mVertices[mesh->mFaces[i].mIndices[k]];
            tri[j++] = vertex.x;
            tri[j++] = vertex.y;
            tri[j++] = vertex.z;
            box.insert(vertex);
        }
        triangles_.push_back(tri);
    }

    bounding_box_ = box.packed();
}
