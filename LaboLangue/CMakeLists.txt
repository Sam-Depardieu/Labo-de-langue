find_package(Qt6 REQUIRED COMPONENTS Multimedia)
target_link_libraries(${LaboLangue} PRIVATE Qt6::Multimedia)

add_library(ts3client SHARED IMPORTED)
set_target_properties(ts3client PROPERTIES IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/lib/ts3client.so")

target_include_directories(my_project PRIVATE "${CMAKE_SOURCE_DIR}/include")
target_link_libraries(my_project ts3client)
