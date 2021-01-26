find_package(Catch2 REQUIRED CONFIG)
find_package(Boost COMPONENTS filesystem system)
FILE(GLOB SRCFILELIST
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_SOURCE_DIR}/Src/SnippetPublisher/*.cpp")

add_executable(catch2_SnippetPublisher ${SRCFILELIST})

target_link_libraries(catch2_SnippetPublisher
    Catch2::Catch2WithMain
    ${LOCAL_LINK_LIB}
    ${Boost_LIBRARIES}
    )