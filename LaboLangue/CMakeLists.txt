find_package(Qt6 REQUIRED COMPONENTS Multimedia)
target_link_libraries(${LaboLangue} PRIVATE Qt6::Multimedia)

find_package(ZeroMQ REQUIRED)
target_link_libraries(${LaboLangue} PRIVATE ZeroMQ::libzmq)