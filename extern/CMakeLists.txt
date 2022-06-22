cmake_minimum_required(VERSION 3.21)

# set the project name
project(Extern)

# You need to explicitly set BUILD_SHARED_LIBS option to enable static / shared
# library. But don't customize variable name.
option(BUILD_SHARED_LIBS "Build using shared libraries" OFF)

find_package(library REQUIRED)
find_package(library2 REQUIRED)
find_package(library3 REQUIRED)

# add the executable
add_executable(test1 main1.cpp)
target_link_libraries(test1 PRIVATE library)
add_executable(test2 main2.cpp)
target_link_libraries(test2 PRIVATE library2)
add_executable(test3 main3.cpp)
target_link_libraries(test3 PRIVATE library3)

include(CTest)
if(BUILD_TESTING)
  foreach(TESTI test1 test2 test3)
    add_test(NAME ${TESTI} COMMAND ${TESTI})
    # If you are under Windows with dynamic libraries, you need to copy dll in the
    # same path than the executable. RPATH is not supported under Windows.
    if(WIN32 AND BUILD_SHARED_LIBS)
      add_custom_command(
        TARGET ${TESTI}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                $<TARGET_RUNTIME_DLLS:${TESTI}> $<TARGET_FILE_DIR:${TESTI}>
        COMMAND_EXPAND_LISTS)
    endif()
  endforeach()
endif()
