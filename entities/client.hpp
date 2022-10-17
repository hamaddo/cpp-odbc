#ifndef DATABASE_PROGRAMMING_1_CLIENT_HPP
#define DATABASE_PROGRAMMING_1_CLIENT_HPP

#include <optional>
#include <utility>

struct client {
    std::optional<int> id;

    std::wstring name;
    std::wstring surname;
    std::wstring patronymic;

    std::wstring passport;

    std::wstring address;

    std::wstring phone;
};

#endif //DATABASE_PROGRAMMING_1_CLIENT_HPP
