add_executable(qmesh qmesh.cpp)
target_link_libraries(qmesh PRIVATE qmesh::libqmesh)

include(GNUInstallDirs)
install(
  TARGETS qmesh
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
