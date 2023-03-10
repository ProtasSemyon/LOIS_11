#pragma once

#include "LogicFormula.hpp"

class Parser {
public:
    static LogicFormulaPtr parse(const std::string& str);
private:
    static LogicFormulaPtr parseFormula(const std::string& str);

    template <typename ParsedClass>
    static LogicFormulaPtr parseBinary(const std::string& str, const std::string& separator);

    static LogicFormulaPtr parseBinary(const std::string& str);
    
    static LogicFormulaPtr parseUnary(const std::string& str);

    static LogicFormulaPtr parseNegation(const std::string& str);

};

bool skipBraces(const std::string& str, size_t &position);

template <typename ParsedClass>
LogicFormulaPtr Parser::parseBinary(const std::string& str, const std::string& separator) {
    size_t position = 0;
    if (!skipBraces(str, position)){
        position++;
    }
    if (str.find(separator, position) != position) {
        return nullptr;
    }

    auto lhs = parse(str.substr(0, position));
    auto rhs = parse(str.substr(position + separator.size()));

    return std::make_shared<ParsedClass>(lhs, rhs);
}