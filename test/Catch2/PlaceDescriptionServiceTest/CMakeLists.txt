find_package(Catch2 REQUIRED CONFIG)
find_package(jsoncpp REQUIRED CONFIG)
FILE(GLOB SRCFILELIST
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_SOURCE_DIR}/Src/PlaceDescriptionService/*.cpp"
   )

add_executable(catch2_PlaceDescriptionService ${SRCFILELIST})

target_link_libraries(catch2_PlaceDescriptionService
    Catch2::Catch2WithMain
    jsoncpp_static
    ${LOCAL_LINK_LIB} 
    )