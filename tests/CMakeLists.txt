cmake_minimum_required(VERSION 3.19)
set(CMAKE_CXX_STANDARD 20)
include(GNUInstallDirs)

set(TARGET_NAME "telega_tests")
project(${TARGET_NAME})

#	Define source files
set(SOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../src)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../include)
set(SOURCE_FILES tgtelegrambotapi_tests.cpp ${SOURCES_DIR}/tghttprequestservice.cpp ${SOURCES_DIR}/tgsslsocket.cpp ${SOURCES_DIR}/tgtelegrambotapi.cpp ${SOURCES_DIR}/tgtools.cpp)
set(INCLUDE_FILES ${INCLUDE_DIR}/tghttprequestservice.h ${INCLUDE_DIR}/tgsslsocket.h ${INCLUDE_DIR}/tgtelegrambotapi.h ${INCLUDE_DIR}/tgtools.h)

#	Create target
add_executable(${TARGET_NAME} ${SOURCE_FILES} ${INCLUDE_FILES})
target_include_directories(${TARGET_NAME} PRIVATE ${INCLUDE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/../submodules/doctest)

#	Link libraries
if(APPLE)
	set(OPENSSL_ROOT_DIR /opt/homebrew/Cellar/openssl@3/3.2.1/)
 	target_include_directories(${TARGET_NAME} PRIVATE /opt/homebrew/Cellar/openssl@3/3.2.1/include)
endif()
find_package(OpenSSL REQUIRED)
target_link_libraries(${TARGET_NAME} LINK_PUBLIC ${OPENSSL_LIBRARIES} ${OPENSSL_SSL_LIBRARIES})

#	Compiler flags
set(COVERAGE_COMPILER_FLAGS "-fprofile-arcs -ftest-coverage")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COVERAGE_COMPILER_FLAGS}")
