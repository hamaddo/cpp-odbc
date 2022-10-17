#ifndef DATABASE_PROGRAMMING_1_EMPLOYERS_HPP
#define DATABASE_PROGRAMMING_1_EMPLOYERS_HPP

#include <optional>
#include <utility>

struct employers {
    std::optional<int> id;

    std::wstring company_name;
    std::wstring olf;
    std::wstring ownership_type;

    std::wstring address;

    std::wstring phone;

    std::wstring personnel_inspector_fullname;
};

#endif //DATABASE_PROGRAMMING_1_EMPLOYERS_HPP
