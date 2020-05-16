cmake_minimum_required(VERSION 3.5)

project(31.DlibClustering)

add_executable(kkmeans_ex kkmeans_ex.cpp)

set_target_properties(kkmeans_ex PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        )

target_link_libraries(kkmeans_ex
        dlib
        )
