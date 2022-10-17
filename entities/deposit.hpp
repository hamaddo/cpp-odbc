#ifndef DATABASE_PROGRAMMING_1_DEPOSIT_HPP
#define DATABASE_PROGRAMMING_1_DEPOSIT_HPP

#include <optional>
#include <utility>

struct deposit {
    std::optional<int> id;

    std::wstring name;

    int term;
    float annual;
};

#endif //DATABASE_PROGRAMMING_1_DEPOSIT_HPP
