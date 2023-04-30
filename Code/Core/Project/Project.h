#include <iostream>
#include <bits/stdc++.h>
#include "../Rule/Rule.h"
#include "../SeatMatrix/SeatMatrix.h"
using namespace std;

class Project {
    private: 
        Rule* currRule;
        uint currRoundState;
        vector<uint> totalRounds;
        vector<string> filePaths;
        SeatMatrix currSeatMatrix; 
    protected:
    public:
        void sort();
        void preProcessData(uint roundNumber);
        void deleteRound(uint roundNumber);
        void addRound();

};
