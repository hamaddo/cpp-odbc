#ifndef DATABASE_PROGRAMMING_1_EMPLOYERS_HPP
#define DATABASE_PROGRAMMING_1_EMPLOYERS_HPP

#include <optional>
#include <utility>
#include "offer.hpp"

class Employer {
private:
    std::optional<int> id;
    std::wstring name;
    std::wstring ownership_type;
    std::wstring address;
    std::wstring phone;
    int contractNumber;

    std::vector<Offer *> offers;
public:
    const std::optional<int> &getId() const {
        return id;
    }

    const std::wstring &getName() const {
        return name;
    }

    const std::wstring &getOwnershipType() const {
        return ownership_type;
    }

    const std::wstring &getAddress() const {
        return address;
    }

    const std::wstring &getPhone() const {
        return phone;
    }

    int getContractNumber() const {
        return contractNumber;
    }

    void setId(const std::optional<int> &id_) {
        Employer::id = id_;
    }

    void setName(const std::wstring &name_) {
        Employer::name = name_;
    }

    void setOwnershipType(const std::wstring &ownershipType_) {
        ownership_type = ownershipType_;
    }

    void setAddress(const std::wstring &address_) {
        Employer::address = address_;
    }

    void setPhone(const std::wstring &phone_) {
        Employer::phone = phone_;
    }

    void setContractNumber(int contractNumber_) {
        Employer::contractNumber = contractNumber_;
    }

    friend std::wostream &operator<<(std::wostream &os, Employer *employer) {
        os << " name: " << employer->name << " ownership_type: " << employer->ownership_type
           << " address: " << employer->address << " phone: " << employer->phone << " contractNumber: "
           << employer->contractNumber;
        return os;
    }


};

#endif //DATABASE_PROGRAMMING_1_EMPLOYERS_HPP
