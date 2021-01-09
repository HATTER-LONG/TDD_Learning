find_package(GTest REQUIRED CONFIG)
find_package(jsoncpp REQUIRED CONFIG)
FILE(GLOB SRCFILELIST
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_SOURCE_DIR}/Src/PlaceDescriptionService/*.cpp"
   )

add_executable(gmock_PlaceDescriptionService ${SRCFILELIST})

target_link_libraries(gmock_PlaceDescriptionService
    GTest::gmock
    GTest::gmock_main
    jsoncpp_lib_static
    ${LOCAL_LINK_LIB} 
    )