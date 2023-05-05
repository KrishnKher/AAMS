#ifndef RULE_INTERFACE_H
#define RULE_INTERFACE_H

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

namespace Rule {

enum class dataType { numeric, text, other };
enum relationType { lesser, greater, equal };
enum class ruleMixType { AND, NOT, OR };
enum class sortOrder { ascending, descending, none };

const std::string kDefaultColumnName = "header";
const sortOrder kDefaultSortOrder = sortOrder::descending;
const uint32_t kDefaultColumnIndex = 0;

// composite + builder. first composite

template <typename T>
class Rule {
private:
protected:
  shared_ptr <Rule> realRule;

public:
  //CONSTRUCTOR!

//   bool configureRule();
//   bool loadRule(std::map<ruleElement> referenceRuleComposition);
//   std::map<ruleElement> fetchRule();

  uint32_t fetchColumnIndex(); // temporary

  virtual relationType comparator(T operand1, T operand2) = 0; //requires variadic, pack, fold expression

  virtual bool condition() = 0;

  /* Abstract functions for defining rule conjunctions.*/
  virtual bool operator and (Rule &complementaryRule) = 0;
  virtual bool operator or (Rule &complementaryRule) = 0;
  virtual bool operator not () = 0;

  virtual bool operator () (T operand1, T operand2) = 0;

  /* Identifies itself as a base rule or a composite rule.*/
  virtual bool isCompositeRule() = 0;

  /* DEFAULT DESTRUCTOR?*/
  virtual ~Rule();
};

template <typename T>
class BaseRule : public Rule <T> {
private:
  std::string columnName;
  uint32_t columnIndex;
  std::vector <uint32_t> rowIndices;
  sortOrder sortingOrder;

protected:
public:
  BaseRule(std::string columnName = kDefaultColumnName, uint32_t columnIndex = kDefaultColumnIndex,
    rowIndices = {}, sortOrder sortingOrder = kDefaultSortOrder) : columnName(columnName), 
   columnIndex(columnIndex), rowIndices(rowIndices), sortingOrder(sortingOrder) {}; 
  // BaseRule(const BaseRule& referenceBaseRule);
  // BaseRule(BaseRule&& baseRule);

  inline bool configureColumnName(std::string columnName) { this->columnName = columnName; return true; };
  std::string fetchColumnName() { return this->columnName; }

  inline bool configureColumnIndex(uint32_t columnIndex) { this->columnIndex = columnInidex; return true; }
  uint32_t fetchColumnIndex() { return this->columnIndex; }

  inline bool configureRowIndices(std::vector <uint32_t> rowIndices) 
  { this->rowIndices = rowIndices; return true; }
  std::vector <uint32_t> fetchRowIndices() { return this->rowIndices; }

  inline bool configureSortingOrder(sortOrder sortingOrder) { this->sortingOrder = sortingOrder; return true; }
  sortOrder fetchSortingOrder() { return this->sortingOrder; }

  // inline bool condition() override { return true; };

  // bool comparator(T operand1, T operand2) override;

  // bool operator and (Rule &complementaryRule) override {return true; };
  // bool operator or (Rule &complementaryRule) override {return true; };
  // bool operator not () override {return true; };
  // bool operator () (T operand1, T operand2) override;

  inline bool isCompositeRule() final {return false; };

  // ~BaseRule() override; //DESTRUCTO!
};

template <typename T, typename Ts> // Need to update using variadic stuff.
class CompositeRule : public Rule <T> {
  private:
  protected:
    std::map<shared_ptr<Rule<Ts>>, uint32_t> rulePriorities;
    std::map<std::pair<shared_ptr<Rule<Ts>>, shared_ptr<Rule<Ts>>>, ruleMixType> ruleConjunctions;

  public:
    /* Initialization based constructor.*/
    CompositeRule(std::map<shared_ptr<Rule<Ts>>, uint32_t> rulePriorities = {},
    std::map<std::pair<shared_ptr<Rule<Ts>>, shared_ptr<Rule<Ts>>>, ruleMixType> ruleConjunctions = {})
    : rulePriorities(rulePriorities), ruleConjunctions(ruleConjunctions) {}; // initializer_list based!!!
    /* Deep copy constructor.*/
    CompositeRule(const CompositeRule &compositeRule) {};
    /* Move constructor for transferring ownership of rule objects.*/
    CompositeRule(CompositeRule &&compositeRule) {};

    /* Accessor-mutator function pair for handling storage
     of rules and their priorities.*/
    bool configureRulePriorities(std::map<shared_ptr<Rule<Ts>>, uint32_t> referenceRulePriorities);
    // bool configureRulePriorities(std::vector<std::pair<shared_ptr<Rule>, uint32_t>> referenceRulePriorities);
    // std::vector<std::pair<shared_ptr<Rule<Ts>>, uint32_t>> fetchRulePriorities(std::vector<shared_ptr<Rule<Ts>>> requestedRules);
    std::map<shared_ptr<Rule<Ts>>, uint32_t> fetchRulePriorities(std::vector<shared_ptr<Rule<Ts>>> requestedRules);

    /* Accessor functions for handling storage
    of rules and their priorities.*/
    std::map<shared_ptr<Rule<Ts>>, uint32_t> fetchAllRulePriorities();

    /* Mutator functions for handling storage
    of rules and their priorities.*/
    bool updateRules(std::vector<std::pair<shared_ptr<Rule<Ts>>, shared_ptr<Rule<Ts>>>> rulesExchangeMap);
    bool updateRulePriorities(std::vector<std::pair<shared_ptr<Rule<Ts>>, uint32_t>> updatedPrioritizedRules);
    bool addRules(std::vector<std::pair<shared_ptr<Rule<Ts>>, uint32_t>> newRules);
    bool subtractRules(std::vector<shared_ptr<Rule<Ts>>> oldRules);

    /* Accessor-mutator pair for handling storage of various rule conjunctions.*/
    bool configureRuleConjunctions(std::map<std::pair<shared_ptr<Rule<Ts>>, shared_ptr<Rule<Ts>>>,
     ruleMixType> ruleConjunctions);
    std::map<std::pair<shared_ptr<Rule<Ts>>, shared_ptr<Rule<Ts>>>,
     ruleMixType> fetchRuleConjunctions(std::vector<std::pair<shared_ptr<Rule<Ts>>,
      shared_ptr<Rule<Ts>>>> rulePairs);

    /* Accessor function for handling storage of various rule conjunctions.*/
    std::map<std::pair<shared_ptr<Rule<Ts>>, shared_ptr<Rule<Ts>>>,
     ruleMixType> fetchAllRuleConjunctions();

    /* Mutator functions for handling storage
    of various rule conjunctions.*/
    bool updateRulePair(std::vector<std::pair<std::pair<shared_ptr<Rule<Ts>>, shared_ptr<Rule<Ts>>>,
     std::pair<shared_ptr<Rule<Ts>>, shared_ptr<Rule<Ts>>>>> rulePairsExchangeMap);
    bool updateRuleConjunctions(std::vector<std::pair<std::pair<shared_ptr<Rule<Ts>>, shared_ptr<Rule<Ts>>>,
     ruleMixType>> updatedRuleConjunctions);
    bool addRuleConjunctions(std::vector<std::pair<std::pair<shared_ptr<Rule<Ts>>, shared_ptr<Rule<Ts>>>,
     ruleMixType>> newRuleConjunctions);
    bool subtractRuleConjunctions(std::vector<std::pair<shared_ptr<Rule<Ts>>, shared_ptr<Rule<Ts>>>> oldRuleConjunctions);

    // bool condition() override; // WHAT ABOUT pure virtial?

    relationType comparator(T operand1, T operand2) override;

    // bool operator and (Rule &complementaryRule) override;
    // bool operator or (Rule &complementaryRule) override;
    // bool operator not () override;

    // bool operator () (T operand1, T operand2) override;

    inline bool isCompositeRule() final {return true; };

    ~CompositeRule() override;
  };

} // namespace Rule

#endif RULE_INTERFACE_H
