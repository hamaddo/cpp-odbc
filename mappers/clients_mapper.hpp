#ifndef DATABASE_PROGRAMMING_1_CLIENTS_MAPPER_HPP
#define DATABASE_PROGRAMMING_1_CLIENTS_MAPPER_HPP

#include <vector>
#include "sql_executor.hpp"
#include "entities/clients.hpp"

class clients_mapper {
public:
    explicit clients_mapper(sql_executor *executor)
            : executor_(executor) {
        auto query =
                "create table if not exists clients\n"
                "(\n"
                "    id           serial primary key,\n"
                "\n"
                "    registry_number   integer not null,\n"
                "    full_name   varchar(255) not null,\n"
                "    address    varchar(255) not null,\n"
                "    gender   varchar(255) not null,\n"
                "    phone   varchar(255) not null\n"
                ")";

        SQLHSTMT statement = executor_->execute(query);
        auto retcode = SQLFetch(statement);
    };

    void create(Client &client_) {
        std::wstringstream query_builder;
        query_builder <<
                      "insert into clients(registry_number, full_name, address, gender, phone)" << std::endl
                      <<
                      "values" << std::endl << '(' <<
                      client_.getRegistryNumber() << ',' <<
                      '\'' << client_.getFullName() << '\'' << ',' <<
                      '\'' << client_.getAddress() << '\'' << ',' <<
                      '\'' << client_.getGender() << '\'' << ',' <<
                      '\'' << client_.getPhone() << '\'' <<
                      ')' << std::endl <<
                      "returning id";

        std::wcout << query_builder.str() << std::endl;

        SQLHSTMT statement = executor_->execute(query_builder.str());

        SQLINTEGER id;

        auto retcode = SQLBindCol(statement, 1, SQL_C_LONG, &id, 0, nullptr);

        retcode = SQLFetch(statement);


        std::wcout << id << std::endl;

        client_.setClientId(id);
    }

    std::vector<Client> read(int id_) {
        std::stringstream query_builder;

        query_builder <<
                      "select * from clients" << std::endl <<
                      "where id = " << id_;

        SQLHSTMT statement = executor_->execute(query_builder.str());

        return this->get_table(statement);
    }

    std::vector<Client> readAll() {
        SQLHSTMT statement = executor_->execute("select * from clients");

        return this->get_table(statement);
    }

    void update(const Client &client_) {
        if (!client_.getClientId().has_value()) {
            throw std::runtime_error("[clients_mapper]: record doesn't exists");
        }

        std::wstringstream query_builder;

        query_builder <<
                      "update clients" << std::endl <<
                      "set " <<
                      "where id = " << client_.getClientId().value() << std::endl <<
                      "returning *";

        SQLHSTMT statement = executor_->execute(query_builder.str());
    }

    void remove(int id_) {
        std::stringstream query_builder;

        query_builder <<
                      "delete from clients" << std::endl <<
                      "where id = " << id_ << std::endl <<
                      "returning *";

        SQLHSTMT statement = executor_->execute(query_builder.str());
    }

private:
    sql_executor *executor_;

    std::vector<Client> get_table(SQLHSTMT statement) {
        std::vector<Client> buff;

        SQLINTEGER id;
        SQLINTEGER registry_number;
        SQLWCHAR full_name[255];
        SQLWCHAR address[255];
        SQLWCHAR gender[255];
        SQLWCHAR phone[255];

        auto retcode = SQLBindCol(statement, 1, SQL_C_LONG, &id, 0, nullptr);
        retcode = SQLBindCol(statement, 2, SQL_C_LONG, &registry_number, 0, nullptr);
        retcode = SQLBindCol(statement, 3, SQL_C_WCHAR, &address, 255, nullptr);
        retcode = SQLBindCol(statement, 4, SQL_C_WCHAR, &full_name, 255, nullptr);
        retcode = SQLBindCol(statement, 5, SQL_C_WCHAR, &gender, 255, nullptr);
        retcode = SQLBindCol(statement, 6, SQL_C_LONG, &phone, 0, nullptr);


        while (true) {
            retcode = SQLFetch(statement);
            if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
                Client client;
                client.setClientId(id);
                client.setRegistryNumber(registry_number);
                client.setFullName(full_name);
                client.setAddress(address);
                client.setGender(gender);
                client.setPhone(phone);

                buff.push_back(client);
            } else {
                if (retcode == SQL_NO_DATA) {
                    break;
                }
            }

        }


        return buff;
    }
};

#endif //DATABASE_PROGRAMMING_1_CLIENTS_MAPPER_HPP
