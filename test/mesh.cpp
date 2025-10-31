#include "QMesh/mesh.hpp"
#include <array>
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
