cmake_minimum_required(VERSION 3.5)

if($ENV{TRAVIS_BUILD_NUMBER})
    project(DlibClustering VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
    project(DlibClustering)
endif()

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
if (MSVC)
    target_compile_options(kkmeans PRIVATE
            /W4
            )
else ()
    target_compile_options(kkmeans PRIVATE
            -Wall -Wextra -pedantic -Werror
            )
endif()

install(TARGETS kkmeans RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT lismut@gmail.com)

include(CPack)