#pragma once

#include "QMesh/types.hpp"
#include <optional>
namespace qmesh {

class HalfEdge {
public:
  HalfEdge(VertexId origin, FaceId incident_face);
  HalfEdge(VertexId origin);

  void set_incident_face(FaceId to);
  void remove_incident_face();
  void set_next(HalfEdgeId to);
  void set_prev(HalfEdgeId to);
  void set_twin(HalfEdgeId to);
  void set_id(HalfEdgeId to);

  VertexId origin() const;
  std::optional<FaceId> incident_face() const;
  HalfEdgeId twin() const;
  HalfEdgeId next() const;
  HalfEdgeId prev() const;
  HalfEdgeId id() const;
  bool has_incident_face();

private:
  HalfEdgeId id_;
  VertexId origin_;
  // A boundary half edge can have an empty face.
  std::optional<FaceId> incident_face_;

  // May not exist a the time of creation but every
  // half edge in an initialized mesh must have all
  // the following properties.

  std::optional<HalfEdgeId> twin_;
  std::optional<HalfEdgeId> next_;
  std::optional<HalfEdgeId> prev_;
};
} // namespace qmesh
