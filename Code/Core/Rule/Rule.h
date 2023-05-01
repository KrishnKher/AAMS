#ifndef RULE_H
#define RULE_H

#include <iostream>
#include <bits/stdc++.h>
#include "RuleInterface.h"
using namespace std;

// can have maxbase rule, minbase rule, groupby baserule, etc.

// visitor pattern: later

class GateScoreRule: public Rule::BaseRule<uint32_t> {
public:
  bool condition() override { return true; }

  bool comparator(uint32_t score1, uint32_t score2) override;

  inline bool operator and (Rule &complementaryRule) override {return true; }
  inline bool operator or (Rule &complementaryRule) override {return true; }
  inline bool operator not () override {return true; }
};

class DoBRule: public Rule::BaseRule<std::string> {
public:
  inline bool condition() override { return true; }

  bool comparator(std::string date1, std::string date2) override;

  inline bool operator and (Rule &complementaryRule) override {return true; }
  inline bool operator or (Rule &complementaryRule) override {return true; }
  inline bool operator not () override {return true; }
};

class CoAPRule: public Rule::CompositeRule<uint32_t, std::string> {
 public:
  inline bool condition() override { return true; }

  bool comparator(uint32_t _, uint32_t __, std::string ___, std::string ____) override;

  inline bool operator and (Rule &complementaryRule) override {return true; }
  inline bool operator or (Rule &complementaryRule) override {return true; }
  inline bool operator not () override {return true; }
};


#endif RULE_H
