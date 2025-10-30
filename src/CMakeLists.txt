add_library(libqmesh
libqmesh.cpp
vertex.cpp
face.cpp
halfedge.cpp
mesh.cpp
)
add_library(qmesh::libqmesh ALIAS libqmesh)

set_target_properties(
libqmesh
PROPERTIES OUTPUT_NAME qmesh
)

target_compile_features(libqmesh PUBLIC cxx_std_20)

target_include_directories(
  libqmesh
PUBLIC
  $<INSTALL_INTERFACE:include>
  $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
PRIVATE
  ${CMAKE_SOURCE_DIR}/src/include
)

include(GNUInstallDirs)
install(TARGETS libqmesh
  EXPORT qmesh-targets
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
  DIRECTORY ${PROJECT_SOURCE_DIR}/include/
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
  EXPORT qmesh-targets
  FILE qmesh-config.cmake
  NAMESPACE qmesh::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/qmesh
)
