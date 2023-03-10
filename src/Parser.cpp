#include "Parser.hpp"
#include "LogicFormula.hpp"

#include <memory>
#include <stdexcept>
#include <string>

const char TRUE = '1';
const char FALSE = '0';

const std::string CONJUNCTION = "/\\";
const std::string DISJUNCTION = "\\/";
const std::string IMPLICATION = "->";
const std::string EQUIVALENT = "~";
const char NEGATION = '!';

bool skipBraces(const std::string& str, size_t &position) {
    int lBr = 0;
    int rBr = 0;

    if (str.size() > position && str[position] == '(') {
        lBr++;
        position++;
    } else {
        return false;
    }

    while (lBr > rBr && position < str.size()) {
        switch(str[position]) {
        case '(':
            lBr++;
            break;
        case ')':
            rBr++;
            break;
        }
        position++;
    }

    return lBr == rBr;
}   


LogicFormulaPtr Parser::parse(const std::string& str) {
    if (str.size() == 1) {
        if (str[0] == TRUE || str[0] == FALSE) {
            return std::make_shared<LogicConstant>(str[0]);
        }
        if (str[0] >= 'A' && str[0] <= 'Z') {
            return std::make_shared<AtomicFormula>(str[0]);
        }

        throw std::invalid_argument("Invalid input: " + str);
    }

    size_t v = 0;
    if(!skipBraces(str, v) || v < str.size()) {
        throw std::invalid_argument("Invalid input: " + str);  
    }

    if (const auto formula = parseUnary(str.substr(1, str.size() - 2))) {
        return formula;
    }

    if (const auto formula = parseBinary(str.substr(1, str.size() - 2))) {
        return formula;
    }

    throw std::invalid_argument("Invalid input: " + str);
}

LogicFormulaPtr Parser::parseBinary(const std::string& str) {
    if (const auto formula = parseBinary<ConjunctionF>(str, CONJUNCTION)) {
        return formula;
    }
    if (const auto formula = parseBinary<DisjunctionF>(str, DISJUNCTION)) {
        return formula;
    }
    if (const auto formula = parseBinary<ImplicationF>(str, IMPLICATION)) {
        return formula;
    }
    if (const auto formula = parseBinary<EquivalentionF>(str, EQUIVALENT)) {
        return formula;
    }
    return nullptr;
}

LogicFormulaPtr Parser::parseUnary(const std::string& str) {
    return parseNegation(str);
}

LogicFormulaPtr Parser::parseNegation(const std::string& str) {
    if(str.empty() || str[0] != NEGATION) {
        return nullptr;
    }

    auto rhs = parse(str.substr(1));

    return std::make_shared<NegationF>(rhs);
}

