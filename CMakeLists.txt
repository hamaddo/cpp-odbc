cmake_minimum_required(VERSION 3.21)
project(database-programming-1)

set(CMAKE_CXX_STANDARD 20)

add_executable(database-programming-1 main.cpp entities/employers.hpp entities/clients.hpp mappers/clients_mapper.hpp mappers/employer_mapper.hpp helpers/clients_helper.hpp sql_executor.hpp helpers/abstract_helper.hpp helpers/employer_helper.hpp entities/request.hpp entities/offer.hpp)

target_include_directories(database-programming-1 PRIVATE .)

target_link_libraries(database-programming-1 odbc32)
