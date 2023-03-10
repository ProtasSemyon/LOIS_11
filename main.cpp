//////////////////////////////////////////////////////////////////////////////////////
// Лабораторная работа 1 по дисциплине ЛОИС
// Выполнена студентом группы 021701
// БГУИР Протас С.А.
// Вариант D - Проверить, является ли формула СДНФ
// 26.02.2023

#include "src/Validator.hpp"
#include "src/Parser.hpp"
#include <iostream>
#include <limits>
#include <stdexcept>



int main() {
    while (true) {
        std::cout << "1. Check formula\n2. Exit program\n";
        std::string option;
        std::cin >> option;
        std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
        if (option == "2") {
            break;
        }
        if (option != "1") {
            continue;
        }
        
        std::cout << "Enter formula\n";
        std::string formula;
        std::getline(std::cin, formula);
        LogicFormulaPtr logicFormula;
        try {
            logicFormula = Parser::parse(formula);
        } catch (const std::invalid_argument& e) {
            std::cout << e.what() << std::endl;
            continue;
        }

        if (Validator::isPDNF(logicFormula)) {
            std::cout << "Formula is PDNF\n";
        } else {
            std::cout << "Formula isn't PDNF\n";
        }
    }

    return 0;
}