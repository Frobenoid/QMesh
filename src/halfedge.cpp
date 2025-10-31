#include "QMesh/types.hpp"
#include <QMesh/halfedge.hpp>
#include <iostream>
#include <stdexcept>
namespace qmesh {
HalfEdge::HalfEdge(VertexId origin, FaceId incident_face)
    : origin_(origin), incident_face_(incident_face) {}
HalfEdge::HalfEdge(VertexId origin) : origin_(origin) {}

void HalfEdge::set_incident_face(FaceId to) { incident_face_ = to; }
void HalfEdge::set_next(HalfEdgeId to) { next_ = to; }
void HalfEdge::set_prev(HalfEdgeId to) { prev_ = to; }
void HalfEdge::set_twin(HalfEdgeId to) { twin_ = to; }
void HalfEdge::set_id(HalfEdgeId to) { id_ = to; }

VertexId HalfEdge::origin() const { return origin_; }
HalfEdgeId HalfEdge::id() const { return id_; }

std::optional<FaceId> HalfEdge::incident_face() const { return incident_face_; }

HalfEdgeId HalfEdge::twin() const {
  return twin_.has_value()
             ? twin_.value()
             : throw std::runtime_error("The current half edge has no twin");
}

HalfEdgeId HalfEdge::next() const {
  std::cout << "Getting next for " << id_ << '\n';
  return next_.has_value()
             ? next_.value()
             : throw std::runtime_error("The current half edge has no next");
}

HalfEdgeId HalfEdge::prev() const {
  return prev_.has_value()
             ? prev_.value()
             : throw std::runtime_error("The current half edge has no prev");
}

// TODO: Implementing this would require to move pointers around.
void HalfEdge::remove_incident_face() { incident_face_ = std::nullopt; }
} // namespace qmesh
