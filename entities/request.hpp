#ifndef DATABASE_PROGRAMMING_1_REQUEST_HPP
#define DATABASE_PROGRAMMING_1_REQUEST_HPP


#include <string>
#include <optional>

class Request {
private:
    std::optional<int> id;
    std::wstring position_name;
    int salary;

    int client_id;

public:

    const std::wstring &getPositionName() const {
        return position_name;
    }

    void setPositionName(const std::wstring &positionName) {
        position_name = positionName;
    }

    int getSalary() const {
        return salary;
    }

    void setSalary(int salary) {
        Request::salary = salary;
    }

    const std::optional<int> &getId() const {
        return id;
    }

    void setId(const std::optional<int> &id) {
        Request::id = id;
    }

    int getClientId() const {
        return client_id;
    }

    void setClientId(int clientId) {
        client_id = clientId;
    }

};


#endif //DATABASE_PROGRAMMING_1_REQUEST_HPP
