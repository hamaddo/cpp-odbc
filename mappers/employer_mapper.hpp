#ifndef DATABASE_PROGRAMMING_1_EMPLOYER_MAPPER_HPP
#define DATABASE_PROGRAMMING_1_EMPLOYER_MAPPER_HPP

#include <vector>
#include "sql_executor.hpp"
#include "entities/employers.hpp"

class EmployerMapper {
public:
    explicit EmployerMapper(sql_executor *executor)
            : executor_(executor) {
        auto query =
                "create table if not exists employers\n"
                "(\n"
                "    id         serial primary key,\n"
                "\n"
                "    name       varchar(255) not null,\n"
                "    ownership_type varchar(255) not null,\n"
                "    address   varchar(255) not null,\n"
                "    phone      varchar(255) not null,\n"
                "    contract_number      integer not null\n"
                ")";

        SQLHSTMT statement = executor_->execute(query);
        auto retcode = SQLFetch(statement);
    };

    void create(Employer &employer_) {
        std::wstringstream query_builder;

        query_builder <<
                      "insert into employers(name, ownership_type, address, phone, contract_number)" << std::endl <<
                      "values" << std::endl << '(' <<
                      '\'' << employer_.getName() << '\'' << ',' <<
                      '\'' << employer_.getOwnershipType() << '\'' << ',' <<
                      '\'' << employer_.getAddress() << '\'' << ',' <<
                      '\'' << employer_.getPhone() << '\'' << ',' <<
                      '\'' << employer_.getContractNumber() << '\'' <<
                      ')' << std::endl <<
                      "returning id";

        SQLHSTMT statement = executor_->execute(query_builder.str());

        SQLINTEGER id;

        auto retcode = SQLBindCol(statement, 1, SQL_C_LONG, &id, 0, nullptr);

        retcode = SQLFetch(statement);
        employer_.setId(id);
    }

    std::vector<Employer*> read(int id_) {
        std::stringstream query_builder;

        query_builder <<
                      "select * from employers" << std::endl <<
                      "where id = " << id_;

        SQLHSTMT statement = executor_->execute(query_builder.str());

        return this->get_table(statement);
    }

    std::vector<Employer*> readAll() {
        SQLHSTMT statement = executor_->execute("select * from clients");

        return this->get_table(statement);
    }

    void update(Employer &employer_) {
        if (!employer_.getId().has_value()) {
            throw std::runtime_error("[EmployerMapper]: record doesn't exists");
        }

        std::wstringstream query_builder;

        query_builder <<
                      "update employers" << std::endl <<
                      "set " <<
                      "name=" << '\'' << employer_.getName() << '\'' << ',' <<
                      "ownership_type=" << '\'' << employer_.getOwnershipType() << '\'' << ',' <<
                      "address=" << '\'' << employer_.getAddress() << '\'' << ',' <<
                      "phone=" << '\'' << employer_.getPhone() << '\'' << ',' <<
                      "contract_number=" << '\'' << employer_.getContractNumber() << '\'' << std::endl <<
                      "where id = " << employer_.getId().value() << std::endl <<
                      "returning *";

        SQLHSTMT statement = executor_->execute(query_builder.str());
    }

    void remove(int id_) {
        std::stringstream query_builder;

        query_builder <<
                      "delete from employers" << std::endl <<
                      "where id = " << id_ << std::endl <<
                      "returning *";
        SQLHSTMT statement = executor_->execute(query_builder.str());
    }

private:
    sql_executor *executor_;
    std::vector<Employer *> employers_;

    std::vector<Employer *> get_table(SQLHSTMT statement) {
        SQLINTEGER id;
        SQLWCHAR name[255];
        SQLWCHAR ownership_type[255];
        SQLWCHAR address[255];
        SQLWCHAR phone[255];
        SQLINTEGER contract_number;

        auto retcode = SQLBindCol(statement, 1, SQL_C_LONG, &id, 0, nullptr);
        retcode = SQLBindCol(statement, 2, SQL_C_WCHAR, &name, 255, nullptr);
        retcode = SQLBindCol(statement, 3, SQL_C_WCHAR, &ownership_type, 255, nullptr);
        retcode = SQLBindCol(statement, 4, SQL_C_WCHAR, &address, 255, nullptr);
        retcode = SQLBindCol(statement, 5, SQL_C_WCHAR, &phone, 255, nullptr);
        retcode = SQLBindCol(statement, 6, SQL_C_LONG, &contract_number, 255, nullptr);

        retcode = SQLFetch(statement);

        std::vector<Employer> buff = {};

        while (true) {
            retcode = SQLFetch(statement);
            if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
                auto new_employer = new Employer();

                new_employer->setId(id);
                new_employer->setName(name);
                new_employer->setOwnershipType(ownership_type);
                new_employer->setAddress(address);
                new_employer->setPhone(phone);
                new_employer->setContractNumber(contract_number);

                bool found = false;
                for (auto employer_: employers_) {
                    if (employer_->getId().value() == new_employer->getId().value()) {
                        employer_->setId(id);
                        employer_->setName(name);
                        employer_->setOwnershipType(ownership_type);
                        employer_->setAddress(address);
                        employer_->setPhone(phone);
                        employer_->setContractNumber(contract_number);
                        found = true;

                        break;
                    }
                }

                if (!found) {
                    employers_.push_back(new_employer);
                } else {
                    delete new_employer;
                }
            } else {
                if (retcode == SQL_NO_DATA) {
                    break;
                }
            }
        }

        return employers_;
    }
};

#endif //DATABASE_PROGRAMMING_1_EMPLOYER_MAPPER_HPP
