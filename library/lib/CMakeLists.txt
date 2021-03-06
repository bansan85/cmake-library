# Linux / gcc will fails to run test when nested dependencies.

# Windows doesn't support RPATH and will do nothing.
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_LIBDIR}")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

if(BUILD_SHARED_LIBS)
  # EXPORT_ALL_SYMBOLS generates .lib with all symbols from .dll. This is needed
  # because Windows can only link .lib file and will avoid to set the .def file.
  set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
  # No need to set CMAKE_POSITION_INDEPENDENT_CODE if you don't mix shared and
  # static library. It's already TRUE for shared library and FALSE for static
  # library.
endif(BUILD_SHARED_LIBS)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/version.h.in
               ${CMAKE_CURRENT_BINARY_DIR}/include/${PROJECT_NAME}/version.h)

add_library(${PROJECT_NAME})

include(GenerateExportHeader)

# Generate file based on configuration of the library set in target field. This
# file will set LIBRARY_EXPORT define to:

# * dllimport/dllexport for Windows shared library,

# * visibility ("default") / visibility ("hidden") for Linux shared library,

# * empty for static library.

# See https://gcc.gnu.org/wiki/Visibility for more information.
generate_export_header(
  ${PROJECT_NAME} BASE_NAME ${PROJECT_NAME} EXPORT_FILE_NAME
  ${CMAKE_CURRENT_BINARY_DIR}/include/${PROJECT_NAME}/subfolder/helper.h)

set(${PROJECT_NAME}_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/lib.cpp)
set(${PROJECT_NAME}_HEADER
    ${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/lib.h)
set(${PROJECT_NAME}_HEADER_AUTO
    ${CMAKE_CURRENT_BINARY_DIR}/include/${PROJECT_NAME}/subfolder/helper.h
    ${CMAKE_CURRENT_BINARY_DIR}/include/${PROJECT_NAME}/version.h)

# The use of FILE_SET HEADER (instead of PUBLIC_HEADER) keeps the tree folder
# and groups header files in Visual Studio.
target_sources(
  ${PROJECT_NAME}
  PRIVATE ${${PROJECT_NAME}_SRC}
  PUBLIC FILE_SET HEADERS BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include/ FILES
         ${${PROJECT_NAME}_HEADER}
  PUBLIC FILE_SET HEADERS BASE_DIRS ${CMAKE_CURRENT_BINARY_DIR}/include/ FILES
         ${${PROJECT_NAME}_HEADER_AUTO})
if(NOT BUILD_SHARED_LIBS)
  # For static library, you need to add a define to know you built library in
  # static mode.

  # In shared mode, CMake automatically defines ${PROJECT_NAME}_Export in
  # private.
  target_compile_definitions(${PROJECT_NAME}
                             PUBLIC ${PROJECT_NAME}_STATIC_DEFINE)
endif(NOT BUILD_SHARED_LIBS)

# BUILD_INTERFACE will be the include folder when you build the library.

# INSTALL_INTERFACE will be the include folder when you import the library via
# find_package.
target_include_directories(
  ${PROJECT_NAME}
  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
         $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
         $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

# List all files you want to install.
install(
  TARGETS ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}Targets
  FILE_SET HEADERS
  RUNTIME
  LIBRARY
  ARCHIVE)

# Generate and install Targets.cmake files for find_package.

# NAMESPACE is usefull to generate an alias library::library.
install(
  EXPORT ${PROJECT_NAME}Targets
  FILE ${PROJECT_NAME}Targets.cmake
  NAMESPACE ${PROJECT_NAME}::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME})

# Generate and install Config.cmake files.
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

# Generation of the export targets for the build tree needs to be after the
# install(TARGETS) command.
export(
  EXPORT ${PROJECT_NAME}Targets
  FILE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Targets.cmake"
  NAMESPACE ${PROJECT_NAME}::)
