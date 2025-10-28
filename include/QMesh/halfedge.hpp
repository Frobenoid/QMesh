#pragma once

#include <cstdint>
namespace qmesh {

class HalfEdge {
public:
  // Index of origin vertex.
  uint32_t origin;
  // Twin.
  uint32_t twin;
  uint32_t incident_face;
  uint32_t next;
  uint32_t prev;
};
} // namespace qmesh
