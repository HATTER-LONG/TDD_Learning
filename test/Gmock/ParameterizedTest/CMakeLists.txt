find_package(GTest REQUIRED CONFIG)

FILE(GLOB SRCFILELIST
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
   )

add_executable(gmock_Parameterized ${SRCFILELIST})

target_link_libraries(gmock_Parameterized
    GTest::gmock
    GTest::gmock_main
    ${LOCAL_LINK_LIB} 
    )