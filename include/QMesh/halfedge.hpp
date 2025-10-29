#pragma once

#include "QMesh/types.hpp"
#include <optional>
namespace qmesh {

class HalfEdge {
public:
  HalfEdge(VertexId origin, FaceId incident_face);
  HalfEdge(VertexId origin);

  void set_incident_face(FaceId to);
  void remove_incident_face();
  void set_next(HalfEdgeId to);
  void set_prev(HalfEdgeId to);
  void set_twin(HalfEdgeId to);

private:
  VertexId origin;

  // May not exist a the time of creation but every
  // half edge in an initialized mesh must have all
  // the following properties.

  std::optional<FaceId> incident_face;
  std::optional<HalfEdgeId> twin;
  std::optional<HalfEdgeId> next;
  std::optional<HalfEdgeId> prev;
};
} // namespace qmesh
