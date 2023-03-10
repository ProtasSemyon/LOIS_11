#pragma once

#include <memory>
#include <string>
#include <vector>

enum Types {
    Conjunction,
    Disjunction,
    Implication,
    Equivalention,
    Negation,
    Atomic,
    Constant
};

class LogicFormula;
using LogicFormulaPtr = std::shared_ptr<LogicFormula>;


class LogicFormula {
public:
    virtual Types getType() const = 0;
    virtual std::string toString() const = 0;
    virtual std::vector<LogicFormulaPtr> getChildren() const {
        return {};
    }
};

class BinaryFormula : public LogicFormula {
public:
    BinaryFormula(const LogicFormulaPtr &left, const LogicFormulaPtr &right) : leftF(left), rightF(right) {}
    std::string toString() const final{
        return "(" + leftF->toString() + getSign() + rightF->toString() + ")";
    }
    std::vector<LogicFormulaPtr> getChildren() const override {
        return {leftF, rightF};
    }

private:
    LogicFormulaPtr leftF;
    LogicFormulaPtr rightF;

    virtual std::string getSign() const = 0;
};

class ConjunctionF : public BinaryFormula {
public:
    ConjunctionF(const LogicFormulaPtr &left, const LogicFormulaPtr &right) : BinaryFormula(left, right) {}
    Types getType() const override {
        return Types::Conjunction;
    }
private:
    std::string getSign() const override{
        return "/\\";
    }
};

class DisjunctionF : public BinaryFormula {
public:
    DisjunctionF(const LogicFormulaPtr &left, const LogicFormulaPtr &right) : BinaryFormula(left, right) {}
    Types getType() const override {
        return Types::Disjunction;
    }
private:
    std::string getSign() const override{
        return "\\/";
    }
};

class ImplicationF : public BinaryFormula { 
public:
    ImplicationF(const LogicFormulaPtr &left, const LogicFormulaPtr &right) : BinaryFormula(left, right) {}
    Types getType() const override {
        return Types::Implication;
    }
private:
    std::string getSign() const override{
        return "->";
    }
};

class EquivalentionF : public BinaryFormula {
public:
    EquivalentionF(const LogicFormulaPtr &left, const LogicFormulaPtr &right) : BinaryFormula(left, right) {}
    Types getType() const override {
        return Types::Equivalention;
    }
private:
    std::string getSign() const override{
        return "~";
    }
};

class UnaryFormula : public LogicFormula { 
public:
    UnaryFormula(const LogicFormulaPtr &child) : child(child) {}
    std::string toString() const override { 
        return  "(" + getSign() + child->toString() + ")";
    }
    std::vector<LogicFormulaPtr> getChildren() const override {
        return {child};
    }

private:
    LogicFormulaPtr child;

    virtual std::string getSign() const = 0;
};

class NegationF : public UnaryFormula {
public:
    NegationF(const LogicFormulaPtr &child) : UnaryFormula(child) {}
    Types getType() const override {
        return Types::Negation;
    }
private:
    std::string getSign() const override{
        return "!";
    }
};

class AtomicFormula : public LogicFormula { 
public:
    AtomicFormula(char value) : value(value) {}
    Types getType() const override {
        return Types::Atomic;
    }
    std::string toString() const override {
        return {value};
    }
private:
    char value;
};

class LogicConstant : public LogicFormula {
public:
    LogicConstant(char value) : value(value) {}
    Types getType() const override {
        return Types::Constant;
    }
    std::string toString() const override {
        return {value};
    }
private:
    char value;
};