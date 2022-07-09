cmake_minimum_required(VERSION 3.23)

project(citOLCCore LANGUAGES CXX)

add_library(citOLCCore src/citOLCCore.cpp)
target_include_directories(citOLCCore PUBLIC include)

set_target_properties(
  citOLCCore
  PROPERTIES CXX_STANDARD 17
             CXX_STANDARD_REQUIRED ON
             CXX_EXTENSIONS OFF)

# Can be ["latest", "v0.2.0", ...]
set(tolc_version latest)
include(FetchContent)
FetchContent_Declare(
  tolc_entry
  URL https://github.com/Tolc-Software/tolc/releases/download/${tolc_version}/tolc-${CMAKE_HOST_SYSTEM_NAME}.tar.xz
)
FetchContent_Populate(tolc_entry)
set(tolc_DIR ${tolc_entry_SOURCE_DIR}/lib/cmake/tolc)
find_package(tolc CONFIG REQUIRED)

# Creates a CMake target citOLCCore_objc
tolc_create_bindings(
  TARGET
  citOLCCore
  LANGUAGE
  objc
  OUTPUT
  ${CMAKE_CURRENT_BINARY_DIR}/objc-bindings)

# set_target_properties(citOLCCore_objc PROPERTIES
#   FRAMEWORK TRUE
#   MACOSX_FRAMEWORK_IDENTIFIER io.tolc.citOLC
#   PUBLIC_HEADER ${CMAKE_CURRENT_BINARY_DIR}/objc-bindings/citOLCCore.h
#   INSTALL_RPATH @loader_path/..)

# install(TARGETS citOLCCore_objc
#   FRAMEWORK DESTINATION .
# )
install(TARGETS citOLCCore
        ARCHIVE DESTINATION lib/cpp)
install(TARGETS citOLCCore_objc
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib/static)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/objc-bindings/citOLCCore.h DESTINATION include)
