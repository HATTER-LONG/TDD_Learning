find_package(Catch2 REQUIRED CONFIG)

set(TESTSRC ./main.cpp)

add_executable(catch2_tdd_test ${TESTSRC})

target_link_libraries(catch2_tdd_test
    Catch2::Catch2WithMain
    ${LOCAL_LINK_LIB} 
    )