find_package(Catch2 REQUIRED CONFIG)

FILE(GLOB SRCFILELIST
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_SOURCE_DIR}/Src/Portfolio/*.cpp"
   )

add_executable(cathc2_PortfolioTest ${SRCFILELIST})

target_link_libraries(cathc2_PortfolioTest
    Catch2::Catch2WithMain
    ${LOCAL_LINK_LIB} 
    )