add_executable(main.cpp)

target_include_directories(PRIVATE ${SFML_INCLUDE_DIR})
target_compile_features(PUBLIC cxx_std_17)
target_compile_definitions(PRIVATE SFML_STATIC)

target_link_libraries(${SFML_LIBRARIES} ${SFML_DEPENDENCIES})