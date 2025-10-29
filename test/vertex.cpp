#include <QMesh/vertex.hpp>
#include <catch2/catch_test_macros.hpp>
#include <cstdlib>

TEST_CASE("Vertex creation", "[vertex]") {
  std::array<float, 3> temp = {0.0, 0.1, 1.2};

  qmesh::Vertex v(temp);

  REQUIRE(abs(v.x() - 0.0) < 1e-5);
  REQUIRE(abs(v.y() - 0.1) < 1e-5);
  REQUIRE(abs(v.z() - 1.2) < 1e-5);

  REQUIRE_THROWS(v.incident_edge());

  v.set_as_origin(0);

  REQUIRE_NOTHROW(v.incident_edge());

  REQUIRE(v.incident_edge() == 0);
};
