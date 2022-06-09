cmake_minimum_required(VERSION 3.21)

# set the project name
project(Extern)

find_package(library REQUIRED)

# add the executable
add_executable(test2 main.cpp)
target_link_libraries(test2 PRIVATE library)

include(CTest)
if(BUILD_TESTING)
  add_test(NAME test2 COMMAND test2)
  if(WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(
      TARGET test2
      POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_if_different
              $<TARGET_RUNTIME_DLLS:test2> $<TARGET_FILE_DIR:test2>
      COMMAND_EXPAND_LISTS)
  endif()
endif()
