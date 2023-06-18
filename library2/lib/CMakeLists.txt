set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_LIBDIR}")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/version.h.in
               ${CMAKE_CURRENT_BINARY_DIR}/include/${PROJECT_NAME}/version.h)

add_library(${PROJECT_NAME})
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

include(GenerateExportHeader)

generate_export_header(
  ${PROJECT_NAME} BASE_NAME ${PROJECT_NAME} EXPORT_FILE_NAME
  ${CMAKE_CURRENT_BINARY_DIR}/include/${PROJECT_NAME}/subfolder/helper.h)

set(${PROJECT_NAME}_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/lib.cpp)
set(${PROJECT_NAME}_HEADER
    ${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/lib.h)
set(${PROJECT_NAME}_HEADER_AUTO
    ${CMAKE_CURRENT_BINARY_DIR}/include/${PROJECT_NAME}/subfolder/helper.h
    ${CMAKE_CURRENT_BINARY_DIR}/include/${PROJECT_NAME}/version.h)

# Test compilation / build with FetchContent_Declare or find_package
if(BUILD_FETCH_CONTENT)
  include(FetchContent)
  # There is a target test1 in library and library2. Hack to disable
  # BUILD_TESTING only in library.
  set(BUILD_TESTING_SAVE ${BUILD_TESTING})
  set(BUILD_TESTING OFF)
  FetchContent_Declare(library SOURCE_DIR
                               "${CMAKE_CURRENT_SOURCE_DIR}/../../library")
  # Don't use FetchContent_MakeAvailable since it doesn't support
  # EXCLUDE_FROM_ALL. If you don't EXCLUDE_FROM_ALL, you will install library
  # with library2.
  FetchContent_GetProperties(library)
  if(NOT library_POPULATED)
    FetchContent_Populate(library)
    add_subdirectory(${library_SOURCE_DIR} ${library_BINARY_DIR}
                     EXCLUDE_FROM_ALL)
  endif()
  set(BUILD_TESTING ${BUILD_TESTING_SAVE})
else()
  find_package(library REQUIRED)
endif()
# With FetchContent, library::library is an alias to library.

# With find_package, it's a real namespace::library.
target_link_libraries(${PROJECT_NAME} PUBLIC library::library)

target_sources(
  ${PROJECT_NAME}
  PRIVATE ${${PROJECT_NAME}_SRC}
  PUBLIC FILE_SET HEADERS BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include/ FILES
         ${${PROJECT_NAME}_HEADER}
  PUBLIC FILE_SET HEADERS BASE_DIRS ${CMAKE_CURRENT_BINARY_DIR}/include/ FILES
         ${${PROJECT_NAME}_HEADER_AUTO})

target_include_directories(
  ${PROJECT_NAME}
  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
         $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
         $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

install(
  TARGETS ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}Targets
  FILE_SET HEADERS
  RUNTIME
  LIBRARY
  ARCHIVE)

install(
  EXPORT ${PROJECT_NAME}Targets
  FILE ${PROJECT_NAME}Targets.cmake
  NAMESPACE ${PROJECT_NAME}::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME})

configure_package_config_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/../cmake/${PROJECT_NAME}Config.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
  PATH_VARS CMAKE_INSTALL_PREFIX CMAKE_INSTALL_BINDIR CMAKE_INSTALL_INCLUDEDIR
            CMAKE_INSTALL_LIBDIR CMAKE_INSTALL_DATAROOTDIR)
write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
  VERSION
    ${Tutorial_VERSION_MAJOR}.${Tutorial_VERSION_MINOR}.${Tutorial_VERSION_PATCH}
  COMPATIBILITY SameMajorVersion)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
              ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME})

export(
  EXPORT ${PROJECT_NAME}Targets
  FILE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Targets.cmake"
  NAMESPACE ${PROJECT_NAME}::)
