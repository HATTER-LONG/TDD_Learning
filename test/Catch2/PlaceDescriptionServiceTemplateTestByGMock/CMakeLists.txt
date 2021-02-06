find_package(Catch2 REQUIRED CONFIG)
find_package(jsoncpp REQUIRED CONFIG)
find_package(GTest REQUIRED CONFIG)

FILE(GLOB SRCFILELIST
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_SOURCE_DIR}/Src/PlaceDescriptionServiceTemplateMock/*.cpp"
   )

# 当前使用的 googletest 版本为 1.10.x MOCK_METHOD 宏在编译器下会有错误信息，依据 gmock issues 无用报错 关闭相关警告
add_definitions(-Wno-gnu-zero-variadic-macro-arguments)
add_executable(cathc2_PlaceDescriptionServiceTemplateByGmock ${SRCFILELIST})

target_link_libraries(cathc2_PlaceDescriptionServiceTemplateByGmock
    Catch2::Catch2WithMain
    GTest::gmock
    jsoncpp_lib_static
    ${LOCAL_LINK_LIB} 
    )