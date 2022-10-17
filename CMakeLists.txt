cmake_minimum_required(VERSION 3.21)
project(database-programming-1)

set(CMAKE_CXX_STANDARD 20)

add_executable(database-programming-1 main.cpp entities/employers.hpp entities/deposit.hpp entities/clients.hpp mappers/clients_mapper.hpp mappers/employer_mapper.hpp mappers/deposit_mapper.hpp sql_executor.hpp)

target_include_directories(database-programming-1 PRIVATE .)

target_link_libraries(database-programming-1 odbc32)
