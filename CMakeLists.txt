cmake_minimum_required(VERSION 3.5.0)
project(faqyh VERSION 0.0.2 LANGUAGES C CXX)
message(STATUS "Project version: ${PROJECT_VERSION}")
set (CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -no-pie -O3 -g0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -no-pie -O3 -g0 -flto")

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(${PROJECT_NAME} 
${PROJECT_SOURCE_DIR}/src/main.cpp 
${PROJECT_SOURCE_DIR}/src/logger.cpp 
${PROJECT_SOURCE_DIR}/src/hwinfo.cpp 
${PROJECT_SOURCE_DIR}/src/formatter.cpp
${PROJECT_SOURCE_DIR}/src/terminalscreen.cpp)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)