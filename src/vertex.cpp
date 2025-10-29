
#include "QMesh/types.hpp"
#include <QMesh/vertex.hpp>
#include <array>

namespace qmesh {

Vertex::Vertex(std::array<float, 3> position) { position_ = position; };

float Vertex::x() const { return position_[0]; }
float Vertex::y() const { return position_[1]; }
float Vertex::z() const { return position_[2]; }

HalfEdgeId Vertex::incident_edge() {
  return incident_edge_.has_value()
             ? incident_edge_.value()
             // TODO: When can this happen?
             : throw std::runtime_error("Incident edge has no value");
};

void Vertex::set_as_origin(HalfEdgeId of) {
  if (!incident_edge_.has_value()) {
    incident_edge_ = of;
  }
};

} // namespace qmesh
