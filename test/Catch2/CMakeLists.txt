find_package(Catch2 REQUIRED CONFIG)

FILE(GLOB SRCFILELIST
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
add_executable(catch2_tdd_test ${SRCFILELIST})

target_link_libraries(catch2_tdd_test
    Catch2::Catch2WithMain
    ${LOCAL_LINK_LIB} 
    )