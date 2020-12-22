find_package(GTest REQUIRED CONFIG)

set(TESTSRC ./main.cpp)

add_executable(gmock_tdd_test ${TESTSRC})

target_link_libraries(gmock_tdd_test
  GTest::gmock
  GTest::gmock_main
  ${LOCAL_LINK_LIB} 
  )