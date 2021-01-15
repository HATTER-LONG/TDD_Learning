find_package(GTest REQUIRED CONFIG)
find_package(jsoncpp REQUIRED CONFIG)
FILE(GLOB SRCFILELIST
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_SOURCE_DIR}/Src/PlaceDescriptionServiceMock/*.cpp"
   )

# 当前使用的 googletest 版本为 1.10.x MOCK_METHOD 宏在编译器下会有错误信息，依据 gmock issues 无用报错 关闭相关警告
add_definitions(-Wno-gnu-zero-variadic-macro-arguments)
add_executable(gmock_PlaceDescriptionServiceByGmock ${SRCFILELIST})

target_link_libraries(gmock_PlaceDescriptionServiceByGmock
    GTest::gmock
    GTest::gmock_main
    jsoncpp_lib_static
    ${LOCAL_LINK_LIB} 
    )