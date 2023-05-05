#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>
// #include "../Rule/Rule.h"
#include "../SeatMatrix/SeatMatrix.h"
using namespace std;

class Comparator{
    public:
        bool operator()(vector<string> a,vector<string> b){
            if(stoi(a[3]) == stoi(b[3])){
                string dob1 = a[2];
                string dob2 = b[2];

                const std::string delimiter = "-";
                int result = -1;
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

                int yearComparison = (stoi(year[0]) == stoi(year[1]));

                if (stoi(year[0]) < stoi(year[1])) {
                    yearComparison = -1;
                } else if (stoi(year[0]) ==  stoi(year[1])) {
                    yearComparison = 0;
                } else {
                    yearComparison = 1;
                }

                if (yearComparison == 0) {
                    int monthComparison = (stoi(month[0]) == stoi(month[1]));

                if (stoi(month[0]) < stoi(month[1])) {
                    monthComparison = -1;
                } else if (stoi(month[0]) ==  stoi(month[1])) {
                    monthComparison = 0;
                } else {
                    monthComparison = 1;
                }

                    if (monthComparison == 0) {
                    int dayComparison = (stoi(day[0]) == stoi(day[1]));

                if (stoi(day[0]) < stoi(day[1])) {
                    dayComparison = -1;
                } else if (stoi(day[0]) ==  stoi(day[1])) {
                    dayComparison = 0;
                } else {
                    dayComparison = 1;
                }

                    if (dayComparison == 0) {
                        result = 1;
                    } else if (dayComparison < 0) {
                        result = 0;
                    } else {
                        result = 1;
                    }

                    } else if (monthComparison < 0) {
                    result = 0;
                    } else {
                    result = 1;
                    }

                } else if (yearComparison < 0) {
                    result = 0;
                } else {
                    result = 1;
                }

                return 1-result;
            }
            return stoi(a[3]) > stoi(b[3]);
        }
};

namespace Project {
class Project {
    private: 
        // Rule::CoAPRule* currRule;
        uint32_t currRoundState;
        vector<uint32_t> totalRounds;
        string baseFilePath;
        vector<string> offerResponsePaths;
        vector<vector<string>> studentData;
        map<string,int> studentColPlace; // tells the colId of the colName
        set<string> visited;
        map<string,vector<string>> studentPriority;
        unordered_map<string,string> rules;
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
        map<string,int> getColData();
        vector<vector<string>> getOffers();
        vector<map<string,string>> sortData(string coapResponsePath="",string directory="");
        vector<vector<string>> getOffers(uint32_t roundNumber);
        void updateBasedOnCoapData(string coapResponsePath,uint32_t roundNumber);
        void deleteRound(uint32_t roundNumber);
        void addRound();
        void switchRound(uint32_t roundNumber);
        void printCurrState();
};
}
