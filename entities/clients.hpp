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


    friend std::wostream &operator<<(std::wostream &out, clients &client_) {
        if (client_.id.has_value()) {
            out << client_.id.value() << ' ';
        }
        out << client_.full_name << ' ' << client_.address << ' ' << client_.receipt_number << ' ' << client_.gender
            << ' '
            << client_.registry_number;

        return out;
    };
};

#endif //DATABASE_PROGRAMMING_1_CLIENTS_HPP
