#ifndef DATABASE_PROGRAMMING_1_EMPLOYER_MAPPER_HPP
#define DATABASE_PROGRAMMING_1_EMPLOYER_MAPPER_HPP

#include "sql_executor.hpp"
#include "entities/employers.hpp"

class employer_mapper {
public:
    explicit employer_mapper(sql_executor *executor)
            : executor_(executor) {
        auto query =
                "create table if not exists employers\n"
                "(\n"
                "    id         serial primary key,\n"
                "\n"
                "    company_name       varchar(255) not null,\n"
                "    olf    varchar(255) not null,\n"
                "    ownership_type varchar(255) not null,\n"
                "    address   varchar(255) not null,\n"
                "    phone      varchar(255) not null,\n"
                "    personnel_inspector_fullname   varchar(255) not null\n"
                ")";

        SQLHSTMT statement = executor_->execute(query);
        auto retcode = SQLFetch(statement);
    };

    employers create(const employers &client_) {
        std::wstringstream query_builder;

        query_builder <<
                      "insert into employers(name, surname, patronymic, passport, address, phone)" << std::endl <<
                      "values" << std::endl << '(' <<
                      '\'' << client_.address << '\'' << ',' <<
                      '\'' << client_.phone << '\'' <<
                      ')' << std::endl <<
                      "returning id";

        SQLHSTMT statement = executor_->execute(query_builder.str());

        SQLINTEGER id;

        auto retcode = SQLBindCol(statement, 1, SQL_C_LONG, &id, 0, nullptr);

        retcode = SQLFetch(statement);

        auto new_client = client_;
        new_client.id = id;
        return new_client;
    }

    employers read(int id_) {
        std::stringstream query_builder;

        query_builder <<
                      "select * from employers" << std::endl <<
                      "where id = " << id_;

        SQLHSTMT statement = executor_->execute(query_builder.str());

        return this->get_table(statement);
    }

    employers update(const employers &client_) {
        if (!client_.id.has_value()) {
            throw std::runtime_error("[employer_mapper]: record doesn't exists");
        }

        std::wstringstream query_builder;

        query_builder <<
                      "update employers" << std::endl <<
                      "set " <<
                      "address=" << '\'' << client_.address << '\'' << ',' <<
                      "phone=" << '\'' << client_.phone << '\'' << std::endl <<
                      "where id = " << client_.id.value() << std::endl <<
                      "returning *";

        SQLHSTMT statement = executor_->execute(query_builder.str());

        return this->get_table(statement);
    }

    employers remove(int id_) {
        std::stringstream query_builder;

        query_builder <<
                      "delete from employers" << std::endl <<
                      "where id = " << id_ << std::endl <<
                      "returning *";

        SQLHSTMT statement = executor_->execute(query_builder.str());
        return this->get_table(statement);
    }

private:
    sql_executor *executor_;

    employers get_table(SQLHSTMT statement) {
        SQLINTEGER id;
        SQLWCHAR company_name[255];
        SQLWCHAR olf[255];
        SQLWCHAR ownership_type[255];
        SQLWCHAR address[255];
        SQLWCHAR phone[255];
        SQLWCHAR personnel_inspector_fullname[255];

        auto retcode = SQLBindCol(statement, 1, SQL_C_LONG, &id, 0, nullptr);
        retcode = SQLBindCol(statement, 2, SQL_C_WCHAR, &company_name, 255, nullptr);
        retcode = SQLBindCol(statement, 3, SQL_C_WCHAR, &olf, 255, nullptr);
        retcode = SQLBindCol(statement, 4, SQL_C_WCHAR, &ownership_type, 255, nullptr);
        retcode = SQLBindCol(statement, 5, SQL_C_WCHAR, &address, 255, nullptr);
        retcode = SQLBindCol(statement, 6, SQL_C_WCHAR, &phone, 255, nullptr);
        retcode = SQLBindCol(statement, 7, SQL_C_WCHAR, &phone, 255, nullptr);

        retcode = SQLFetch(statement);

        employers fetched = {
                .id = id,
                .company_name = company_name,
                .olf = olf,
                .ownership_type = ownership_type,
                .address = address,
                .phone = phone,
                .personnel_inspector_fullname = personnel_inspector_fullname,
        };

        return fetched;

    }
};

#endif //DATABASE_PROGRAMMING_1_EMPLOYER_MAPPER_HPP
