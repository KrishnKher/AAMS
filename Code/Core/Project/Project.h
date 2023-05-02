#include <iostream>
#include <bits/stdc++.h>
#include "../Rule/Rule.h"
#include "../SeatMatrix/SeatMatrix.h"
using namespace std;

// class Rule{
//     int a;
// };

class Project {
    private: 
        Rule* currRule;
        uint32_t currRoundState;
        vector<uint32_t> totalRounds;
        string baseFilePath;
        vector<string> coapResponsePaths;
        vector<pair<string,vector<string>>> data;
        map<string,int> colPlace; // tells the colId of the colName
        set<string> visited;
        map<string,vector<string>> studentPriority;
        vector<vector<pair<string,vector<string>>>> allRoundData;
        SeatMatrix currSeatMatrix; 
    protected:
    public:
        Project(string fileName,map<string,map<string,uint32_t>> matrix);
        // make a load file function
        void loadData(string fileName);
        void loadStudentPriority();
        void deleteRow(uint32_t id);
        void createSeatMatrix(SeatMatrix matrix);
        void updateSeatMatrix();
        void sort();
        void preProcessData(string coapResponsePath,uint32_t roundNumber);
        void deleteRound(uint32_t roundNumber);
        void addRound();
        void switchRound(uint32_t roundNumber);
};
