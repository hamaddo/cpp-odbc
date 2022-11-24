#ifndef DATABASE_PROGRAMMING_1_CLIENTS_HPP
#define DATABASE_PROGRAMMING_1_CLIENTS_HPP

#include <optional>
#include <sqlext.h>
#include <ostream>


class Client {
private:
    std::optional<int> client_id;
    std::wstring full_name;
    int registry_number;
    std::wstring address;
    std::wstring gender;
    std::wstring phone;

public:
    Client() {
        client_id = -1;
        full_name = L"";
        registry_number = 0;
        address = L"";
        gender = L"";
        phone = L"";
    };

    ~Client() {

    };

    const std::optional<int> &getClientId() const {
        return client_id;
    }

    void setClientId(const std::optional<int> &clientId) {
        client_id = clientId;
    }

    const std::wstring &getFullName() const {
        return full_name;
    }

    void setFullName(const std::wstring &fullName) {
        full_name = fullName;
    }

    int getRegistryNumber() const {
        return registry_number;
    }

    void setRegistryNumber(int registryNumber) {
        registry_number = registryNumber;
    }

    const std::wstring &getAddress() const {
        return address;
    }

    void setAddress(const std::wstring &address) {
        Client::address = address;
    }

    const std::wstring &getGender() const {
        return gender;
    }

    void setGender(const std::wstring &gender) {
        Client::gender = gender;
    }

    const std::wstring &getPhone() const {
        return phone;
    }

    void setPhone(const std::wstring &phone) {
        Client::phone = phone;
    }

    friend std::wostream &operator<<(std::wostream &out, Client &client_) {

        out << client_.client_id.value() << ' ';

        out << client_.full_name << ' ' << client_.address << ' ' << client_.phone << ' ' << client_.gender
            << ' '
            << client_.registry_number;

        return out;
    }
};

#endif //DATABASE_PROGRAMMING_1_CLIENTS_HPP
