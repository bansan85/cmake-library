cmake_minimum_required(VERSION 3.21)

project(Extern)

option(BUILD_SHARED_LIBS "Build using shared libraries" OFF)
option(BUILD_FETCH_CONTENT
       "Use FetchContext instead of find_package for external library" OFF)

if(BUILD_FETCH_CONTENT)
  include(FetchContent)
  set(BUILD_TESTING_SAVE ${BUILD_TESTING})
  set(BUILD_TESTING OFF)
  FetchContent_Declare(library4 SOURCE_DIR
                                "${CMAKE_CURRENT_SOURCE_DIR}/../library4")
  FetchContent_GetProperties(library4)
  if(NOT library4_POPULATED)
    FetchContent_Populate(library4)
    add_subdirectory(${library4_SOURCE_DIR} ${library4_BINARY_DIR}
                     EXCLUDE_FROM_ALL)
  endif()
  set(BUILD_TESTING ${BUILD_TESTING_SAVE})
else()
  find_package(library4 REQUIRED)
endif()

add_executable(test1 main1.cpp)
target_link_libraries(test1 PRIVATE library::library)
add_executable(test2 main2.cpp)
target_link_libraries(test2 PRIVATE library2::library2)
add_executable(test3 main3.cpp)
target_link_libraries(test3 PRIVATE library3::library3)
add_executable(test4 main4.cpp)
target_link_libraries(test4 PRIVATE library4::library4)

include(CTest)
if(BUILD_TESTING)
  foreach(TESTI test1 test2 test3 test4)
    add_test(NAME ${TESTI} COMMAND ${TESTI})
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
