find_package(Catch2 REQUIRED CONFIG)

FILE(GLOB SRCFILELIST
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_SOURCE_DIR}/Src/GeoServer/*.cpp"
   )

add_executable(catch2_GeoServerTest ${SRCFILELIST})

target_link_libraries(catch2_GeoServerTest
    Catch2::Catch2WithMain
    ${LOCAL_LINK_LIB} 
    )