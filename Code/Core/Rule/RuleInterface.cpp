#include "RuleInterface.h"
using namespace std;

template <typename T, typename Ts>
bool Rule::CompositeRule<T, Ts>::configureRulePriorities(std::map<shared_ptr<Rule<Ts>>, uint32_t> referenceRulePriorities) {

    for(auto& rulePriority: referenceRulePriorities)
        {
            this->rulePriorities[rulePriority.first] = rulePriority.second;
        }
    return true;
}

template <typename T, typename Ts>
std::map<shared_ptr<Rule::Rule<Ts>>, uint32_t>
Rule::CompositeRule<T, Ts>::fetchRulePriorities(std::vector<shared_ptr<Rule<Ts>>> requestedRules) {

    std::map<shared_ptr<Rule<Ts>>, uint32_t> resultRulePriorities;
    for(auto& rulePointer: requestedRules) {
        resultRulePriorities[rulePointer] = this->resultPriorities[rulePointer];
    }

    return resultRulePriorities;
}

/* Accessor functions for handling storage
of rules and their priorities.*/
template <typename T, typename Ts>
std::map<shared_ptr<Rule::Rule<Ts>>, uint32_t> Rule::CompositeRule<T, Ts>::fetchAllRulePriorities() { 
    return this->rulePriorities;
}

/* Mutator functions for handling storage
of rules and their priorities.*/
template <typename T, typename Ts>
bool Rule::CompositeRule<T, Ts>::updateRules
(std::vector<std::pair<shared_ptr<Rule<Ts>>, shared_ptr<Rule<Ts>>>> rulesExchangeMap) {

    for(auto& ruleExchangePair: rulesExchangeMap) {
        this->rulePriorities[ruleExchangePair.second] = this->rulePriorities[ruleExchangePair.first];
        this->rulePriorities.erase(ruleExchangePair.first);
    }
    return true;
}
template <typename T, typename Ts>
bool Rule::CompositeRule<T, Ts>::updateRulePriorities(std::vector<std::pair<shared_ptr<Rule<Ts>>,
     uint32_t>> updatedPrioritizedRules) {
        // keep an assert for checking if the rule is already there?
    for(auto& newRulePriority: updatedPrioritizedRules) {
        this->rulePriorities[newRulePriority.first] = newRulePriority.second;
    }
    return true;
}
template <typename T, typename Ts>
bool Rule::CompositeRule<T, Ts>::addRules(std::vector<std::pair<shared_ptr<Rule<Ts>>, uint32_t>> newRules) {
    for(auto& newRule: newRules) {
        this->rulePriorities.insert(newRule);
    }
    return true;
}
template <typename T, typename Ts>
bool Rule::CompositeRule<T, Ts>::subtractRules(std::vector<shared_ptr<Rule<Ts>>> oldRules) {
    for(auto& oldRule: oldRules) {
        this->rulePriorities.erase(oldRule);
    }
    return true;
}

/* Accessor-mutator pair for handling storage of various rule conjunctions.*/
template <typename T, typename Ts>
bool Rule::CompositeRule<T, Ts>::configureRuleConjunctions
(std::map<std::pair<shared_ptr<Rule<Ts>>, shared_ptr<Rule<Ts>>>, ruleMixType> ruleConjunctions) {

    this->ruleConjunctions = ruleConjunctions;
    return true;
 }
template <typename T, typename Ts>
std::map<std::pair<shared_ptr<Rule::Rule<Ts>>, shared_ptr<Rule::Rule<Ts>>>, Rule::ruleMixType> 
Rule::CompositeRule<T, Ts>::fetchRuleConjunctions(std::vector<std::pair<shared_ptr<Rule<Ts>>,
  shared_ptr<Rule<Ts>>>> rulePairs) {

std::map<std::pair<shared_ptr<Rule<Ts>>, shared_ptr<Rule<Ts>>>,
 ruleMixType> resultRuleConjunctions;

    for(auto& rulePair: rulePairs) {
        resultRuleConjunctions[rulePair] = this->ruleConjunctions[rulePair];
    }
    return resultRuleConjunctions;
  }

/* Accessor function for handling storage of various rule conjunctions.*/
template <typename T, typename Ts>
std::map<std::pair<shared_ptr<Rule::Rule<Ts>>, shared_ptr<Rule::Rule<Ts>>>, Rule::ruleMixType> 
Rule::CompositeRule<T, Ts>::fetchAllRuleConjunctions() { return this->ruleConjunctions; }

/* Mutator functions for handling storage
of various rule conjunctions.*/
template <typename T, typename Ts>
bool Rule::CompositeRule<T, Ts>::updateRulePair(std::vector<std::pair<std::pair<shared_ptr<Rule<Ts>>,
 shared_ptr<Rule<Ts>>>, std::pair<shared_ptr<Rule<Ts>>, shared_ptr<Rule<Ts>>>>> rulePairsExchangeMap) {

    for(auto& ruleQuadruple: rulePairsExchangeMap) {
        this->ruleConjunctions[ruleQuadruple.first] = this->ruleConjunctions[ruleQuadruple.second];
        this->ruleConjunctions.erase(ruleQuadruple.second);
    }
    return true;
  }
 template <typename T, typename Ts>
bool Rule::CompositeRule<T, Ts>::updateRuleConjunctions(std::vector<std::pair<std::pair<shared_ptr<Rule<Ts>>,
 shared_ptr<Rule<Ts>>>, ruleMixType>> updatedRuleConjunctions) {

    for(auto& updatedRuleConjunction: updatedRuleConjunctions) {
        this->ruleConjunctions[updatedRuleConjunction.first] = updatedRuleConjunction.second;
    }
    return true;
 }
 template <typename T, typename Ts>
bool Rule::CompositeRule<T, Ts>::addRuleConjunctions(
    std::vector<std::pair<std::pair<shared_ptr<Rule<Ts>>, shared_ptr<Rule<Ts>>>,
 ruleMixType>> newRuleConjunctions) {

    for (auto& newRuleConjunction: newRuleConjunctions) {
        this->ruleConjunctions.insert(newRuleConjunction);
    }
    return true;
 }
 template <typename T, typename Ts>
bool Rule::CompositeRule<T, Ts>::subtractRuleConjunctions(std::vector<std::pair<shared_ptr<Rule<Ts>>,
 shared_ptr<Rule<Ts>>>> oldRuleConjunctions) {

    for (auto& oldRuleConjunction: oldRuleConjunctions) {
        this->ruleConjunctions.erase(oldRuleConjunction);
    }
    return true;
 }

 template <typename T, typename Ts>
Rule::relationType Rule::CompositeRule<T, Ts>::comparator(T operand1, T operand2) {
    
    for(auto& rulePriority: this->rulePriorities) {
        if(rulePriority.first->comparator(operand1, operand2) != relationType::equal)
            return rulePriority.first->comparator(operand1, operand2);
    }
    return relationType::equal;
 }
