#ifndef DATABASE_PROGRAMMING_1_OFFER_HELPER_HPP
#define DATABASE_PROGRAMMING_1_OFFER_HELPER_HPP



#include "abstract_helper.hpp"
#include "mappers/offer_mapper.hpp"

class OfferHelper: public AbstractHelper{
private:
    OfferMapper &mapper_instance;
    int employer_id;
public:
    explicit OfferHelper(OfferMapper &mapper_instance_) : mapper_instance(mapper_instance_) {

    }

    void setEmployerId(int employer_id_) {
        employer_id = employer_id_;
    }

    void printActions() override {
        std::wcout << std::endl << L"--- Предложения(ваканси) работодателя ---" << std::endl
                   << L"1. Показать все предложения" << std::endl
                   << L"2. Найти предложение по порядковому номеру" << std::endl
                   << L"3. Изменить данные предложения" << std::endl
                   << L"4. Создать предложение" << std::endl
                   << L"5. Удалить предложение" << std::endl << std::endl;

        std::wcout << L"0. Выход" << std::endl;
    }

    void print() override {
        auto result = mapper_instance.readAll(employer_id);
        int order = 1;
        for (auto i: result) {
            std::wcout << order++ << L". " << i << std::endl;
        }
    }

    void read() override {
        int order;
        std::wcin >> order;
        auto result = mapper_instance.read(order - 1, employer_id);
        std::wcout << result << std::endl;
    }

    void create() override {
        Offer request;
        std::wstring name;
        std::wstring gender;
        int number;

        std::wcout << "Enter position name: ";
        std::getline(std::wcin >> std::ws, name);
        request.setPositionName(name);

        std::wcout << "Enter salary: ";
        std::wcin >> number;
        request.setSalary(number);

        std::wcout << "Enter gender: ";
        std::getline(std::wcin >> std::ws, gender);
        request.setGender(gender);

        request.setEmployerId(employer_id);

        mapper_instance.create(request);
    }

    void remove() override {
        int order;
        std::wcin >> order;

        auto result = mapper_instance.remove(order - 1, employer_id);

        int position = 1;
        for (auto i: result) {
            std::wcout << position++ << L". " << i << std::endl;
        }

    }

    void update() override {
    }

    void goToChild() override {

    }
};



#endif //DATABASE_PROGRAMMING_1_OFFER_HELPER_HPP
