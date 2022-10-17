#ifndef DATABASE_PROGRAMMING_1_CLIENTS_MAPPER_HPP
#define DATABASE_PROGRAMMING_1_CLIENTS_MAPPER_HPP

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
                "    receipt_number   integer not null\n"
                ")";

        SQLHSTMT statement = executor_->execute(query);
        auto retcode = SQLFetch(statement);
    };

    clients create(const clients &client_) {
        std::wstringstream query_builder;

        query_builder <<
                      "insert into accounts(registry_number, full_name, address, gender, receipt_number)" << std::endl
                      <<
                      "values" << std::endl << '(' <<
                      '\'' << client_.full_name << '\'' << ',' <<
                      client_.registry_number << ',' <<
                      '\'' << client_.address << '\'' << ',' <<
                      '\'' << client_.gender << '\'' << ',' <<
                      client_.receipt_number <<
                      ')' << std::endl <<
                      "returning id";

        SQLHSTMT statement = executor_->execute(query_builder.str());

        SQLINTEGER id;

        auto retcode = SQLBindCol(statement, 1, SQL_C_LONG, &id, 0, nullptr);

        retcode = SQLFetch(statement);

        auto new_account = client_;
        new_account.id = id;
        return new_account;
    }

    clients read() {
        SQLHSTMT statement = executor_->execute("select * from accounts");

        return this->get_table(statement);
    }

    clients read(int id_) {
        std::stringstream query_builder;

        query_builder <<
                      "select * from accounts" << std::endl <<
                      "where id = " << id_;

        SQLHSTMT statement = executor_->execute(query_builder.str());

        return this->get_table(statement);
    }

    clients update(const clients &client_) {
        if (!client_.id.has_value()) {
            throw std::runtime_error("[clients_mapper]: record doesn't exists");
        }

        std::wstringstream query_builder;

        query_builder <<
                      "update accounts" << std::endl <<
                      "set " <<
                      "where id = " << client_.id.value() << std::endl <<
                      "returning *";

        SQLHSTMT statement = executor_->execute(query_builder.str());


        return this->get_table(statement);
    }

    clients remove(int id_) {
        std::stringstream query_builder;

        query_builder <<
                      "delete from accounts" << std::endl <<
                      "where id = " << id_ << std::endl <<
                      "returning *";

        SQLHSTMT statement = executor_->execute(query_builder.str());

        return this->get_table(statement);
    }

private:
    sql_executor *executor_;

    clients get_table(SQLHSTMT statement) {
        SQLINTEGER id;
        SQLINTEGER registry_number;
        SQLWCHAR full_name[255];
        SQLWCHAR address[255];
        SQLWCHAR gender[255];

        SQLINTEGER receipt_number;

        auto retcode = SQLBindCol(statement, 1, SQL_C_LONG, &id, 0, nullptr);
        retcode = SQLBindCol(statement, 2, SQL_C_LONG, &registry_number, 0, nullptr);
        retcode = SQLBindCol(statement, 3, SQL_C_WCHAR, &address, 255, nullptr);
        retcode = SQLBindCol(statement, 4, SQL_C_WCHAR, &full_name, 255, nullptr);
        retcode = SQLBindCol(statement, 5, SQL_C_WCHAR, &gender, 255, nullptr);
        retcode = SQLBindCol(statement, 6, SQL_C_LONG, &receipt_number, 0, nullptr);

        retcode = SQLFetch(statement);

        clients fetched = {
                .id = id,
                .registry_number = registry_number,
                .full_name = full_name,
                .address = address,
                .gender = gender,
                .receipt_number = receipt_number,
        };

        return fetched;
    }
};

#endif //DATABASE_PROGRAMMING_1_CLIENTS_MAPPER_HPP
