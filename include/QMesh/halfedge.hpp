#pragma once

#include "QMesh/types.hpp"
namespace qmesh {

class HalfEdge {
public:
  VertexId origin;
  HalfEdgeId twin;
  FaceId incident_face;
  HalfEdgeId next;
  HalfEdgeId prev;

  HalfEdge(VertexId origin, FaceId incident_face);
  HalfEdge(VertexId origin);

  void set_incident_face(FaceId to);
  void set_next(FaceId to);
  void set_prev(FaceId to);
  void set_twin(FaceId to);
};
} // namespace qmesh
