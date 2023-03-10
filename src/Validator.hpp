#pragma once

#include "LogicFormula.hpp"

class Validator {
public:
    static bool isPDNF(const LogicFormulaPtr &formula);
private:
    struct ConjunctionElement {
        LogicFormulaPtr atomic;
        bool negated;
        std::string toString();
    };
    using AtomicVector = std::vector<ConjunctionElement>;
    
    static std::vector<LogicFormulaPtr> getConjunctions(const LogicFormulaPtr &formula);
    static AtomicVector getAtomic(const LogicFormulaPtr &formula);
    static bool checkRepeat(const AtomicVector &vect);

    static bool isEquivalentAtomics(const AtomicVector &lhs, const AtomicVector &rhs);
    static bool compareAtomics(const AtomicVector &lhs, const AtomicVector &rhs);


};