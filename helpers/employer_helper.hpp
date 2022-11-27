#ifndef DATABASE_PROGRAMMING_1_EMPLOYER_HELPER_HPP
#define DATABASE_PROGRAMMING_1_EMPLOYER_HELPER_HPP

#include <iostream>
#include "abstract_helper.hpp"
#include "mappers/employer_mapper.hpp"

class EmployerHelper : public AbstractHelper {
private:
    EmployerMapper &mapper_instance;
public:
    explicit EmployerHelper(EmployerMapper &mapper_instance_) : mapper_instance(mapper_instance_) {

    }

    void printActions() override {
        std::wcout << std::endl << L"--- Работодатели ---" << std::endl
                   << L"1. Показать всех работодателей" << std::endl
                   << L"2. Найти работодателя по порядковому номеру" << std::endl
                   << L"3. Изменить данные работодателя" << std::endl
                   << L"4. Создать работодателя" << std::endl
                   << L"5.Удалить работодателя" << std::endl << std::endl;

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
        Employer employer;
        std::wstring name;
        std::wstring ownership_type;
        std::wstring address;
        std::wstring phone;

        int number;

        std::wcout << "Enter name: " << std::endl;
        std::getline(std::wcin >> std::ws, name);
        employer.setName(name);

        std::wcout << "Enter ownership type: " << std::endl;
        std::wcin >> ownership_type;
        employer.setOwnershipType(ownership_type);

        std::wcout << "Enter address: " << std::endl;
        std::getline(std::wcin >> std::ws, address);
        employer.setAddress(address);

        std::wcout << "Enter phone: " << std::endl;
        std::wcin >> phone;
        employer.setPhone(phone);


        std::wcout << "Enter contract number: " << std::endl;
        std::wcin >> number;
        employer.setContractNumber(number);

        mapper_instance.create(employer);
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

};


#endif //DATABASE_PROGRAMMING_1_EMPLOYER_HELPER_HPP
