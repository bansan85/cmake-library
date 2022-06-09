cmake_minimum_required(VERSION 3.21)

# Configuration of the project
project(
  library
  LANGUAGES CXX
  VERSION 1.2.3)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

option(BUILD_SHARED_LIBS "Build using shared libraries" OFF)

# Set default library path to install
include(GNUInstallDirs)
# Features to generate .cmake file for find_package.
include(CMakePackageConfigHelpers)

# Generator expressions
set(gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU,LCC>")
set(msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")

add_compile_options("$<${msvc_cxx}:/MP>")

# Configuration of the library
add_subdirectory(lib)

# Enable tests
include(CTest)
if(BUILD_TESTING)
  add_subdirectory(tests)
endif()

# Generate an installer (requires nsis)
include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/../LICENSE")
set(CPACK_PACKAGE_VERSION_MAJOR "${${PROJECT_NAME}_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${${PROJECT_NAME}_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${${PROJECT_NAME}_VERSION_PATCH}")
set(CPACK_PACKAGE_VERSION_TWEAK "${${PROJECT_NAME}_VERSION_TWEAK}")
set(CPACK_SOURCE_GENERATOR "TGZ")
file(TO_NATIVE_PATH "${path_suggested}/${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}" path_suggested)
string(REPLACE "\\" "\\\\" path_suggested "${path_suggested}")
set(CPACK_PACKAGE_INSTALL_DIRECTORY
    "${path_suggested}"
)
set(CPACK_NSIS_PACKAGE_NAME
    "${PROJECT_NAME} ${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}"
)
include(CPack)
