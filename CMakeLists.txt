cmake_minimum_required(VERSION 3.19)
set(CMAKE_CXX_STANDARD 20)
include(GNUInstallDirs)

set(PROJECT_NAME "telega")
project(${PROJECT_NAME})

include_directories(include)
if(APPLE)
	set(OPENSSL_ROOT_DIR /opt/homebrew/Cellar/openssl@3/3.2.1/)
 	include_directories(/opt/homebrew/Cellar/openssl@3/3.2.1/include)
endif()

if(UNIX AND NOT APPLE)
	set(OPENSSL_ROOT_DIR /usr/local)
	find_package(PkgConfig REQUIRED)

	pkg_check_modules(Tesseract REQUIRED IMPORTED_TARGET tesseract lept)
	add_library(Tesseract::libtesseract ALIAS PkgConfig::Tesseract)
endif()

find_package(OpenSSL REQUIRED)

#	Tests coverage
set(COVERAGE_COMPILER_FLAGS "-fprofile-arcs -ftest-coverage")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COVERAGE_COMPILER_FLAGS}")

add_executable(${PROJECT_NAME} src/telega.cpp src/tghttprequestservice.cpp src/tgsslsocket.cpp src/tgtelegrambotapi.cpp src/tgtools.cpp)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC ${OPENSSL_LIBRARIES} ${OPENSSL_SSL_LIBRARIES})
