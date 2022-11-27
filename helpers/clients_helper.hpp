#ifndef DATABASE_PROGRAMMING_1_CLIENTS_HELPER_HPP
#define DATABASE_PROGRAMMING_1_CLIENTS_HELPER_HPP


#include <iostream>
#include "abstract_helper.hpp"
#include "mappers/clients_mapper.hpp"

class ClientsHelper : public AbstractHelper {
private:
    ClientsMapper &mapper_instance;
public:
    explicit ClientsHelper(ClientsMapper &mapper_instance_) : mapper_instance(mapper_instance_) {

    }

    void printActions() override {
        std::wcout << std::endl << L"--- Клиенты ---" << std::endl
                   << L"1. Показать всех клиентов" << std::endl
                   << L"2. Найти клиента по порядковому номеру" << std::endl
                   << L"3. Изменить данные клиента" << std::endl
                   << L"4. Создать клиента" << std::endl
                   << L"5. Удалить клиента" << std::endl
                   << L"6. Перейти к заявкам клиента по порядковому номеру" << std::endl << std::endl;

        std::wcout << L"0. Выход" << std::endl;
    }

    void print() override {
        auto result = mapper_instance.readAll();
        int position = 1;
        for (auto i: result) {
            std::wcout << position++ << L". " << i << std::endl;
        }
    }

    void read() override {
        int order;
        std::wcin >> order;
        auto result = mapper_instance.read(order - 1);
        std::wcout << result << std::endl;
    }

    void create() override {
        Client client;
        std::wstring name;
        std::wstring address;
        std::wstring gender;
        std::wstring phone;
        int number;

        std::wcout << "Enter name: ";
        std::getline(std::wcin >> std::ws, name);
        client.setFullName(name);

        std::wcout << "Enter registry number: ";
        std::cin >> number;
        client.setRegistryNumber(number);

        std::wcout << "Enter address: ";
        std::getline(std::wcin >> std::ws, address);
        client.setAddress(address);

        std::wcout << "Enter gender: ";
        std::wcin >> gender;
        client.setGender(gender);

        std::wcout << "Enter phone: ";
        std::wcin >> phone;
        client.setPhone(phone);

        mapper_instance.create(client);
    }

    void remove() override {
        int order;
        std::wcin >> order;

        auto result = mapper_instance.remove(order - 1);

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


#endif //DATABASE_PROGRAMMING_1_CLIENTS_HELPER_HPP
