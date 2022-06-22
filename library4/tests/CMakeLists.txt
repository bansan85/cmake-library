add_executable(test1 test1.cpp)
target_link_libraries(test1 PRIVATE ${PROJECT_NAME})

foreach(TESTI test1)
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
