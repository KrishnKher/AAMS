// #include "Project.h"
// using namespace std;

// Project::Project(string fileName,map<string,map<string,uint>> matrix){
//     currRoundState = 1;
//     baseFilePath = fileName;
//     totalRounds.push_back(currRoundState);
//     coapResponsePaths.push_back("coap_response_"+to_string(currRoundState));
//     SeatMatrix temp(matrix);
//     this->currSeatMatrix = temp;
// }

// void Project::deleteRound(uint roundNumber){
//     if(currRoundState == 1){
//         //reset the data
//     }
//     else{
//         totalRounds.erase(totalRounds.begin()+roundNumber,totalRounds.end());
//         coapResponsePaths.erase(coapResponsePaths.begin()+roundNumber,coapResponsePaths.end());
//         currRoundState = roundNumber;
//         //reset the data
//     }
// }

// void Project::addRound(){
//     totalRounds.push_back(currRoundState + 1);
//     coapResponsePaths.push_back("coap_response_"+to_string(currRoundState+1));
// }

// void Project::switchRound(uint roundNumber){
//     //load the data of that round
// }

// /*void Project::createSeatMatrix(SeatMatrix matrix){
//     this->currSeatMatrix = matrix;
// }*/

// void Project::loadData(string fileName){
//     ifstream file(fileName);
//     if(!file.is_open()) throw std::runtime_error("Could not open file");
//     string line,colName;
//     string val;
//     if(file.good())
//     {
//         // Extract the first line in the file
//         std::getline(file, line);
//         line.pop_back();

//         // Create a stringstream from line
//         std::stringstream ss(line);

//         // Extract each column name
//         while(std::getline(ss, colName, ',')){
            
//             // Initialize and add <colname, int vector> pairs to result
//             data.push_back({colName, std::vector<string> {}});
//         }
//     }

//     while(std::getline(file, line))
//     {
//         line.pop_back();
//         string temp = "";
//         int colId = 0;
//         //cout<<line<<endl;
//         for(int i=0;i<line.size();i++){
            
//             if(line[i] == ','){
//                 data.at(colId).second.push_back(temp);
//                 //cout<<temp<<endl;
//                 temp = "";
//                 colId++;
//             }
//             else{
//                 temp += line[i];
//             }
//         }
//         data.at(colId).second.push_back(temp);
//         //cout<<temp<<temp.size()<<endl;//"  "<<colId<<endl;//<<data.at(colId).first<<endl;

//     }
//     allRoundData.push_back(data);
// }

// void Project::deleteRow(uint id){
//     int i,j;
//     for(i=0;i<data.size();i++){
//         if(data[i].first == "applicant_id"){
//             for(j=0;j<data[i].second.size();j++){
//                 if(data[i].second[j] == to_string(id)){
//                     break;
//                 }
//             }
//         }
//     }
//     if(j != data[i].second.size()){
//         for(i=0;i<data.size();i++){
//             data[i].second.erase(data[i].second.begin()+j);
//         }
//     }
// }

// void Project::loadStudentPriority(){
//     map<string,int> colPlace;
//     set<string> visited;
//     for(int i=0;i<data.size();i++){
//         if(data[i].first == "applicant_id" || data[i].first == "category" || data[i].first == "specialization_desc_1" || data[i].first == "specialization_desc_2" || data[i].first == "specialization_desc_3" || data[i].first == "specialization_desc_4" || data[i].first == "specialization_desc_5"){
//             if(visited.find(data[i].first) == visited.end()){
//                 visited.insert(data[i].first);
//                 colPlace[data[i].first] = i;
//             }
//         }
//     }
//     for(int i=0;i<data.at(colPlace["applicant_id"]).second.size();i++){
//         studentPriority[{data.at(colPlace["applicant_id"]).second[i],data.at(colPlace["category"])}].push_back(data.at(colPlace["specialization_desc_1"]).second[i]);
//         studentPriority[{data.at(colPlace["applicant_id"]).second[i],data.at(colPlace["category"])}].push_back(data.at(colPlace["specialization_desc_2"]).second[i]);
//         studentPriority[{data.at(colPlace["applicant_id"]).second[i],data.at(colPlace["category"])}].push_back(data.at(colPlace["specialization_desc_3"]).second[i]);
//         studentPriority[{data.at(colPlace["applicant_id"]).second[i],data.at(colPlace["category"])}].push_back(data.at(colPlace["specialization_desc_4"]).second[i]);
//         studentPriority[{data.at(colPlace["applicant_id"]).second[i],data.at(colPlace["category"])}].push_back(data.at(colPlace["specialization_desc_5"]).second[i]);
//     }
// }

// void Project::preProcessData(string coapResponsePath,uint roundNumber){

// }

// void Project::updateSeatMatrix(){
//     for(int student=0;student<studentPriority.size();student++){

//     }
// }
// void Project::sort(){

// }

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// void deleteRow(vector<pair<string,vector<string>>>& data,uint id){
//     int i,j;
//     for(i=0;i<data.size();i++){
//         if(data[i].first == "applicant_id"){
//             for(j=0;j<data[i].second.size();j++){
//                 if(data[i].second[j] == to_string(id)){
//                     break;
//                 }
//             }
//         }
//     }
//     if(j != data[i].second.size()){
//         for(i=0;i<data.size();i++){
//             data[i].second.erase(data[i].second.begin()+j);
//         }
//     }
// }


int main(){
    ifstream file("/home/sujeeth/project_graph/SWE/modCOAP.csv");
    vector<pair<string,vector<string>>> data;
    if(!file.is_open()) throw std::runtime_error("Could not open file");
    string line,colName;
    string val;
    if(file.good())
    {
        // Extract the first line in the file
        std::getline(file, line);
        line.pop_back();

        // Create a stringstream from line
        std::stringstream ss(line);

        // Extract each column name
        while(std::getline(ss, colName, ',')){
            
            // Initialize and add <colname, int vector> pairs to result
            data.push_back({colName, std::vector<string> {}});
        }
    }

    while(std::getline(file, line))
    {
        line.pop_back();
        string temp = "";
        int colId = 0;
        //cout<<line<<endl;
        for(int i=0;i<line.size();i++){
            
            if(line[i] == ','){
                data.at(colId).second.push_back(temp);
                //cout<<temp<<endl;
                temp = "";
                colId++;
            }
            else{
                temp += line[i];
            }
        }
        data.at(colId).second.push_back(temp);
        //cout<<temp<<temp.size()<<endl;//"  "<<colId<<endl;//<<data.at(colId).first<<endl;

    }
    //cout<<data[8].first[-1]<<endl;
    for(int i=0;i<data.size();i++){
        cout<<"ColName "<<i<<": "<<data[i].first<<" ";
        for(int j=0;j<data[i].second.size();j++){
            cout<<data[i].second[j]<<" ";
        }
        cout<<endl;
        cout.flush();
    }
    map<string,vector<string>> studentPriority;
    map<string,int> colPlace;
    set<string> visited;
    for(int i=0;i<data.size();i++){
        if(data[i].first == "applicant_id" || data[i].first == "specialization_desc_1" || data[i].first == "specialization_desc_2" || data[i].first == "specialization_desc_3" || data[i].first == "specialization_desc_4" || data[i].first == "specialization_desc_5"){
            if(visited.find(data[i].first) == visited.end()){
                visited.insert(data[i].first);
                colPlace[data[i].first] = i;
            }
        }
    }
    
    cout<<data.at(colPlace["applicant_id"]).second[0]<<" :"<<data.at(colPlace["specialization_desc_2"]).second[0]<<endl;
    for(int i=0;i<data.at(colPlace["applicant_id"]).second.size();i++){
        studentPriority[{data.at(colPlace["applicant_id"]).second[i],data.at(colPlace["category"])}].push_back(data.at(colPlace["specialization_desc_1"]).second[i]);
        studentPriority[{data.at(colPlace["applicant_id"]).second[i],data.at(colPlace["category"])}].push_back(data.at(colPlace["specialization_desc_2"]).second[i]);
        studentPriority[{data.at(colPlace["applicant_id"]).second[i],data.at(colPlace["category"])}].push_back(data.at(colPlace["specialization_desc_3"]).second[i]);
        studentPriority[{data.at(colPlace["applicant_id"]).second[i],data.at(colPlace["category"])}].push_back(data.at(colPlace["specialization_desc_4"]).second[i]);
        studentPriority[{data.at(colPlace["applicant_id"]).second[i],data.at(colPlace["category"])}].push_back(data.at(colPlace["specialization_desc_5"]).second[i]);
    }
    cout<<studentPriority[{"1","GEN"}]<<endl;
    return 0;
}
