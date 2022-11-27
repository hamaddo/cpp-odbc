#ifndef DATABASE_PROGRAMMING_1_OFFER_MAPPER_HPP
#define DATABASE_PROGRAMMING_1_OFFER_MAPPER_HPP

#include <vector>
#include <unordered_map>
#include "sql_executor.hpp"
#include "entities/offer.hpp"

class OfferMapper {
public:
    explicit OfferMapper(sql_executor *executor)
            : executor_(executor) {
        auto query =
                "create table if not exists offers\n"
                "(\n"
                "    id           serial primary key,\n"
                "\n"
                "    employer_id           integer not null,\n"
                "\n"
                "    position_name   varchar(255) not null,\n"
                "    salary    integer not null,\n"
                "    gender   varchar(255) not null,\n"
                "\n"
                "    constraint fk_employer_id\n"
                "        foreign key (employer_id)\n"
                "            references employers(id)\n"
                "            on delete cascade\n"
                ")";

        SQLHSTMT statement = executor_->execute(query);
        auto retcode = SQLFetch(statement);
    };

    void create(Offer &offer) {
        std::wstringstream query_builder;
        query_builder <<
                      "insert into offers(employer_id, position_name, salary, gender)" << std::endl
                      <<
                      "values" << std::endl << '(' <<
                      offer.getEmployerId() << ',' <<
                      '\'' << offer.getPositionName() << '\'' << ',' <<
                      offer.getSalary() << ',' <<
                      '\'' << offer.getGender() << '\'' <<
                      ')' << std::endl <<
                      "returning id";

        std::wcout << query_builder.str() << std::endl;

        SQLHSTMT statement = executor_->execute(query_builder.str());

        SQLINTEGER id;

        auto retcode = SQLBindCol(statement, 1, SQL_C_LONG, &id, 0, nullptr);

        retcode = SQLFetch(statement);

        offer.setId(id);
    }

    Offer *read(int order, int employer_id) {
        if (order > offers_map.size()) {
            throw std::runtime_error("[OfferMapper]: out of bounds");
        }

        return offers_map[employer_id][order];
    }

    std::vector<Offer *> readAll(int employer_id) {
        std::wstringstream query_builder;

        query_builder <<
                      "select * from offers" << std::endl <<
                      "where employer_id = " << employer_id << std::endl;

        std::wcout << query_builder.str() << std::endl;

        SQLHSTMT statement = executor_->execute(query_builder.str());

        return this->get_table(statement);
    }

    void update(const Offer &offer) {
        if (!offer.getId().value()) {
            throw std::runtime_error("[OfferMapper]: record doesn't exists");
        }

        std::wstringstream query_builder;

        query_builder <<
                      "update offers" << std::endl <<
                      "set " <<
                      "where id = " << offer.getId().value() << std::endl <<
                      "returning *";

        SQLHSTMT statement = executor_->execute(query_builder.str());
    }

    std::vector<Offer *> remove(int order, int employer_id) {
        if (order > offers_map.size()) {
            throw std::runtime_error("[OfferMapper]: out of bounds");
        }
        std::stringstream query_builder;

        query_builder <<
                      "delete from offers" << std::endl <<
                      "where id = " << offers_map[employer_id][order]->getId().value() << std::endl <<
                      "returning id";

        SQLHSTMT statement = executor_->execute(query_builder.str());

        delete offers_map[employer_id][order];
        offers_map[employer_id].erase(offers_map[employer_id].begin() + order);

        return this->readAll(employer_id);
    }

private:
    sql_executor *executor_;
    std::unordered_map<int, std::vector<Offer *>> offers_map;

    std::vector<Offer *> get_table(SQLHSTMT statement) {
        SQLINTEGER id;
        SQLINTEGER employer_id;
        SQLWCHAR position_name[255];
        SQLINTEGER salary;
        SQLWCHAR gender[255];

        auto retcode = SQLBindCol(statement, 1, SQL_C_LONG, &id, 0, nullptr);
        retcode = SQLBindCol(statement, 2, SQL_C_LONG, &employer_id, 0, nullptr);
        retcode = SQLBindCol(statement, 3, SQL_C_WCHAR, &position_name, 255, nullptr);
        retcode = SQLBindCol(statement, 4, SQL_C_LONG, &salary, 255, nullptr);
        retcode = SQLBindCol(statement, 5, SQL_C_WCHAR, &gender, 255, nullptr);



        while (true) {
            retcode = SQLFetch(statement);
            if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
                auto new_offer = new Offer();
                new_offer->setId(id);
                new_offer->setEmployerId(employer_id);
                new_offer->setPositionName(position_name);
                new_offer->setSalary(salary);
                new_offer->setGender(gender);

                bool found = false;
                for (auto offer: offers_map[employer_id]) {
                    if (offer->getId().value() == new_offer->getId().value()) {
                        offer->setId(id);
                        offer->setEmployerId(employer_id);
                        offer->setPositionName(position_name);
                        offer->setSalary(salary);
                        new_offer->setGender(gender);

                        found = true;

                        break;
                    }
                }

                if (!found) {
                    offers_map[employer_id].push_back(new_offer);
                } else {
                    delete new_offer;
                }
            } else {
                if (retcode == SQL_NO_DATA) {
                    break;
                }
            }
        }

        return offers_map[employer_id];
    }
};


#endif //DATABASE_PROGRAMMING_1_OFFER_MAPPER_HPP
