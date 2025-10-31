#pragma once
#include <QMesh/face.hpp>
#include <QMesh/halfedge.hpp>
#include <QMesh/vertex.hpp>
#include <array>
#include <ranges>
#include <vector>

namespace qmesh {
class Mesh {
public:
  // The most basic way to construct a `Mesh` is by
  // providing a sequence of vertices and indices.
  Mesh(std::vector<std::array<float, 3>> vertices,
       std::vector<std::array<uint32_t, 3>> indices);

  size_t num_of_vertices() const;
  size_t num_of_faces() const;
  size_t num_of_half_edges() const;

  const std::vector<Vertex> &vertices() const;
  const std::vector<Face> &faces() const;
  const std::vector<HalfEdge> &half_edges() const;

  auto internal_edges() const {
    return half_edges_ | std::views::filter([this](auto &edge) {
             return edge.incident_face().has_value();
           });
  }

private:
  std::vector<Vertex> vertices_;
  std::vector<Face> faces_;
  std::vector<HalfEdge> half_edges_;
};
} // namespace qmesh
