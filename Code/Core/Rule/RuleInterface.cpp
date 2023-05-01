#include <RuleInterface.h>
using namespace std;

namespace Rule
{
    bool CompositeRule<int>::configureRulePriorities(std::map<shared_ptr<Rule<int>>, uint32_t> referenceRulePriorities) {};
} // namespace Rule
