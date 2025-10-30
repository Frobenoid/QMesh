
#include <QMesh/mesh.hpp>
#include <QMesh/types.hpp>
#include <algorithm>
#include <map>
#include <utility>

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

  // TODO: Order is not required for this, use an unordered map with a custom
  // hash function. (It has a better performance)
  std::map<std::pair<VertexId, VertexId>, HalfEdgeId> visited;

  // Initialize halfedges.
  std::ranges::for_each(faces_, [this, &visited](auto face) {
    std::vector<std::pair<VertexId, VertexId>> circulate = {
        std::pair(face.indices_[0], face.indices_[1]),
        std::pair(face.indices_[1], face.indices_[2]),
        std::pair(face.indices_[2], face.indices_[0]),
    };

    std::ranges::for_each(circulate, [this, &visited, circulate, face](
                                         std::pair<VertexId, VertexId> index) {
      if (visited.contains(std::pair(index.second, index.first))) {
        // The current edge has no face so we will assign it.
        HalfEdge current = half_edges_[visited.at(index)];
        current.set_incident_face(face.id());
      } else {
        // Create inner edge with `i` as origin and  with the current face.
        HalfEdge inner(index.first, face.id());
        // Create outer edge without face.
        HalfEdge outer(index.second);

        // Assign their ID's
        inner.set_id(half_edges_.size());
        outer.set_id(half_edges_.size() + 1);

        // Link them as twins
        inner.set_twin(outer.id());
        outer.set_twin(inner.id());
        //
        // Mark them as visited.
        visited[std::pair(index.first, index.second)] = inner.id();
        visited[std::pair(index.second, index.first)] = outer.id();

        // Add them to the list.
        half_edges_.push_back(inner);
        half_edges_.push_back(outer);
      }
    });
  });
}
} // namespace qmesh
