#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>
//#include "../Rule/Rule.h"
#include "../SeatMatrix/SeatMatrix.h"
using namespace std;

class Comparator{
    public:
        bool operator()(vector<string> a,vector<string> b){
            return stoi(a[3]) > stoi(b[3]);
        }
};

void printData(vector<vector<string>> data){
    for(int i=0;i<data.size();i++){
        for(int j=0;j<data[i].size();j++){
            cout<<data[i][j]<<" ";
        }
        cout<<endl;
    }
}

namespace Project {
class Project {
    private: 
        //Rule::Rule<string>* currRule;
        uint32_t currRoundState;
        vector<uint32_t> totalRounds;
        string baseFilePath;
        vector<string> offerResponsePaths;
        vector<vector<string>> studentData;
        map<string,int> studentColPlace; // tells the colId of the colName
        set<string> visited;
        map<string,vector<string>> studentPriority;
        vector<vector<string>> offeredStudents;
        vector<vector<pair<string,vector<string>>>> allRoundData;
        SeatMatrix currSeatMatrix; 
    protected:
    public:
        Project();
        void setBaseFileSeatMatrix(string fileName,map<string,map<string,uint32_t>> matrix);
        // make a load file function
        pair<map<string,int>,vector<vector<string>>> loadData(string fileName);
        void loadStudentPriority();
        void setPriority(map<string,string> priority);
        void deleteRow(uint32_t id);
        void createSeatMatrix(SeatMatrix matrix);
        vector<vector<string>> getOffers();
        vector<map<string,string>> sortData(string coapResponsePath,string directory);
        vector<vector<string>> getOffers(uint32_t roundNumber);
        void updateBasedOnCoapData(string coapResponsePath,uint32_t roundNumber);
        void deleteRound(uint32_t roundNumber);
        void addRound();
        void switchRound(uint32_t roundNumber);
        void printCurrState();
};
}