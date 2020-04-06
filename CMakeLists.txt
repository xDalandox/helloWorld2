cmake_minimum_required(VERSION 3.14)

if(NOT TRAVIS_BUILD_NUMBER)
    set(PATCH 27)
else()
    set(PATCH $ENV{TRAVIS_BUILD_NUMBER})
endif()

project(HelloWorld VERSION 0.0.${PATCH})

find_package(boost REQUIRED COMPONENTS unit_test_framework)

message("Boost library dirs are ${Boost_INCLUDE_DIRS}")

configure_file(version.h.in version.h)

add_executable(HelloWorld main.cpp)
add_library(HelloWorldLib STATIC lib.cpp)
add_executable(test_version test_version.cpp)

set_target_properties(HelloWorld HelloWorldLib test_version PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        )

#find out what does it do
target_include_directories(HelloWorldLib
        PRIVATE "${CMAKE_BINARY_DIR}"
        )

set_target_properties(test_version PROPERTIES
        COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
        INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
        )

target_link_libraries(HelloWorld PRIVATE
        HelloWorldLib
        )

target_link_libraries(test_version
        ${Boost_LIBRARIES}
        HelloWorldLib
        )

if(MSVC)
    target_compile_options(HelloWorld PRIVATE
            /W4
            )
    target_compile_options(HelloWorldLib PRIVATE
            /W4
            )
    target_compile_options(test_version PRIVATE
            /W4
            )
else()
    target_compile_options(HelloWorld PRIVATE
            -Wall -Wextra -pedantic -Werror
            )
    target_compile_options(HelloWorldLib PRIVATE
            -Wall -Wextra -pedantic -Werror
            )
    target_compile_options(test_version PRIVATE
            -Wall -Wextra -pedantic -Werror
            )
endif()

install(TARGETS HelloWorld RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)

enable_testing()

add_test(test_version test_version)