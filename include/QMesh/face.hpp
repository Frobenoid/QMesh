#pragma once
#include <QMesh/types.hpp>

#include <array>
#include <optional>

namespace qmesh {
// TODO: This will only work for triangle meshes.
class Face {
public:
  Face(std::array<uint32_t, 3> indices);
  Face(uint32_t i, uint32_t j, uint32_t k);

  // Set the given half edge as the incident edge
  // of this face. This only happens if the face
  // has not been assigned an incident edge. Otherwise
  // nothing happens.
  //
  // To get all the half edges incident to this face
  // you can use the `incident_edges` method.
  void set_incident_edge(HalfEdgeId of);

  // Returns all half edges incident to this face.
  // TODO: What should the return type of this be?
  auto incident_edges();

  // Retrieves a half edge incident to
  // this face. If there is no half edge
  // incident to this face and this function
  // is called then an error is thrown.
  HalfEdgeId incident_edge() const;

  FaceId id() const;
  void set_id(FaceId to);

private:
  // Indices of vertex forming this face, relative to their
  // parent mesh.
  // FIX: This is not required. Indices can be created
  // only for deserealization in order to be consumed by
  // the renderer.
  std::array<VertexId, 3> indices_;

  // Index of incident edge in parent mesh.
  //
  // May not exists at the time the face
  // is created (during mesh initialization) but any face
  // within an initialized mesh must have an incident edge.
  std::optional<HalfEdgeId> incident_edge_;

  // Id inside parent mesh.
  std::optional<FaceId> id_;
};
} // namespace qmesh
