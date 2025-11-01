#include "QMesh/mesh.hpp"
#include <QMesh/primitives.hpp>
#include <array>
#include <vector>

namespace qmesh {

Mesh primitive::make_cube() {
  using V3 = std::array<float, 3>;
  using T3 = std::array<uint32_t, 3>;

  std::vector<V3> v = {
      V3{-0.5f, -0.5f, -0.5f}, // 0
      V3{0.5f, -0.5f, -0.5f},  // 1
      V3{0.5f, 0.5f, -0.5f},   // 2
      V3{-0.5f, 0.5f, -0.5f},  // 3
      V3{-0.5f, -0.5f, 0.5f},  // 4
      V3{0.5f, -0.5f, 0.5f},   // 5
      V3{0.5f, 0.5f, 0.5f},    // 6
      V3{-0.5f, 0.5f, 0.5f},   // 7
  };

  // std::vector<T3> i = {
  //     // Front
  //     T3{6, 5, 4},
  //     T3{7, 6, 4},
  //     // Back
  //     T3{1, 2, 0},
  //     T3{2, 3, 0},
  //     // Left
  //     T3{7, 3, 0},
  //     T3{4, 7, 0},
  //     // Right
  //     T3{5, 6, 1},
  //     T3{6, 2, 1},
  //     // Bottom
  //     T3{1, 5, 0},
  //     T3{5, 4, 0},
  //     // Top
  //     T3{2, 6, 3},
  //     T3{6, 7, 3},
  // };
  //
  std::vector<T3> i = {
      T3{0, 1, 2},
      T3{0, 2, 3},
      // Back
      T3{0, 4, 1},
      T3{1, 4, 5},
      // Left
      T3{0, 3, 4},
      T3{3, 7, 4},
      // Right
      T3{3, 2, 6},
      T3{3, 6, 7},
      // Bottom
      T3{7, 6, 5},
      T3{4, 7, 5},
      // Top
      T3{5, 6, 1},
      T3{1, 6, 2},
  };
  return Mesh(std::move(v), std::move(i));
}

Mesh primitive::make_simplex() {
  using V3 = std::array<float, 3>;
  using T3 = std::array<uint32_t, 3>;

  std::vector<V3> v = {
      {0.0, 0.0, 0.0},
      {1.0, 0.0, 0.0},
      {0.0, 1.0, 0.0},
      {0.0, 0.0, 1.0},
  };

  std::vector<T3> i = {{0, 3, 1}, {0, 1, 2}, {0, 2, 3}, {1, 3, 2}};

  return Mesh(std::move(v), std::move(i));
}

} // namespace qmesh
