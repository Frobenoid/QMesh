add_executable(tests
vertex.cpp
face.cpp
mesh.cpp
primitives.cpp
)
target_link_libraries(tests PRIVATE qmesh::libqmesh Catch2::Catch2WithMain)
include(Catch)
catch_discover_tests(tests)
