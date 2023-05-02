#include "Rule.h"
using namespace std;

bool GateScoreRule::comparator(std::string score1, std::string score2) {
    uint32_t _score1 = stoi(score1);
    uint32_t _score2 = stoi(score2);
    return _score1 < _score2;
}

bool DoBRule::comparator(std::string dob1, std::string dob2) {
    // asumming the format dd-mm-yy
    

}