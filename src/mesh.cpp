#include "QMesh/halfedge.hpp"
#include <QMesh/mesh.hpp>
#include <QMesh/types.hpp>
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <map>
#include <ranges>
#include <utility>
#include <vector>

namespace qmesh {
// The most basic way to construct a `Mesh` is by
// providing a sequence of vertices and indices.
Mesh::Mesh(std::vector<std::array<float, 3>> vertices,
           std::vector<std::array<uint32_t, 3>> indices) {

  // Initialize vertices.
  std::ranges::for_each(vertices, [this](auto vertex) {
    auto id = vertices_.size();
    vertices_.emplace_back(vertex, id);
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
    std::vector<HalfEdgeId> inner_edges_of_face;

    // Each half edge created here contains an origin vertex, a face (or null)
    // its twin, and its id.
    std::ranges::for_each(
        face.circulate(), [this, &visited, &inner_edges_of_face,
                           face](std::pair<VertexId, VertexId> index) {
          std::cout << "At (" << index.first << "," << index.second << ")"
                    << "\n";
          if (visited.contains(index)) {
            std::cout << "\tFound previously outer edge(" << index.first << ","
                      << index.second << ")" << "\n";
            // The current edge was previously created as a boundary edge,
            // now we assign its face.
            HalfEdge &current = half_edges_[visited.at(index)];
            printf("\t\tSetting face to %d for Edge(%d)\n ", face.id(),
                   current.id());
            current.set_incident_face(face.id());
            // Not this is an inner edge of the current face.
            inner_edges_of_face.push_back(current.id());
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

            printf("\t\tInner(%d,%d) -> Edge(%d)\n", index.first, index.second,
                   inner.id());
            printf("\t\tOuter(%d,%d) -> Edge(%d)\n", index.second, index.first,
                   outer.id());

            // Add them to the list.
            half_edges_.push_back(inner);
            half_edges_.push_back(outer);
            inner_edges_of_face.push_back(inner.id());

            // Assigning incident edges to vertex.
            vertices_[index.first].set_as_origin(inner.id());
          }
        });

    // Now all the created half edges corresponding to this face have
    // a next/prev .
    // TODO: Improve this using another circulate view.
    std::cout << "For face " << face.id() << '\n';
    auto n = inner_edges_of_face.size();
    for (int i = 0; i < inner_edges_of_face.size(); i++) {
      HalfEdge &current = half_edges_[inner_edges_of_face[i]];
      std::cout << "\tAssignin pointers for " << current.id() << '\n';
      HalfEdgeId prev = inner_edges_of_face[(i + n - 1) % n];
      current.set_prev(prev);
      HalfEdgeId next = inner_edges_of_face[(i + 1) % n];
      current.set_next(next);
      printf("Result: Prev(%d)->Edge(%d)->Next(%d)\n", prev,
             inner_edges_of_face[i], next);
    }

    // Assign incident edge for this face.
    face.set_incident_edge(inner_edges_of_face[0]);
  });

  // WARN: Please be decent and simplify this.
  std::ranges::for_each(
      half_edges_ | std::views::filter(
                        [this](const auto edge) { return !edge.has_next(); }),
      [this](auto &edge) {
        HalfEdge twin = half_edges_[edge.twin()];
        HalfEdgeId prev_of_twin = half_edges_[twin.id()].prev();
        HalfEdgeId next_of_twin = half_edges_[twin.id()].next();
        HalfEdgeId twin_of_prev_of_twin = half_edges_[prev_of_twin].twin();
        HalfEdgeId twin_of_next_of_twin = half_edges_[next_of_twin].twin();

        edge.set_next(twin_of_prev_of_twin);
        edge.set_prev(twin_of_next_of_twin);
        printf("Edge(%d) -> Next(%d), Prev(%d)\n", edge.id(),
               twin_of_prev_of_twin, twin_of_next_of_twin);
      });
}

size_t Mesh::num_of_vertices() const { return vertices_.size(); }
size_t Mesh::num_of_faces() const { return faces_.size(); }
size_t Mesh::num_of_half_edges() const { return half_edges_.size(); }

const std::vector<Vertex> &Mesh::vertices() const { return vertices_; }
const std::vector<Face> &Mesh::faces() const { return faces_; }
const std::vector<HalfEdge> &Mesh::half_edges() const { return half_edges_; }

} // namespace qmesh
