#include <iostream>
#include <bits/stdc++.h>
//#include "../Rule/Rule.h"
#include "../SeatMatrix/SeatMatrix.h"
using namespace std;

class Rule{
    int a;
};

class Project {
    private: 
        Rule* currRule;
        uint currRoundState;
        vector<uint> totalRounds;
        string baseFilePath;
        vector<string> coapResponsePaths;
        vector<pair<string,vector<string>>> data;
        map<pair<string,string>,vector<string>> studentPriority;
        vector<vector<pair<string,vector<string>>>> allRoundData;
        SeatMatrix currSeatMatrix; 
    protected:
    public:
        Project(string fileName,map<string,map<string,uint>> matrix);
        // make a load file function
        void loadData(string fileName);
        void loadStudentPriority(string fileName);
        void deleteRow(uint id);
        void createSeatMatrix(SeatMatrix matrix);
        void updateSeatMatrix();
        void sort();
        void preProcessData(string coapResponsePath,uint roundNumber);
        void deleteRound(uint roundNumber);
        void addRound();
        void switchRound(uint roundNumber);
};
