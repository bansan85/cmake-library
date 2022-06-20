configure_file(${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/version.h.in
               ${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/version.h)

set(${PROJECT_NAME}_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/lib.cpp)
set(${PROJECT_NAME}_HEADER
    ${CMAKE_CURRENT_SOURCE_DIR}/include/library/lib.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/library/subfolder/helper.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/library/version.h)

add_library(${PROJECT_NAME})
target_sources(
  ${PROJECT_NAME}
  PRIVATE ${${PROJECT_NAME}_SRC}
  PUBLIC FILE_SET HEADERS BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include/ FILES
         ${${PROJECT_NAME}_HEADER})
if(BUILD_SHARED_LIBS)
  # EXPORT_ALL_SYMBOLS generates .lib with all symbols from .dll. This is needed
  # because Windows can only link .lib file.
  set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
  # No need to set CMAKE_POSITION_INDEPENDENT_CODE. It's already TRUE for shared
  # library and FALSE for static library.
else(BUILD_SHARED_LIBS)
  target_compile_definitions(${PROJECT_NAME} PUBLIC ${PROJECT_NAME}_STATIC)
endif()

# Show headers in Visual Studio.
source_group("Header Files" FILES ${${PROJECT_NAME}_HEADER})

target_include_directories(
  ${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                         $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

# Don't set PUBLIC_HEADER because files will be installed without keeping
# structure.

# set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER
# "${${PROJECT_NAME}_HEADER}")

# No need to tell more if default values are good.
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
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME})

# Generate and install .cmake files.
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

# generate the export targets for the build tree needs to be after the
# install(TARGETS) command
export(EXPORT ${PROJECT_NAME}Targets
       FILE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Targets.cmake")
