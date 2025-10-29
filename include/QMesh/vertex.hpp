#pragma once

#include "QMesh/types.hpp"
#include <array>

namespace qmesh {

class Vertex {
public:
  Vertex(std::array<float, 3> position);
  ~Vertex() = default;

  float x() const;
  float y() const;
  float z() const;

  // Returns the ID of an incident edge of the node,
  // if there is no incident edge then this throws.
  //
  // There may be multiple half-edges originating
  // from this node, they can be retrieve with the
  // `incident_edges()` method.
  HalfEdgeId incident_edge();

  // Returns all half edges incident to this vertex.
  // TODO: What should the return type of this be?
  auto incident_edges();

  // Set the vertex as the origin of a given
  // half-edge. This only happens if the vertex
  // has not been assigned an incident edge. Otherwise
  // nothing happens.
  void set_as_origin(HalfEdgeId of);

  VertexId id() const;
  void set_id(VertexId to);

private:
  std::array<float, 3> position_;

  // Index of incident edge in parent mesh.
  //
  // May not exists at the time the vertex
  // is created.
  std::optional<HalfEdgeId> incident_edge_;

  // Id inside parent mesh.
  std::optional<VertexId> id_;
};
} // namespace qmesh
