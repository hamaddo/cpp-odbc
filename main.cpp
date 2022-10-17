#include <fcntl.h>
#include "sql_executor.hpp"
#include "mappers/client_mapper.hpp"
#include "mappers/deposit_mapper.hpp"
#include "mappers/clients_mapper.hpp"

bool menu(deposit_mapper &deposit_instance, client_mapper &client_instance,
          clients_mapper &clients_instance) {
    auto should_break = false;

    while (!should_break) {
        int choice = -1;

        std::wcout << L"--- Clients ---" << std::endl
                   << L"1. Показать всех клиентов" << std::endl
                   << L"2. Найти клиента по индентификатору" << std::endl
                   << L"3. Изменить данные клиента" << std::endl
                   << L"4. Создать клиента" << std::endl
                   << L"5. Удалить клиента" << std::endl << std::endl;

        std::wcout << L"--- Клиенты ---" << std::endl
                   << L"6. Показать всех клиентов" << std::endl
                   << L"7. Найти клиента по индентификатору" << std::endl
                   << L"8. Изменить данные клиента" << std::endl
                   << L"9. Создать клиента" << std::endl
                   << L"10. Удалить клиента" << std::endl << std::endl;

        std::wcout << L"--- Вклады ---" << std::endl
                   << L"11. Показать все вклады" << std::endl
                   << L"12. Найти вклад по индентификатору" << std::endl
                   << L"13. Изменить данные вклада" << std::endl
                   << L"14. Создать вклад" << std::endl
                   << L"15. Удалить вклад" << std::endl << std::endl;

        std::wcout << L"0. Выход";

        std::cin >> choice;


        switch (choice) {
            case (0) : {
                should_break = true;

                break;
            }
            case (1): {
                clients_instance.read();

                break;
            }
        }
    }

    return true;
}

int main(int argc, char **argv) {
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

        auto deposit_mapper_instance = deposit_mapper(&executor);
        auto client_mapper_instance = client_mapper(&executor);
        auto clients_mapper_instance = clients_mapper(&executor);

        menu(deposit_mapper_instance, client_mapper_instance, clients_mapper_instance);
    }
        /* Connection catch */
    catch (const std::exception &ex) {
        std::wcerr << ex.what() << std::endl;
    }

    return 0;
}
