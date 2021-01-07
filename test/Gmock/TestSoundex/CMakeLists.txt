find_package(GTest REQUIRED CONFIG)

FILE(GLOB SRCFILELIST
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_SOURCE_DIR}/Src/Soundex/*.cpp")

add_executable(gmock_Soundex ${SRCFILELIST})

target_link_libraries(gmock_Soundex
    GTest::gmock
    GTest::gmock_main
    ${LOCAL_LINK_LIB} 
    )