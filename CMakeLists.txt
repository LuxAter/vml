cmake_minimum_required(VERSION 3.11)
project(
  vml
  VERSION 0.1.0
  DESCRIPTION
    "A header only C++ library that provides fast linear algebra systems"
  HOMEPAGE_URL "https://github.com/LuxAter/vml")
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
  set(VML_MAIN_PROJECT TRUE)
  set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
else()
  set(VML_MAIN_PROJECT FALSE)
endif()

option(VML_TESTS "Build tests" ${VML_MAIN_PROJECT})
option(VML_INSTALL "Create install target" ${VML_MAIN_PROJECT})

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

add_library(${PROJECT_NAME} INTERFACE)
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_include_directories(
  ${PROJECT_NAME}
  INTERFACE $<BUILD_INTERFACE:${${PROJECT_NAME}_SOURCE_DIR}/include>
            $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)
target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_11 cxx_constexpr)

if(VML_TESTS)
  enable_testing()
  set(SOURCES tests/core.cpp)
  add_executable(unit-tests ${SOURCES})
  target_link_libraries(unit-tests ${PROJECT_NAME})
endif()

if(VML_INSTALL)
  write_basic_package_version_file(
    "${PROJECT_NAME}ConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion)
  configure_package_config_file(
    "${PROJECT_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake.in"
    "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake" INSTALL_DESTINATION
    ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake)

  install(
    TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}_Targets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

  install(
    EXPORT ${PROJECT_NAME}_Targets
    FILE ${PROJECT_NAME}Targets.cmake
    NAMESPACE ${PROJECT_NAME}::
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake)
  install(FILES "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
                "${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
          DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake)
  install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}
          DESTINATION include)
endif()
