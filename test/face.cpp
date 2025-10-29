#include "QMesh/face.hpp"
#include <array>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Face initialization", "[face]") {
  std::array<uint32_t, 3> temp = {0, 1, 2};

  qmesh::Face f(temp);

  REQUIRE_THROWS(f.incident_edge());

  f.set_incident_edge(0);

  REQUIRE(f.incident_edge() == 0);
}
