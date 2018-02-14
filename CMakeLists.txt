cmake_minimum_required (VERSION 3.5)
project (mybf)
set (CMAKE_CXX_STANDARD 11)

find_package(LLVM REQUIRED CONFIG)

include_directories(/usr/local/opt/llvm/include)
include_directories(${PROJECT_SOURCE_DIR}/lib)
add_subdirectory(lib)

llvm_map_components_to_libnames(llvm_libs core)
add_executable(mybf mybf.cc)
target_link_libraries(mybf bflib ${llvm_libs})
