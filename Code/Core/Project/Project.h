#include <iostream>
#include <bits/stdc++.h>
#include "../Rule/Rule.h"
#include "../SeatMatrix/SeatMatrix.h"
using namespace std;

class Project {
    private: 
        Rule::Rule* currRule;
        uint32_t currRoundState;
        vector<uint32_t> totalRounds;
        string baseFilePath;
        vector<string> coapResponsePaths;
        SeatMatrix currSeatMatrix; 
    protected:
    public:
        Project(string fileName);
        // make a load file function
        void loadData(string fileName);
        void sort();
        void preProcessData(uint32_t roundNumber);
        void deleteRound(uint32_t roundNumber);
        void addRound();

};
