#include <QMesh/vertex.hpp>
#include <array>
#include <stdexcept>

namespace qmesh {

Vertex::Vertex(std::array<float, 3> position) : position_(position) {}
Vertex::Vertex(std::array<float, 3> position, size_t id)
    : position_(position), id_(id) {}

float Vertex::x() const { return position_[0]; }
float Vertex::y() const { return position_[1]; }
float Vertex::z() const { return position_[2]; }

HalfEdgeId Vertex::incident_edge() {
  return incident_edge_.has_value()
             ? incident_edge_.value()
             // TODO: When can this happen?
             : throw std::runtime_error("Vertex has no incident edge.");
}

void Vertex::set_as_origin(HalfEdgeId of) {
  if (!incident_edge_.has_value()) {
    incident_edge_ = of;
  }
}

VertexId Vertex::id() const {
  return id_.has_value()
             ? id_.value()
             : throw std::runtime_error("Current vertex has no parent mesh.");
}

void Vertex::set_id(VertexId to) {
  if (!id_.has_value()) {
    id_ = to;
  } else {
    throw std::runtime_error("This vertex already has a parent.");
  }
}

bool Vertex::has_incident_edge() { return incident_edge_.has_value(); }

} // namespace qmesh
