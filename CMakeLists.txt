cmake_minimum_required(VERSION 3.5)

project(31.DlibClustering)

find_package(BLAS REQUIRED)

add_executable(kkmeans kkmeans_ex.cpp)

set_target_properties(kkmeans PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        )

target_link_libraries(kkmeans
        dlib
        blas
        lapack
        )
