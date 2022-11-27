#ifndef DATABASE_PROGRAMMING_1_ABSTRACT_HELPER_HPP
#define DATABASE_PROGRAMMING_1_ABSTRACT_HELPER_HPP


#include <iostream>

class AbstractHelper {
public:
    virtual void print() = 0;

    virtual void read() = 0;

    virtual void create() = 0;

    virtual void update() = 0;

    virtual void remove() = 0;

    virtual void printActions() = 0;

    void start() {
        auto should_break = false;

        while (!should_break) {
            int choice;

            printActions();
            std::wcin >> choice;

            switch (choice) {
                case (0) : {
                    should_break = true;
                    break;
                }
                case 1:
                    print();
                    break;
                case 2:
                    read();
                    break;
                case 3:
                    create();
                    break;
                case 4:
                    update();
                    break;
                case 5:
                    remove();
                    break;
                default:
                    std::cout << "Back to main menu..." << std::endl;
                    break;
            }
        }
    }
};


#endif //DATABASE_PROGRAMMING_1_ABSTRACT_HELPER_HPP
