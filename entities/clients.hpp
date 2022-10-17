#ifndef DATABASE_PROGRAMMING_1_CLIENTS_HPP
#define DATABASE_PROGRAMMING_1_CLIENTS_HPP

#include <optional>
#include <sqlext.h>

struct clients {
    std::optional<int> id;

    int registry_number;
    std::wstring full_name;
    std::wstring address;
    std::wstring gender;

    int receipt_number;
};

#endif //DATABASE_PROGRAMMING_1_CLIENTS_HPP
