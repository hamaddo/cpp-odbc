#ifndef DATABASE_PROGRAMMING_1_REQUEST_MAPPER_HPP
#define DATABASE_PROGRAMMING_1_REQUEST_MAPPER_HPP

#include <vector>
#include <unordered_map>
#include "sql_executor.hpp"
#include "entities/clients.hpp"

class RequestMapper {
public:
    explicit RequestMapper(sql_executor *executor)
            : executor_(executor) {
        auto query =
                "create table if not exists requests\n"
                "(\n"
                "    id           serial primary key,\n"
                "\n"
                "    client_id           integer not null,\n"
                "\n"
                "    position_name   varchar(255) not null,\n"
                "    salary    integer not null,\n"
                "\n"
                "    constraint fk_client_id\n"
                "        foreign key (client_id)\n"
                "            references clients (id)\n"
                "            on delete cascade\n"
                ")";

        SQLHSTMT statement = executor_->execute(query);
        auto retcode = SQLFetch(statement);
    };

    void create(Request &request, int client_id) {
        std::wstringstream query_builder;
        query_builder <<
                      "insert into requests(client_id, position_name, salary)" << std::endl
                      <<
                      "values" << std::endl << '(' <<
                      client_id << ',' <<
                      '\'' << request.getPositionName() << '\'' << ',' <<
                      request.getSalary() <<
                      ')' << std::endl <<
                      "returning id";

        std::wcout << query_builder.str() << std::endl;

        SQLHSTMT statement = executor_->execute(query_builder.str());

        SQLINTEGER id;

        auto retcode = SQLBindCol(statement, 1, SQL_C_LONG, &id, 0, nullptr);

        retcode = SQLFetch(statement);

        request.setId(id);
        request.setClientId(id);
    }

    Client *read(int order, int client_id) {
        if (order > requests_.size()) {
            throw std::runtime_error("[ClientsMapper]: out of bounds");
        }

        return requests_[client_id][order];
    }

    std::vector<Client *> readAll(int client_id) {
        SQLHSTMT statement = executor_->execute("select * from clients");

        return this->get_table(statement, client_id);
    }

    void update(const Client &client_) {
        if (!client_.getClientId().has_value()) {
            throw std::runtime_error("[ClientsMapper]: record doesn't exists");
        }

        std::wstringstream query_builder;

        query_builder <<
                      "update clients" << std::endl <<
                      "set " <<
                      "where id = " << client_.getClientId().value() << std::endl <<
                      "returning *";

        SQLHSTMT statement = executor_->execute(query_builder.str());
    }

    std::vector<Client *> remove(int order, int client_id) {
        if (order > requests_.size()) {
            throw std::runtime_error("[ClientsMapper]: out of bounds");
        }
        std::stringstream query_builder;

        query_builder <<
                      "delete from clients" << std::endl <<
                      "where id = " << requests_[client_id][order]->getClientId().value() << std::endl <<
                      "returning id";

        SQLHSTMT statement = executor_->execute(query_builder.str());

        delete requests_[client_id][order];
        requests_[client_id].erase(requests_[client_id].begin() + order);

        return this->readAll(client_id);
    }

private:
    sql_executor *executor_;
    std::unordered_map<int, std::vector<Client *>> requests_;

    std::vector<Client *> get_table(SQLHSTMT statement, int client_id) {
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
                auto new_client = new Client();
                new_client->setClientId(id);
                new_client->setRegistryNumber(registry_number);
                new_client->setFullName(full_name);
                new_client->setAddress(address);
                new_client->setGender(gender);
                new_client->setPhone(phone);

                bool found = false;
                for (auto client_: requests_[client_id]) {
                    if (client_->getClientId().value() == new_client->getClientId().value()) {
                        client_->setClientId(id);
                        client_->setRegistryNumber(registry_number);
                        client_->setFullName(full_name);
                        client_->setAddress(address);
                        client_->setGender(gender);
                        client_->setPhone(phone);
                        found = true;

                        break;
                    }
                }

                if (!found) {
                    requests_[client_id].push_back(new_client);
                } else {
                    delete new_client;
                }
            } else {
                if (retcode == SQL_NO_DATA) {
                    break;
                }
            }
        }

        return requests_[client_id];
    }
};

#endif //DATABASE_PROGRAMMING_1_REQUEST_MAPPER_HPP
