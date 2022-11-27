#include <fcntl.h>
#include "sql_executor.hpp"
#include "mappers/employer_mapper.hpp"
#include "mappers/clients_mapper.hpp"


bool menu(EmployerMapper &employer_instance,
          ClientsMapper &clients_instance) {
    auto should_break = false;

    while (!should_break) {
        int choice;

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

        std::wcin >> choice;

        switch (choice) {
            case (0) : {
                should_break = true;
                break;
            }
            case (1): {
                auto result = clients_instance.readAll();
                for (auto i: result) {
                    std::wcout << i << std::endl;
                }

                break;
            }
            case (2): {
                int order;
                std::wcin >> order;
                auto result = clients_instance.read(order - 1);
                for (auto &i: result) {
                    std::wcout << i << std::endl;
                }
                break;
            }
            case (4): {
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

                clients_instance.create(client);
                break;
            }
            case (5): {
                auto result = clients_instance.readAll();
                for (auto item: result) {
                    std::wcout << item << std::endl;
                }

                break;
            }
            case (6): {
                auto result = employer_instance.readAll();
                for (auto item: result) {
                    std::wcout << item << std::endl;
                }

                break;
            }
            case (7): {
                auto result = employer_instance.readAll();
                for (auto item: result) {
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

                employer_instance.create(employer);
                break;
            }
            default: {
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
