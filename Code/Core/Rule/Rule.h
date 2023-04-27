#ifndef RULE_H
#define RULE_H

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

namespace Rule{

typedef shared_ptr<BaseRule>, uint ruleElement;

// have to implement approximate factory method here

class Rule{
private:
std::map <shared_ptr<BaseRule>, uint> ruleComposition;
protected:
friend class BaseRule;
public:
Rule(): ruleComposition({}) {};
Rule(const Rule& referenceRule);
Rule(Rule&& rule);

bool configureRule();
bool loadRule(std::map <ruleElement> referenceRuleComposition);
std::map <ruleElement> fetchRule();

~Rule();
};

class BaseRule{
private:
std::string columnName;
protected:
public:
BaseRule() : columnName("def") {};
BaseRule(const BaseRule& referenceBaseRule);
BaseRule(BaseRule&& baseRule);

BaseRule operator < (BaseRule& coBaseRule) {

}

}

}

#endif RULE_H