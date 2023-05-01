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
        string baseFilePath;
        vector<string> coapResponsePaths;
        SeatMatrix currSeatMatrix; 
    protected:
    public:
        Project(string fileName);
        // make a load file function
        void loadData(string fileName);
        void sort();
        void preProcessData(uint roundNumber);
        void deleteRound(uint roundNumber);
        void addRound();

};
