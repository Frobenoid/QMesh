
#include "QMesh/face.hpp"
#include "QMesh/types.hpp"
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

HalfEdgeId Face::incident_edge() const {
  return incident_edge_.has_value()
             ? incident_edge_.value()
             : throw std::runtime_error("Incident edge for face has no value");
}

FaceId Face::id() const {
  return id_.has_value()
             ? id_.value()
             : throw std::runtime_error("Current face has no parent mesh.");
};

void Face::set_id(FaceId to) {
  if (!id_.has_value()) {
    id_ = to;
  } else {
    throw std::runtime_error("[ERROR]: This face has already a parent.");
  }
};
} // namespace qmesh
