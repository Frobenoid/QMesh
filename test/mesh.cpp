#include "QMesh/mesh.hpp"
#include <array>
#include <catch2/catch_message.hpp>
#include <catch2/catch_test_macros.hpp>
#include <vector>

TEST_CASE("Triangle", "[initialization, mesh]") {
  std::vector<std::array<float, 3>> vertex = {
      {0.0, 0.0, 0.0},
      {0.0, 1.0, 0.0},
      {1.0, 1.0, 0.0},
  };

  std::vector<std::array<uint32_t, 3>> indices = {{0, 1, 2}};

  qmesh::Mesh mesh(vertex, indices);

  REQUIRE(mesh.num_of_faces() == 1);
  REQUIRE(mesh.num_of_vertices() == 3);
  REQUIRE(mesh.num_of_half_edges() == 6);
}

TEST_CASE("Glued triangles", "[initialization, mesh]") {
  std::vector<std::array<float, 3>> vertex = {
      {0.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {1.0, 1.0, 0.0}, {1.0, 1.0, 1.0}};

  std::vector<std::array<uint32_t, 3>> indices = {{0, 1, 2}, {1, 3, 2}};

  qmesh::Mesh mesh(vertex, indices);

  REQUIRE(mesh.num_of_faces() == 2);
  REQUIRE(mesh.num_of_vertices() == 4);
  REQUIRE(mesh.num_of_half_edges() == 10);

  // Verifying existence
  for (auto v : mesh.vertices()) {
    REQUIRE_NOTHROW(v.id());
    REQUIRE_NOTHROW(v.incident_edge());
  }

  for (auto f : mesh.faces()) {
    REQUIRE(f.has_incident_edge());
    REQUIRE_NOTHROW(f.id());
    REQUIRE_NOTHROW(f.incident_edge());
  }

  for (auto e : mesh.half_edges()) {
    REQUIRE_NOTHROW(e.twin());
    REQUIRE_NOTHROW(e.next());
    REQUIRE_NOTHROW(e.prev());
  }

  // Verifying topology
  for (auto e : mesh.internal_edges()) {
    REQUIRE(mesh.half_edges()[e.twin()].twin() == e.id());

    if (e.incident_face().has_value()) {
      // this.next.next.next = this
      REQUIRE(mesh.half_edges()[mesh.half_edges()[e.next()].next()].next() ==
              e.id());

      // this.twin.next.origin = this.origin
      REQUIRE(mesh.half_edges()[mesh.half_edges()[e.twin()].next()].origin() ==
              e.origin());

      // this.twin.origin = this.next.origin
      REQUIRE(mesh.half_edges()[e.twin()].origin() ==
              mesh.half_edges()[e.next()].origin());
    }
  }

  // TODO: Add outer face walk
}
