cmake_minimum_required(VERSION 3.19)
set(CMAKE_CXX_STANDARD 20)
include(GNUInstallDirs)

set(PROJECT_NAME "telega")
project(${PROJECT_NAME})
set(SOURCE_FILES src/telega.cpp src/tghttprequestservice.cpp src/tgsslsocket.cpp src/tgtelegrambotapi.cpp src/tgtools.cpp)
set(INCLUDE_FILES include/tghttprequestservice.h include/tgsslsocket.h include/tgtelegrambotapi.h include/tgtools.h)

if(APPLE)
	set(OPENSSL_ROOT_DIR /opt/homebrew/Cellar/openssl@3/3.2.1/)
 	include_directories(/opt/homebrew/Cellar/openssl@3/3.2.1/include)
endif()

find_package(OpenSSL REQUIRED)

#	Tests coverage
set(COVERAGE_COMPILER_FLAGS "-fprofile-arcs -ftest-coverage")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COVERAGE_COMPILER_FLAGS}")

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${INCLUDE_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE include)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC ${OPENSSL_LIBRARIES} ${OPENSSL_SSL_LIBRARIES})
