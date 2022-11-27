#ifndef DATABASE_PROGRAMMING_1_OFFER_HPP
#define DATABASE_PROGRAMMING_1_OFFER_HPP


#include <optional>
#include <string>

class Offer {

private:
    std::optional<int> id;
    int employer_id;
    std::wstring position_name;
    int salary;
    std::wstring gender;

public:
    const std::optional<int> &getId() const {
        return id;
    }

    void setId(const std::optional<int> &_id) {
        id = _id;
    }

    const std::wstring &getPositionName() const {
        return position_name;
    }

    void setPositionName(const std::wstring &positionName) {
        position_name = positionName;
    }

    int getSalary() const {
        return salary;
    }

    void setSalary(int _salary) {
        salary = _salary;
    }

    const std::wstring &getGender() const {
        return gender;
    }

    void setGender(const std::wstring &_gender) {
        gender = _gender;
    }

    int getEmployerId() const {
        return employer_id;
    }

    void setEmployerId(int employerId) {
        employer_id = employerId;
    }

    friend std::wostream &operator<<(std::wostream &os, const Offer *offer) {
        os << L"Позиция: " << offer->getPositionName() << std::endl
           << L"Зарплата: " << offer->getSalary() << std::endl
           << L"Гендер: " << offer->getGender() << std::endl;
        return os;
    }

};


#endif //DATABASE_PROGRAMMING_1_OFFER_HPP
