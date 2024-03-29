cmake_minimum_required(VERSION 3.19)
set(CMAKE_CXX_STANDARD 20)
include(GNUInstallDirs)

set(PROJECT_NAME "telega_tests")
project(${PROJECT_NAME})

if(APPLE)
	set(OPENSSL_ROOT_DIR /opt/homebrew/Cellar/openssl@3/3.2.1/)
 	include_directories(/opt/homebrew/Cellar/openssl@3/3.2.1/include)
endif()

find_package(OpenSSL REQUIRED)

#	Tests coverage
set(COVERAGE_COMPILER_FLAGS "-fprofile-arcs -ftest-coverage")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COVERAGE_COMPILER_FLAGS}")

target_include_directories(../include)
add_executable(${PROJECT_NAME} tgtelegrambotapi_tests.cpp)

target_link_libraries(${PROJECT_NAME} LINK_PUBLIC ${OPENSSL_LIBRARIES} ${OPENSSL_SSL_LIBRARIES})
