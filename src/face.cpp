
#include "QMesh/face.hpp"
#include <stdexcept>

namespace qmesh {

Face::Face(std::array<uint32_t, 3> indices) { indices_ = indices; };

Face::Face(uint32_t i, uint32_t j, uint32_t k) {
  indices_[0] = i;
  indices_[1] = j;
  indices_[2] = k;
};

void Face::set_incident_edge(HalfEdgeId edge) {
  if (!incident_edge_.has_value()) {
    incident_edge_ = edge;
  }
};

HalfEdgeId Face::incident_edge() {
  return incident_edge_.has_value()
             ? incident_edge_.value()
             : throw std::runtime_error("Incident edge for face has no value");
}

} // namespace qmesh
