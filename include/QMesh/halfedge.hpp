#pragma once

#include "QMesh/types.hpp"
#include <cstdint>
namespace qmesh {

class HalfEdge {
public:
  VertexId origin;
  HalfEdgeId twin;
  FaceId incident_face;
  HalfEdgeId next;
  HalfEdgeId prev;
};
} // namespace qmesh
