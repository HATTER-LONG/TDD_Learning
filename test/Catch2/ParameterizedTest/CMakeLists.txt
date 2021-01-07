find_package(Catch2 REQUIRED CONFIG)

FILE(GLOB SRCFILELIST
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
   )

add_executable(catch2_Parameterized ${SRCFILELIST})

target_link_libraries(catch2_Parameterized
    Catch2::Catch2WithMain
    ${LOCAL_LINK_LIB} 
    )