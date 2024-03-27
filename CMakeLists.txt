cmake_minimum_required(VERSION 3.19)
set(CMAKE_CXX_STANDARD 20)
include(GNUInstallDirs)

set(PROJECT_NAME "telega")
project(${PROJECT_NAME})

set(OPENSSL_ROOT_DIR /opt/homebrew/Cellar/openssl@3/3.2.1/)
include_directories(/opt/homebrew/Cellar/openssl@3/3.2.1/include)

find_package(OpenSSL REQUIRED)

#	Tests coverage
set(COVERAGE_COMPILER_FLAGS "-g --coverage -fprofile-arcs -ftest-coverage")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COVERAGE_COMPILER_FLAGS}")

add_executable(${PROJECT_NAME} telega.cpp tghttprequestservice.cpp tgsslsocket.cpp tgtelegrambotapi.cpp tgtools.cpp)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC ${OPENSSL_LIBRARIES} ${OPENSSL_SSL_LIBRARIES})
