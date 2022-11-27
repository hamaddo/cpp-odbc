#include <fcntl.h>
#include "sql_executor.hpp"
#include "mappers/employer_mapper.hpp"
#include "mappers/clients_mapper.hpp"
#include "helpers/clients_helper.hpp"
#include "helpers/employer_helper.hpp"


bool menu(EmployerMapper &employer_instance,
          ClientsMapper &client_instance, RequestMapper &request_mapper_instance, OfferMapper &offer_mapper_instance) {
    auto should_break = false;

    auto client_helper = new ClientsHelper(client_instance, request_mapper_instance);
    auto employer_helper = new EmployerHelper(employer_instance, offer_mapper_instance);

    while (!should_break) {
        int choice;

        std::wcout << std::endl << L"--- Разделы ---" << std::endl
                   << L"1. Клиенты" << std::endl
                   << L"2. Работодатели" << std::endl << std::endl;

        std::wcout << L"0. Выход" << std::endl;

        std::wcin >> choice;

        switch (choice) {
            case (0) : {
                should_break = true;
                break;
            }
                // Клиенты
            case (1): {
                client_helper->start();
                break;
            }
                //Работодатели
            case (2): {
                employer_helper->start();
                break;

            }
            default: {
                break;
            }
        }
    }
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
        auto request_mapper_instance = RequestMapper(&executor);
        auto offer_mapper_instance = OfferMapper(&executor);

        menu(employer_mapper_instance, clients_mapper_instance, request_mapper_instance, offer_mapper_instance);
    }
        /* Connection catch */
    catch (const std::exception &ex) {
        std::wcerr << ex.what() << std::endl;
    }

    return 0;
}
