#pragma once
#include <QMesh/face.hpp>
#include <QMesh/halfedge.hpp>
#include <QMesh/vertex.hpp>
#include <array>
#include <vector>

namespace qmesh {
class Mesh {
public:
  std::vector<Vertex> vertices;
  std::vector<Face> faces;
  std::vector<HalfEdge> half_edges;

  // The most basic way to construct a `Mesh` is by
  // providing a sequence of vertices and indices.
  Mesh(std::vector<std::array<float, 3>> vertices,
       std::vector<std::array<uint16_t, 3>> indices);
};
} // namespace qmesh
