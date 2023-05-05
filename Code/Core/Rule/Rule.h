#ifndef RULE_H
#define RULE_H

#include <iostream>
#include <bits/stdc++.h>
#include "RuleInterface.h"
using namespace std;

// can have maxbase rule, minbase rule, groupby baserule, etc.

// visitor pattern: later

// see if GateScorerule etc can be taken out of Rule namespace, and if we should do it.

namespace Rule {

  class DefaultStringRule: public BaseRule <std::string> {
public:
  bool condition() override { return true; }

  relationType comparator(std::string entry1, std::string entry2) override;

  inline bool operator and (Rule &complementaryRule) override {return true; }
  inline bool operator or (Rule &complementaryRule) override {return true; }
  inline bool operator not () override {return true; }
};

  class DefaultNumericRule: public BaseRule <std::string> {
public:
  bool condition() override { return true; }

  relationType comparator(std::string entry1, std::string entry2) override;

  inline bool operator and (Rule &complementaryRule) override {return true; }
  inline bool operator or (Rule &complementaryRule) override {return true; }
  inline bool operator not () override {return true; }
};


class DoBRule: public BaseRule <std::string> {
public:
  inline bool condition() override { return true; }

  relationType comparator(std::string date1, std::string date2) override;

  inline bool operator and (Rule &complementaryRule) override {return true; }
  inline bool operator or (Rule &complementaryRule) override {return true; }
  inline bool operator not () override {return true; }
};

class CoAPRule: public CompositeRule <std::vector<std::string>, std::string> {
 public:
  inline bool condition() override { return true; }

  relationType comparator(std::vector<std::string> coapEntry1, std::vector<std::string> coapEntry2) override;

  inline bool operator and (Rule &complementaryRule) override {return true; }
  inline bool operator or (Rule &complementaryRule) override {return true; }
  inline bool operator not () override {return true; }
};

}

#endif RULE_H
