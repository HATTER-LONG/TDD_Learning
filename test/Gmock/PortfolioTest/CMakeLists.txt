find_package(GTest REQUIRED CONFIG)

FILE(GLOB SRCFILELIST
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_SOURCE_DIR}/Src/Portfolio/*.cpp"
   )

add_executable(gmock_PortfolioTest ${SRCFILELIST})

target_link_libraries(gmock_PortfolioTest
    GTest::gmock
    GTest::gmock_main
    ${LOCAL_LINK_LIB} 
    )