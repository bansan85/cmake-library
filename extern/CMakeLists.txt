cmake_minimum_required(VERSION 3.21)

project(Extern)

option(BUILD_SHARED_LIBS "Build using shared libraries" OFF)

find_package(library REQUIRED)
find_package(library2 REQUIRED)
find_package(library3 REQUIRED)
find_package(library4 REQUIRED)

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
