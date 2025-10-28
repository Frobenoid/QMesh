#pragma once
#include <QMesh/types.hpp>

#include <array>

namespace qmesh {
class Face {
public:
  // TODO: This will only work for triangle meshes.

  // Indices of vertex forming this face, relative to their
  // parent mesh.
  std::array<VertexId, 3> indices;

  Face(std::array<uint32_t, 3> indices);
  Face(uint32_t i, uint32_t j, uint32_t k);
};
} // namespace qmesh
