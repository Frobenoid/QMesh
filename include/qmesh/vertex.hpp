#pragma once

#include <array>

namespace qmesh {

class Vertex {
public:
  std::array<float, 3> position;
  // Index of incident edge in parent mesh.
  uint32_t incident_edge;

  Vertex(std::array<float, 3> position);
  ~Vertex() = default;

  float x() const;
  float y() const;
  float z() const;

  float x();
  float y();
  float z();
};
} // namespace qmesh
