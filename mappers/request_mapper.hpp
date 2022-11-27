#ifndef DATABASE_PROGRAMMING_1_REQUEST_MAPPER_HPP
#define DATABASE_PROGRAMMING_1_REQUEST_MAPPER_HPP

#include <vector>
#include <unordered_map>
#include "sql_executor.hpp"
#include "entities/request.hpp"

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

    void create(Request &request) {
        std::wstringstream query_builder;
        query_builder <<
                      "insert into requests(client_id, position_name, salary)" << std::endl
                      <<
                      "values" << std::endl << '(' <<
                      request.getClientId() << ',' <<
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
    }

    Request *read(int order, int client_id) {
        if (order > requests_map.size()) {
            throw std::runtime_error("[RequestsMapper]: out of bounds");
        }

        return requests_map[client_id][order];
    }

    std::vector<Request *> readAll(int client_id) {
        std::wstringstream query_builder;

        query_builder <<
                      "select * from requests"<< std::endl <<
                      "where client_id = " << client_id << std::endl;

        std::wcout << query_builder.str() << std::endl;

        SQLHSTMT statement = executor_->execute(query_builder.str());

        return this->get_table(statement);
    }

    void update(const Request &request_) {
        if (!request_.getId().value()) {
            throw std::runtime_error("[RequestsMapper]: record doesn't exists");
        }

        std::wstringstream query_builder;

        query_builder <<
                      "update requests" << std::endl <<
                      "set " <<
                      "where id = " << request_.getId().value() << std::endl <<
                      "returning *";

        SQLHSTMT statement = executor_->execute(query_builder.str());
    }

    std::vector<Request *> remove(int order, int client_id) {
        if (order > requests_map.size()) {
            throw std::runtime_error("[RequestsMapper]: out of bounds");
        }
        std::stringstream query_builder;

        query_builder <<
                      "delete from requests" << std::endl <<
                      "where id = " << requests_map[client_id][order]->getId().value() << std::endl <<
                      "returning id";

        SQLHSTMT statement = executor_->execute(query_builder.str());

        delete requests_map[client_id][order];
        requests_map[client_id].erase(requests_map[client_id].begin() + order);

        return this->readAll(client_id);
    }

private:
    sql_executor *executor_;
    std::unordered_map<int, std::vector<Request *>> requests_map;

    std::vector<Request *> get_table(SQLHSTMT statement) {
        SQLINTEGER id;
        SQLINTEGER client_id;
        SQLWCHAR position_name[255];
        SQLINTEGER salary;

        auto retcode = SQLBindCol(statement, 1, SQL_C_LONG, &id, 0, nullptr);
        retcode = SQLBindCol(statement, 2, SQL_C_LONG, &client_id, 0, nullptr);
        retcode = SQLBindCol(statement, 3, SQL_C_WCHAR, &position_name, 255, nullptr);
        retcode = SQLBindCol(statement, 4, SQL_C_LONG, &salary, 255, nullptr);


        while (true) {
            retcode = SQLFetch(statement);
            if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
                auto new_request = new Request();
                new_request->setId(id);
                new_request->setClientId(client_id);
                new_request->setPositionName(position_name);
                new_request->setSalary(salary);

                bool found = false;
                for (auto request: requests_map[client_id]) {
                    if (request->getId().value() == new_request->getId().value()) {
                        request->setId(id);
                        request->setClientId(client_id);
                        request->setPositionName(position_name);
                        request->setSalary(salary);
                        found = true;

                        break;
                    }
                }

                if (!found) {
                    requests_map[client_id].push_back(new_request);
                } else {
                    delete new_request;
                }
            } else {
                if (retcode == SQL_NO_DATA) {
                    break;
                }
            }
        }

        return requests_map[client_id];
    }
};

#endif //DATABASE_PROGRAMMING_1_REQUEST_MAPPER_HPP
