#include "Rule.h"
using namespace std;

Rule::relationType Rule::DefaultNumericRule::comparator(std::string score1, std::string score2) {
  relationType result = relationType::equal;

  uint32_t _score1 = stoi(score1);
  uint32_t _score2 = stoi(score2);

  if(fetchSortingOrder() == sortOrder::none)
    return result;

  if (_score1 < _score2)
    result = relationType::lesser;
  else if (_score1 == _score2)
    result = relationType::equal;
  else
    result = relationType::greater;

  if(fetchSortingOrder() == sortOrder::ascending) {
    if (result != relationType::equal)
      {
        if(result == relationType::lesser)
          result = relationType::greater;
        else
          result = relationType::lesser;
      }
  }

  return result;
}

bool Rule::DefaultNumericRule::operator () (std::string score1, std::string score2) {
  bool result = false;

  relationType placeholder = comparator(score1, score2);

}

Rule::relationType Rule::DefaultStringRule::comparator(std::string score1, std::string score2) {
  relationType result = relationType::equal;

  if(fetchSortingOrder() == sortOrder::none)
    return result;

  if (score1 < score2)
    result = relationType::lesser;
  else if (score1 == score2)
    result = relationType::equal;
  else
    result = relationType::greater;

  if(fetchSortingOrder() == sortOrder::ascending) {
    if (result != relationType::equal)
      {
        if(result == relationType::lesser)
          result = relationType::greater;
        else
          result = relationType::lesser;
      }
  }

  return result;
}

// no sanitization that we did here!!
Rule::relationType Rule::DoBRule::comparator(std::string dob1, std::string dob2) {
  relationType result = relationType::equal;
  const std::string delimiter = "-";

  if(fetchSortingOrder() == sortOrder::none)
    return result;

  // asumming the format dd-mm-yy
  std::vector<std::string> day(2);
  std::vector<std::string> month(2);
  std::vector<std::string> year(2);

  day[0] = dob1.substr(0, dob1.find(delimiter));
  day[1] = dob2.substr(0, dob2.find(delimiter));

  auto dpos1 = dob1.find(delimiter);
  auto dpos2 = dob2.find(delimiter);

  dob1.erase(0, dpos1 + delimiter.length());
  dob2.erase(0, dpos2 + delimiter.length());

  month[0] = dob1.substr(0, dob1.find(delimiter));
  month[1] = dob2.substr(0, dob2.find(delimiter));

  dpos1 = dob1.find(delimiter);
  dpos2 = dob2.find(delimiter);

  dob1.erase(0, dpos1 + delimiter.length());
  dob2.erase(0, dpos2 + delimiter.length());

  year[0] = dob1.substr(0, dob1.find(delimiter));
  year[1] = dob2.substr(0, dob2.find(delimiter));

  auto yearComparison = stoi(year[0]) <=> stoi(year[1]);

  if (yearComparison == 0) {
    auto monthComparison = stoi(month[0]) <=> stoi(month[1]);

    if (monthComparison == 0) {
      auto dayComparison = stoi(day[0]) <=> stoi(day[1]);

      if (dayComparison == 0) {
        result = relationType::equal;
      } else if (dayComparison < 0) {
        result = relationType::lesser;
      } else {
        result = relationType::greater;
      }

    } else if (monthComparison < 0) {
      result = relationType::lesser;
    } else {
      result = relationType::greater;
    }

  } else if (yearComparison < 0) {
    result = relationType::lesser;
  } else {
    result = relationType::greater;
  }

  if(fetchSortingOrder() == sortOrder::ascending) {
    if (result != relationType::equal)
      {
        if(result == relationType::lesser)
          result = relationType::greater;
        else
          result = relationType::lesser;
      }
  }

  return result;
}

// small error here. need to fix it
Rule::relationType Rule::CoAPRule::comparator(std::vector<string> student1, std::vector<string> student2) {
  auto grandRuleIterator = this->rulePriorities.begin();

  while (grandRuleIterator != this->rulePriorities.end()) {
    std::string student1Attribute = student1[grandRuleIterator->first->fetchColumnIndex()];
    std::string student2Attribute = student2[grandRuleIterator->first->fetchColumnIndex()];

    if (grandRuleIterator->first->comparator(student1Attribute, student2Attribute) == relationType::equal) {
      grandRuleIterator++;
      return grandRuleIterator->first->comparator(student1Attribute, student2Attribute);
    } else {
      return grandRuleIterator->first->comparator(student1Attribute, student2Attribute);
    }
  }

  return relationType::equal;
}
