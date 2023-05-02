#include "RuleInterface.h"
using namespace std;

template <typename T>
bool Rule::CompositeRule<T>::configureRulePriorities(std::map<shared_ptr<Rule<T>>, uint32_t> referenceRulePriorities) {

    for(auto& rulePriority: referenceRulePriorities)
        {
            this->rulePriorities[rulePriority.first] = rulePriority.second;
        }
    return true;
}

template <typename T>
std::map<shared_ptr<Rule::Rule<T>>, uint32_t>
Rule::CompositeRule<T>::fetchRulePriorities(std::vector<shared_ptr<Rule<T>>> requestedRules) {

    std::map<shared_ptr<Rule<T>>, uint32_t> resultRulePriorities;
    for(auto& rulePointer: requestedRules) {
        resultRulePriorities[rulePointer] = this->resultPriorities[rulePointer];
    }

    return resultRulePriorities;
}

/* Accessor functions for handling storage
of rules and their priorities.*/
template <typename T>
std::map<shared_ptr<Rule::Rule<T>>, uint32_t> Rule::CompositeRule<T>::fetchAllRulePriorities() { 
    return this->rulePriorities;
}

/* Mutator functions for handling storage
of rules and their priorities.*/
template <typename T>
bool Rule::CompositeRule<T>::updateRules
(std::vector<std::pair<shared_ptr<Rule<T>>, shared_ptr<Rule<T>>>> rulesExchangeMap) {

    for(auto& ruleExchangePair: rulesExchangeMap) {
        this->rulePriorities[ruleExchangePair.second] = this->rulePriorities[ruleExchangePair.first];
        this->rulePriorities.erase(ruleExchangePair.first);
    }
    return true;
}
template <typename T>
bool Rule::CompositeRule<T>::updateRulePriorities(std::vector<std::pair<shared_ptr<Rule<T>>,
     uint32_t>> updatedPrioritizedRules) {
        // keep an assert for checking if the rule is already there?
    for(auto& newRulePriority: updatedPrioritizedRules) {
        this->rulePriorities[newRulePriority.first] = newRulePriority.second;
    }
    return true;
}
template <typename T>
bool Rule::CompositeRule<T>::addRules(std::vector<std::pair<shared_ptr<Rule<T>>, uint32_t>> newRules) {
    for(auto& newRule: newRules) {
        this->rulePriorities.insert(newRule);
    }
    return true;
}
template <typename T>
bool Rule::CompositeRule<T>::subtractRules(std::vector<shared_ptr<Rule<T>>> oldRules) {
    for(auto& oldRule: oldRules) {
        this->rulePriorities.erase(oldRule);
    }
    return true;
}

/* Accessor-mutator pair for handling storage of various rule conjunctions.*/
template <typename T>
bool Rule::CompositeRule<T>::configureRuleConjunctions
(std::map<std::pair<shared_ptr<Rule<T>>, shared_ptr<Rule<T>>>, ruleMixType> ruleConjunctions) {

    this->ruleConjunctions = ruleConjunctions;
    return true;
 }
template <typename T>
std::map<std::pair<shared_ptr<Rule::Rule<T>>, shared_ptr<Rule::Rule<T>>>, Rule::ruleMixType> 
Rule::CompositeRule<T>::fetchRuleConjunctions(std::vector<std::pair<shared_ptr<Rule<T>>,
  shared_ptr<Rule<T>>>> rulePairs) {

std::map<std::pair<shared_ptr<Rule<T>>, shared_ptr<Rule<T>>>,
 ruleMixType> resultRuleConjunctions;

    for(auto& rulePair: rulePairs) {
        resultRuleConjunctions[rulePair] = this->ruleConjunctions[rulePair];
    }
    return resultRuleConjunctions;
  }

/* Accessor function for handling storage of various rule conjunctions.*/
template <typename T>
std::map<std::pair<shared_ptr<Rule::Rule<T>>, shared_ptr<Rule::Rule<T>>>, Rule::ruleMixType> 
Rule::CompositeRule<T>::fetchAllRuleConjunctions() { return this->ruleConjunctions; }

/* Mutator functions for handling storage
of various rule conjunctions.*/
template <typename T>
bool Rule::CompositeRule<T>::updateRulePair(std::vector<std::pair<std::pair<shared_ptr<Rule<T>>,
 shared_ptr<Rule<T>>>, std::pair<shared_ptr<Rule<T>>, shared_ptr<Rule<T>>>>> rulePairsExchangeMap) {

    for(auto& ruleQuadruple: rulePairsExchangeMap) {
        this->ruleConjunctions[ruleQuadruple.first] = this->ruleConjunctions[ruleQuadruple.second];
        this->ruleConjunctions.erase(ruleQuadruple.second);
    }
    return true;
  }
 template <typename T>
bool Rule::CompositeRule<T>::updateRuleConjunctions(std::vector<std::pair<std::pair<shared_ptr<Rule<T>>,
 shared_ptr<Rule<T>>>, ruleMixType>> updatedRuleConjunctions) {

    for(auto& updatedRuleConjunction: updatedRuleConjunctions) {
        this->ruleConjunctions[updatedRuleConjunction.first] = updatedRuleConjunction.second;
    }
    return true;
 }
 template <typename T>
bool Rule::CompositeRule<T>::addRuleConjunctions(
    std::vector<std::pair<std::pair<shared_ptr<Rule<T>>, shared_ptr<Rule<T>>>,
 ruleMixType>> newRuleConjunctions) {

    for (auto& newRuleConjunction: newRuleConjunctions) {
        this->ruleConjunctions.insert(newRuleConjunction);
    }
    return true;
 }
 template <typename T>
bool Rule::CompositeRule<T>::subtractRuleConjunctions(std::vector<std::pair<shared_ptr<Rule<T>>,
 shared_ptr<Rule<T>>>> oldRuleConjunctions) {

    for (auto& oldRuleConjunction: oldRuleConjunctions) {
        this->ruleConjunctions.erase(oldRuleConjunction);
    }
    return true;
 }