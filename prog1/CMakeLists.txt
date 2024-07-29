cmake_minimum_required(VERSION 3.10)


project(prog1 VERSION 1.0)


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)


cmake_policy(SET CMP0167 NEW)


find_package(Boost 1.85 REQUIRED COMPONENTS system filesystem)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_executable(prog1 main.cpp Client.cpp StringProcessor.cpp)
    target_link_libraries(prog1 PRIVATE
    ${Boost_LIBRARIES}
    ws2_32
)
else()
    message(FATAL_ERROR "Boost не найден")
endif()