#pragma once

#include "QMesh/types.hpp"
namespace qmesh {

class HalfEdge {
public:
  HalfEdge(VertexId origin, FaceId incident_face);
  HalfEdge(VertexId origin);

  void set_incident_face(FaceId to);
  void set_next(HalfEdgeId to);
  void set_prev(HalfEdgeId to);
  void set_twin(HalfEdgeId to);

private:
  VertexId origin;
  HalfEdgeId twin;
  FaceId incident_face;
  HalfEdgeId next;
  HalfEdgeId prev;
};
} // namespace qmesh
