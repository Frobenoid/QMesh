#include "QMesh/primitives.hpp"
#include "QMesh/mesh.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Cube", "[primitive]") {
  qmesh::Mesh cube = qmesh::primitive::make_cube();

  REQUIRE(cube.num_of_faces() == 12);
  REQUIRE(cube.num_of_vertices() == 8);
  REQUIRE(cube.num_of_half_edges() == 36);

  // There are no boundary edges.
  for (auto e : cube.half_edges()) {
    REQUIRE_NOTHROW(e.incident_face());
  }

  // Verifying topology
  for (auto e : cube.internal_edges()) {
    REQUIRE(cube.half_edges()[e.twin()].twin() == e.id());

    // this.next.next.next = this
    REQUIRE(cube.half_edges()[cube.half_edges()[e.next()].next()].next() ==
            e.id());
    //
    // this.twin.next.origin = this.origin
    REQUIRE(cube.half_edges()[cube.half_edges()[e.twin()].next()].origin() ==
            e.origin());

    // this.twin.origin = this.next.origin
    REQUIRE(cube.half_edges()[e.twin()].origin() ==
            cube.half_edges()[e.next()].origin());
  }
}

TEST_CASE("Simplex", "[primitive]") {
  qmesh::Mesh simplex = qmesh::primitive::make_simplex();

  REQUIRE(simplex.num_of_vertices() == 4);
  REQUIRE(simplex.num_of_faces() == 4);
  REQUIRE(simplex.num_of_half_edges() == 12);

  // There are no boundary edges.
  for (auto e : simplex.half_edges()) {
    REQUIRE_NOTHROW(e.incident_face());
  }

  // Verifying topology
  for (auto e : simplex.half_edges()) {

    auto next = simplex.half_edges()[e.next()];
    auto next_next = next.next();
    auto next_next_next = simplex.half_edges()[next_next].next();

    REQUIRE(simplex.half_edges()[e.twin()].twin() == e.id());

    // this.next.next.next = this
    REQUIRE(
        simplex.half_edges()[simplex.half_edges()[e.next()].next()].next() ==
        e.id());

    // this.twin.next.origin = this.origin
    REQUIRE(
        simplex.half_edges()[simplex.half_edges()[e.twin()].next()].origin() ==
        e.origin());

    // this.twin.origin = this.next.origin
    REQUIRE(simplex.half_edges()[e.twin()].origin() ==
            simplex.half_edges()[e.next()].origin());
  }
}
