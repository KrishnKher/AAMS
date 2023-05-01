#ifndef RULE_INTERFACE_H
#define RULE_INTERFACE_H

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

namespace Rule {

using ruleElement = std::pair<shared_ptr<BaseRule>, uint32_t>;

enum class dataType { numeric, text, other };
enum class ruleMixType { AND, NOT, OR };
enum class sortOrder { ascending, descending, none };

// composite + builder. first composite

class Rule {
private:
protected:
  shared_ptr<Rule> realRule;

public:
  //CONSTRUCTOR!

//   bool configureRule();
//   bool loadRule(std::map<ruleElement> referenceRuleComposition);
//   std::map<ruleElement> fetchRule();

  virtual bool comparator() = 0; //requires variadic, pack, fold expression

  virtual bool condition() = 0;

  /* Abstract functions for defining rule conjunctions.*/
  virtual bool operator and (Rule &complementaryRule) = 0;
  virtual bool operator or (Rule &complementaryRule) = 0;
  virtual bool operator not () = 0;

  /* Identifies itself as a base rule or a composite rule.*/
  virtual bool isCompositeRule() = 0;

  /* DEFAULT DESTRUCTOR?*/
  virtual ~Rule();
};

class BaseRule : public Rule {
private:
  std::string columnName;
  std::vector<uint32_t> rowIndices;
  sortOrder sortingOrder;

protected:
public:
  // virtual BaseRule() : columnName("def") {}; CONSTRUCTOR!!
  BaseRule(const BaseRule& referenceBaseRule);
  BaseRule(BaseRule&& baseRule);

  bool configureColumnName(std::string columnName);
  std::string fetchColumnName();

  bool configureRowIndices(std::vector <uint32_t> rowIndices);
  std::vector <uint32_t> fetchRowIndices();

  bool configureSortingOrder(sortOrder sortingOrder);
  sortOrder fetchSortingOrder();

  // bool condition() override;

  // bool comparator() override;

  // bool operator and (Rule &complementaryRule) override;
  // bool operator or (Rule &complementaryRule) override;
  // bool operator not () override;

  bool isCompositeRule() final;

  ~BaseRule() override; //DESTRUCTO!
};

  class CompositeRule : public Rule {
  private:
  protected:
    std::map<shared_ptr<Rule>, uint32_t> rulePriorities;
    std::map<std::pair<shared_ptr<Rule>, shared_ptr<Rule>>, ruleMixType> ruleConjunctions;

  public:
    /* Initialization based constructor.*/
    CompositeRule(); // initializer_list based!!!
    /* Deep copy constructor.*/
    CompositeRule(const CompositeRule &compositeRule);
    /* Move constructor for transferring ownership of rule objects.*/
    CompositeRule(CompositeRule &&compositeRule);

    /* Accessor-mutator function pair for handling storage
     of rules and their priorities.*/
    bool configureRulePriorities(std::map<shared_ptr<Rule>, uint32_t> referenceRulePriorities);
    bool configureRulePriorities(std::vector<std::pair<shared_ptr<Rule>, uint32_t>> referenceRulePriorities);
    std::vector<std::pair<shared_ptr<Rule>, uint32_t>> fetchRulePriorities(std::vector<shared_ptr<Rule>> requestedRules);

    /* Accessor functions for handling storage
    of rules and their priorities.*/
    std::map<shared_ptr<Rule>, uint32_t> fetchAllRulePriorities();

    /* Mutator functions for handling storage
    of rules and their priorities.*/
    bool updateRules(std::vector<std::pair<shared_ptr<Rule>, shared_ptr<Rule>>> rulesExchangeMap);
    bool updateRulePriorities(std::vector<std::pair<shared_ptr<Rule>, uint32_t>> updatedPrioritizedRules);
    bool addRules(std::vector<std::pair<shared_ptr<Rule>, uint32_t>> newRules);
    bool subtractRules(std::vector<shared_ptr<Rule>> oldRules);

    /* Accessor-mutator pair for handling storage of various rule conjunctions.*/
    bool configureRuleConjunctions(std::map<std::pair<shared_ptr<Rule>, shared_ptr<Rule>>,
     ruleMixType> ruleConjunctions);
    std::map<std::pair<shared_ptr<Rule>, shared_ptr<Rule>>,
     ruleMixType> fetchRuleConjunctions(std::vector<std::pair<shared_ptr<Rule>,
      shared_ptr<Rule>>> rulePairs);

    /* Accessor function for handling storage of various rule conjunctions.*/
    std::map<std::pair<shared_ptr<Rule>, shared_ptr<Rule>>,
     ruleMixType> fetchAllRuleConjunctions();

    /* Mutator functions for handling storage
    of various rule conjunctions.*/
    bool updateRulePair(std::vector<std::pair<std::pair<shared_ptr<Rule>, shared_ptr<Rule>>,
     std::pair<shared_ptr<Rule>, shared_ptr<Rule>>>> rulePairsExchangeMap);
    bool updateRuleConjunctions(std::vector<std::pair<std::pair<shared_ptr<Rule>, shared_ptr<Rule>>,
     ruleMixType>> updatedRuleConjunctions);
    bool addRuleConjunctions(std::vector<std::pair<std::pair<shared_ptr<Rule>, shared_ptr<Rule>>,
     ruleMixType>> newRuleConjunctions);
    bool subtractRuleConjunctions(std::vector<std::pair<shared_ptr<Rule>, shared_ptr<Rule>>> oldRuleConjunctions);

    // bool condition() override; // WHAT ABOUT pure virtial?

    // bool comparator() override;

    // bool operator and (Rule &complementaryRule) override;
    // bool operator or (Rule &complementaryRule) override;
    // bool operator not () override;

    bool isCompositeRule() final;

    ~CompositeRule() override;
  };

} // namespace Rule

#endif RULE_INTERFACE_H
