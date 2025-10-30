
#include <QMesh/mesh.hpp>
#include <QMesh/types.hpp>
#include <algorithm>
#include <array>
#include <unordered_map>

namespace qmesh {
// The most basic way to construct a `Mesh` is by
// providing a sequence of vertices and indices.
Mesh::Mesh(std::vector<std::array<float, 3>> vertices,
           std::vector<std::array<uint32_t, 3>> indices) {

  // Initialize vertices.
  std::ranges::for_each(vertices, [this](auto vertex) {
    vertices_.emplace_back(vertex, vertices_.size());
  });

  // Intialize faces.
  std::ranges::for_each(
      indices, [this](auto face) { faces_.emplace_back(face, faces_.size()); });

  // std::unordered_map<std::pair<VertexId, VertexId>, HalfEdgeId> visited;
  std::unordered_map<std::array<VertexId, 2>, HalfEdgeId> visited;

  // Initialize halfedges.
  std::ranges::for_each(faces_, [this, &visited](auto face) {
    std::vector<std::array<VertexId, 2>> circulate = {
        {face.indices_[0], face.indices_[1]},
        {face.indices_[1], face.indices_[2]},
        {face.indices_[2], face.indices_[0]},
    };

    std::ranges::for_each(circulate, [this, &visited, circulate,
                                      face](std::array<VertexId, 2> index) {
      if (visited.contains({index[1], index[0]})) {
        // The current edge has no face so we will assign it.
        HalfEdge current = half_edges_[visited.at(index)];
        current.set_incident_face(face.id());
      } else {
        // Create inner edge with `i` as origin and  with the current face.
        HalfEdge inner(index[0], face.id());
        // Create outer edge without face.
        HalfEdge outer(index[1]);

        // Assign their ID's
        inner.set_id(half_edges_.size());
        outer.set_id(half_edges_.size() + 1);

        // Link them as twins
        inner.set_twin(outer.id());
        outer.set_twin(inner.id());
        //
        // Mark them as visited.
        visited[{index[0], index[1]}] = inner.id();
        visited[{index[1], index[0]}] = outer.id();

        // Add them to the list.
        half_edges_.push_back(inner);
        half_edges_.push_back(outer);
      }
    });
  });
}
} // namespace qmesh
