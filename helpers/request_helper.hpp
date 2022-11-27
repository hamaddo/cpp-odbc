#ifndef DATABASE_PROGRAMMING_1_REQUEST_HELPER_HPP
#define DATABASE_PROGRAMMING_1_REQUEST_HELPER_HPP


#include "abstract_helper.hpp"
#include "mappers/request_mapper.hpp"

class RequestHelper: public AbstractHelper{
private:
    RequestMapper &mapper_instance;
    int client_id;
public:
    explicit RequestHelper(RequestMapper &mapper_instance_) : mapper_instance(mapper_instance_) {

    }

    void setClientId(int clientId) {
        client_id = clientId;
    }

    void printActions() override {
        std::wcout << std::endl << L"--- Заявки клиента ---" << std::endl
                   << L"1. Показать все заявки" << std::endl
                   << L"2. Найти заявку по порядковому номеру" << std::endl
                   << L"3. Изменить данные заявки" << std::endl
                   << L"4. Создать заявку" << std::endl
                   << L"5. Удалить заявку" << std::endl << std::endl;

        std::wcout << L"0. Выход" << std::endl;
    }

    void print() override {
        auto result = mapper_instance.readAll(client_id);
        int order = 1;
        for (auto i: result) {
            std::wcout << order++ << L". " << i << std::endl;
        }
    }

    void read() override {
        int order;
        std::wcin >> order;
        auto result = mapper_instance.read(order - 1, client_id);
        std::wcout << result << std::endl;
    }

    void create() override {
        Request request;
        std::wstring name;
        int number;

        std::wcout << "Enter position name: ";
        std::getline(std::wcin >> std::ws, name);
        request.setPositionName(name);

        std::wcout << "Enter salary: ";
        std::wcin >> number;
        request.setSalary(number);

        request.setClientId(client_id);

        mapper_instance.create(request);
    }

    void remove() override {
        int order;
        std::wcin >> order;

        auto result = mapper_instance.remove(order - 1, client_id);

        int position = 1;
        for (auto i: result) {
            std::wcout << position++ << L". " << i << std::endl;
        }

    }

    void update() override {
    }

    void goToChild() override {

    }
};


#endif //DATABASE_PROGRAMMING_1_REQUEST_HELPER_HPP
