
#include "QMesh/halfedge.hpp"
#include <QMesh/mesh.hpp>
#include <QMesh/types.hpp>
#include <algorithm>
#include <iostream>
#include <map>
#include <utility>
#include <vector>

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
  std::ranges::for_each(indices, [this](auto &face) {
    faces_.emplace_back(face, faces_.size());
  });

  // TODO: Order is not required for this, use an unordered map with a custom
  // hash function. (It has a better performance)
  std::map<std::pair<VertexId, VertexId>, HalfEdgeId> visited;

  // Initialize halfedges.
  std::ranges::for_each(faces_, [this, &visited](auto &face) {
    // TODO: Improve this. This wont work for non triangle meshes.
    std::vector<std::pair<VertexId, VertexId>> circulate = {
        std::pair(face.indices_[0], face.indices_[1]),
        std::pair(face.indices_[1], face.indices_[2]),
        std::pair(face.indices_[2], face.indices_[0]),
    };

    std::vector<HalfEdgeId> edges_of_face;

    // Each half edge created here contains an origin vertex, a face (or null)
    // its twin, and its id.
    std::ranges::for_each(
        circulate, [this, &visited, circulate, &edges_of_face,
                    face](std::pair<VertexId, VertexId> index) {
          if (visited.contains(std::pair(index.second, index.first))) {
            // The current edge was previously created as a boundary edge,
            // now we assign its face.
            HalfEdge &current = half_edges_[visited.at(index)];
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

            // Mark them as visited.
            visited[std::pair(index.first, index.second)] = inner.id();
            visited[std::pair(index.second, index.first)] = outer.id();

            // Add them to the list.
            half_edges_.push_back(inner);
            half_edges_.push_back(outer);
            edges_of_face.push_back(inner.id());
            edges_of_face.push_back(outer.id());
          }
        });

    // Now all the created half edges correspoinging to this face have
    // a next/prev .
    // TODO: Improve this using another circulate view.
    for (int i = 0; i < edges_of_face.size(); i++) {
      HalfEdge &current = half_edges_[edges_of_face[i]];
      std::cout << "\tAssignin pointers for " << current.id() << '\n';
      HalfEdgeId prev = edges_of_face[(i - 1) % edges_of_face.size()];
      current.set_prev(prev);
      HalfEdgeId next = edges_of_face[(i + 1) % edges_of_face.size()];
      current.set_next(next);
    }

    // Assign incident edges to each vertex.
    for (auto e : half_edges_) {
      if (!vertices_[e.origin()].has_incident_edge())
        vertices_[e.origin()].set_as_origin(e.id());
    }

    // Assign incident edge for this face.
    face.set_incident_edge(edges_of_face[0]);
  });
}

size_t Mesh::num_of_vertices() const { return vertices_.size(); }
size_t Mesh::num_of_faces() const { return faces_.size(); }
size_t Mesh::num_of_half_edges() const { return half_edges_.size(); }

std::vector<Vertex> &Mesh::vertices() { return vertices_; }
std::vector<Face> &Mesh::faces() { return faces_; }
std::vector<HalfEdge> &Mesh::half_edges() { return half_edges_; }

} // namespace qmesh
