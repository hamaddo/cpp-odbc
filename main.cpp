#include <fcntl.h>
#include "sql_executor.hpp"
#include "mappers/employer_mapper.hpp"
#include "mappers/clients_mapper.hpp"


bool menu(EmployerMapper &employer_instance,
          ClientsMapper &clients_instance) {
    auto should_break = false;

    while (!should_break) {
        int choice = -1;

        std::wcout << L"--- Клиенты ---" << std::endl
                   << L"1. Показать всех клиентов" << std::endl
                   << L"2. Найти клиента по порядковому номеру" << std::endl
                   << L"3. Изменить данные клиента" << std::endl
                   << L"4. Создать клиента" << std::endl
                   << L"5. Удалить клиента" << std::endl << std::endl;

        std::wcout << L"--- Работодатели ---" << std::endl
                   << L"6. Показать всех работодателей" << std::endl
                   << L"7. Найти работодателя по порядковому номеру" << std::endl
                   << L"8. Изменить данные работодателя" << std::endl
                   << L"9. Создать работодателя" << std::endl
                   << L"10.Удалить работодателя" << std::endl << std::endl;

        std::wcout << L"0. Выход";

        std::cin >> choice;

        std::wcout << std::endl;


        switch (choice) {
            case (0) : {
                should_break = true;

                break;
            }
            case (1): {
                auto result = clients_instance.readAll();
                for (auto &i: result) {
                    std::wcout << i << std::endl;
                }

                break;
            }
            case (2): {
                int choice_id = -1;
                std::wcout << L"--- Введите порядковый номер ---" << std::endl;
                std::cin >> choice_id;
                auto result = clients_instance.read(choice_id);
                for (auto &i: result) {
                    std::wcout << i << std::endl;
                }
                break;
            }
            case (4): {
                Client client;
                std::wstring wstr;
                int number;

                std::wcout << "Enter name: ";
                std::wcin.ignore();
                std::getline(std::wcin, wstr);
                client.setFullName(wstr);

                std::wcout << "Enter registry number: ";
                std::wcin.ignore();
                std::cin >> number;
                client.setRegistryNumber(number);

                std::wcout << "Enter address: ";
                std::wcin.ignore();
                std::getline(std::wcin, wstr);
                client.setAddress(wstr);

                std::wcout << "Enter gender: ";
                std::wcin.ignore();
                std::getline(std::wcin, wstr);

                client.setGender(wstr);

                std::wcout << "Enter phone: ";
                std::wcin.ignore();
                std::getline(std::wcin, wstr);

                client.setPhone(wstr);

                clients_instance.create(client);
                break;
            }
            case (5): {
                auto result = clients_instance.readAll();
                for (auto &item: result) {
                    std::wcout << item << std::endl;
                }

                break;
            }
            case (6): {
                auto result = employer_instance.readAll();
                for (auto &item: result) {
                    std::wcout << item << std::endl;
                }

                break;
            }
            case (7): {
                auto result = employer_instance.readAll();
                for (auto &item: result) {
                    std::wcout << item << std::endl;
                }

                break;
            }
            case (8): {
                auto result = employer_instance.readAll();
                for (auto &item: result) {
                    std::wcout << item << std::endl;
                }

                break;
            }
            case (9): {
                Employer employer;
                std::wstring wstr;
                int number;

                std::wcout << "Enter name: ";
                std::wcin.ignore();
                std::getline(std::wcin, wstr);
                employer.setName(wstr);

                std::wcout << "Enter ownership type: ";
                std::wcin.ignore();
                std::wcin >> wstr;
                employer.setOwnershipType(wstr);

                std::wcout << "Enter address: ";
                std::wcin.ignore();
                std::getline(std::wcin, wstr);
                employer.setAddress(wstr);

                std::wcout << "Enter phone: ";
                std::wcin.ignore();
                std::getline(std::wcin, wstr);
                employer.setPhone(wstr);


                std::wcout << "Enter contract number: ";
                std::wcin.ignore();
                std::cin >> number;
                employer.setContractNumber(number);

                employer_instance.create(employer);
                break;
            }
        }
    }

    return true;
}

int main(int argc, char **argv) {
    _setmode(_fileno(stdin), _O_U16TEXT);
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stderr), _O_U16TEXT);

    try {
        connection_data_s connection_data = {
                .username = "postgres",
                .password = "1111",
                .database = "lab1",
                .server = "localhost",
                .port = "5432",
                .driver = "{PostgreSQL UNICODE}",
        };

        auto executor = sql_executor(connection_data);

        auto clients_mapper_instance = ClientsMapper(&executor);
        auto employer_mapper_instance = EmployerMapper(&executor);

        menu(employer_mapper_instance, clients_mapper_instance);
    }
        /* Connection catch */
    catch (const std::exception &ex) {
        std::wcerr << ex.what() << std::endl;
    }

    return 0;
}
