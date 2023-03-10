#include "Validator.hpp"
#include "LogicFormula.hpp"
#include <stdexcept>
#include <iostream>

bool Validator::isPDNF(const LogicFormulaPtr &formula) {
    if (formula->getType() == Types::Atomic) {
        return true;
    }
    if (formula->getType() == Types::Negation && formula->getChildren()[0]->getType() == Types::Atomic) {
        return true;
    }
    if (formula->getType() != Types::Disjunction && formula->getType() != Types::Conjunction) {
        return false;
    }

    std::vector<LogicFormulaPtr> conjunctionVector;
    try {
        conjunctionVector = getConjunctions(formula);
    } catch (const std::invalid_argument& e) {
        return false;
    }
    
    std::vector<AtomicVector> conjunctionAtomics;

    for (const auto& form : conjunctionVector) {
        try {
            conjunctionAtomics.emplace_back(getAtomic(form));
        } catch (const std::invalid_argument& e) {
            return false;
        }
    }

    for (size_t i = 0;i < conjunctionAtomics.size(); i++) {
        for (size_t j = 0;j < conjunctionAtomics.size(); j++) {
            if (i == j) {
                continue;
            }

            bool compareResult;
            try{
                compareResult = compareAtomics(conjunctionAtomics[i], conjunctionAtomics[j]);
            } catch (const std::invalid_argument& e){
                return false;
            }
            if (compareResult) {
                return false;
            }
        }
    }

    return true;
}


std::vector<LogicFormulaPtr> Validator::getConjunctions(const LogicFormulaPtr &formula) {
    if (formula->getType() == Types::Conjunction) {
        return {formula};
    }

    if (formula->getType() == Types::Disjunction) {
        std::vector<LogicFormulaPtr> result;
        for (auto& child : formula->getChildren()) {
            for (auto& form : getConjunctions(child)) {
                result.emplace_back(form);
            }
        }
        return result;
    }

    if (formula->getType() == Types::Negation || formula->getType() == Types::Atomic) {
        return {formula};
    }

    throw std::invalid_argument("It's not a PDNF formula");
}

bool Validator::checkRepeat(const Validator::AtomicVector &vect) {
    for (size_t i = 0;i < vect.size(); i++) {
        for (size_t j = 0;j < vect.size(); j++) {
            if (i == j) {
                continue;
            }
            if (vect[i].atomic->toString() == vect[j].atomic->toString()) {
                return true;
            }
        }
    }
    return false;
}

Validator::AtomicVector Validator::getAtomic(const LogicFormulaPtr &formula) {
    if (formula->getType() == Types::Atomic) {
        return {{formula, false}};
    }

    if(formula->getType() == Types::Negation && formula->getChildren()[0]->getType() == Types::Atomic) {
        return {{formula->getChildren()[0], true}};
    } 

    if (formula->getType() == Types::Conjunction) {
        AtomicVector result;
        for (auto& child : formula->getChildren()) {
            for (auto& form : getAtomic(child)) {
                result.emplace_back(form);
            }
        }
        if (checkRepeat(result)) {
            throw std::invalid_argument("It's not a PDNF formula");
        }
        return result;
    }

    throw std::invalid_argument("It's not a PDNF formula");
}

bool Validator::isEquivalentAtomics(const AtomicVector &lhs, const AtomicVector &rhs) {
    for (const auto &l : lhs) {
        bool isExist = false;;
        for (const auto &r : rhs) {
            if (l.atomic->toString() == r.atomic->toString()) {
                isExist = true;
                break;
            }
        }
        if (!isExist) {
            return false;
        }
    }
    return true;
}

bool Validator::compareAtomics(const AtomicVector &lhs, const AtomicVector &rhs) {
    if (!isEquivalentAtomics(lhs, rhs)) {
        throw std::invalid_argument("It's not a PDNF formula");
    }
    for (const auto &l : lhs) {
        for (const auto &r : rhs) {
            if (l.atomic->toString() == r.atomic->toString() && l.negated != r.negated) {
                return false;
            }
        }
    }
    return true;
}

