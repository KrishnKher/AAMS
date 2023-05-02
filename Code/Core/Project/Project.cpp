// #include "Project.h"
// using namespace std;

// Project::Project(string fileName,map<string,map<string,uint32_t>> matrix){
//     currRoundState = 1;
//     baseFilePath = fileName;
//     totalRounds.push_back(currRoundState);
//     coapResponsePaths.push_back("coap_response_"+to_string(currRoundState));
//     SeatMatrix temp(matrix);
//     this->currSeatMatrix = temp;
// }

// void Project::deleteRound(uint32_t roundNumber){
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

// void Project::switchRound(uint32_t roundNumber){
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
//         int colId = 0;
//         while(std::getline(ss, colName, ',')){
            
//             // Initialize and add <colname, int vector> pairs to result
//             data.push_back({colName, std::vector<string> {}});
//             if(visited.find(colName) == visited.end()){
//                 colPlace[colName] = colId;
//                 visited.insert(colName);
//             }
//             colId++;
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

// void Project::deleteRow(uint32_t id){
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
//     for(int i=0;i<data.size();i++){
//         if(data[i].first == "applicant_id" || data[i].first == "category" || data[i].first == "specialization_desc_1" || data[i].first == "specialization_desc_2" || data[i].first == "specialization_desc_3" || data[i].first == "specialization_desc_4" || data[i].first == "specialization_desc_5"){
//             if(visited.find(data[i].first) == visited.end()){
//                 visited.insert(data[i].first);
//                 colPlace[data[i].first] = i;
//             }
//         }
//     }
//     for(int i=0;i<data.at(colPlace["applicant_id"]).second.size();i++){
//         studentPriority[data.at(colPlace["applicant_id"]).second[i]].push_back(data.at(colPlace["specialization_desc_1"]).second[i]);
//         studentPriority[data.at(colPlace["applicant_id"]).second[i]].push_back(data.at(colPlace["specialization_desc_2"]).second[i]);
//         studentPriority[data.at(colPlace["applicant_id"]).second[i]].push_back(data.at(colPlace["specialization_desc_3"]).second[i]);
//         studentPriority[data.at(colPlace["applicant_id"]).second[i]].push_back(data.at(colPlace["specialization_desc_4"]).second[i]);
//         studentPriority[data.at(colPlace["applicant_id"]).second[i]].push_back(data.at(colPlace["specialization_desc_5"]).second[i]);
//     }
// }

// void Project::preProcessData(string coapResponsePath,uint32_t roundNumber){
//     vector<pair<string,vector<string>>> coapData;
//     map<string,int> colPlaceCoap;
//     set<string> visitedCoap;
//     ifstream file(coapResponsePath);
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
//         int colId = 0;
//         while(std::getline(ss, colName, ',')){
            
//             // Initialize and add <colname, int vector> pairs to result
//             coapData.push_back({colName, std::vector<string> {}});
//             if(visitedCoap.find(colName) == visited.end()){
//                 colPlaceCoap[colName] = colId;
//                 visitedCoap.insert(colName);
//             }
//             colId++;
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
//                 coapData.at(colId).second.push_back(temp);
//                 //cout<<temp<<endl;
//                 temp = "";
//                 colId++;
//             }
//             else{
//                 temp += line[i];
//             }
//         }
//         coapData.at(colId).second.push_back(temp);
//         //cout<<temp<<temp.size()<<endl;//"  "<<colId<<endl;//<<data.at(colId).first<<endl;
//     }
//     for(int i=0;i<coapData.at(colPlace["MTech Application No"]).second.size();i++){
//         if(coapData.at(colPlace["Program Offered"]).second[i] == "Reject and Wait"){
//             studentPriority[coapData.at(colPlace["MTech Application No"]).second[i]];
//         }
//         else if(coapData.at(colPlace["Program Offered"]).second[i] == "Accept and Freeze"){

//         }
//         else if(coapData.at(colPlace["Program Offered"]).second[i] == "Retain and Wait"){
            
//         }
//     }
// }

// void Project::updateSeatMatrix(){
//     for(int student=0;student<studentPriority.size();student++){

//     }
// }
// void Project::sort(){

// }

#include <iostream>
#include <bits/stdc++.h>
#include "../SeatMatrix/SeatMatrix.h"
using namespace std;

int main(){
    ifstream file("/home/sujeeth/project_graph/SWE/modCoap.csv");
    vector<pair<string,vector<string>>> data;
    if(!file.is_open()) throw std::runtime_error("Could not open file");
    string line,colName;
    string val;
    map<string,int> colPlace;
    set<string> visited;
    map<string,map<string,uint32_t>> matrix;
    matrix["CSE"]["GEN"] = 1;
    matrix["CSE"]["OBC"] = 1;
    matrix["CSE"]["SC"] = 1;
    matrix["CSE"]["ST"] = 1;

    matrix["AI"]["GEN"] = 1;
    matrix["AI"]["OBC"] = 1;
    matrix["AI"]["SC"] = 1;
    matrix["AI"]["ST"] = 1;

    matrix["EE"]["GEN"] = 1;
    matrix["EE"]["OBC"] = 1;
    matrix["EE"]["SC"] = 1;
    matrix["EE"]["ST"] = 1;

    matrix["MnC"]["GEN"] = 1;
    matrix["MnC"]["OBC"] = 1;
    matrix["MnC"]["SC"] = 1;
    matrix["MnC"]["ST"] = 1;

    matrix["BM"]["GEN"] = 1;
    matrix["BM"]["OBC"] = 1;
    matrix["BM"]["SC"] = 1;
    matrix["BM"]["ST"] = 1;

    matrix["CE"]["GEN"] = 1;
    matrix["CE"]["OBC"] = 1;
    matrix["CE"]["SC"] = 1;
    matrix["CE"]["ST"] = 1;

    matrix["CH"]["GEN"] = 1;
    matrix["CH"]["OBC"] = 1;
    matrix["CH"]["SC"] = 1;
    matrix["CH"]["ST"] = 1;
    SeatMatrix m(matrix);
    if(file.good())
    {
        // Extract the first line in the file
        std::getline(file, line);
        line.pop_back();

        // Create a stringstream from line
        std::stringstream ss(line);

        // Extract each column name
        int colId = 0;
        while(std::getline(ss, colName, ',')){
            
            // Initialize and add <colname, int vector> pairs to result
            data.push_back({colName, std::vector<string> {}});
            if(visited.find(colName) == visited.end()){
                colPlace[colName] = colId;
                visited.insert(colName);
            }
            colId++;
        }
    }
    for(auto i=colPlace.begin();i!=colPlace.end();i++){
        cout<<i->first<<" "<<i->second<<endl;
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
    
    // cout<<data.at(colPlace["applicant_id"]).second[0]<<" :"<<data.at(colPlace["specialization_desc_2"]).second[0]<<endl;
    // for(int i=0;i<data.at(colPlace["applicant_id"]).second.size();i++){
    //     studentPriority[data.at(colPlace["applicant_id"]).second[i]].push_back(data.at(colPlace["specialization_desc_1"]).second[i]);
    //     studentPriority[data.at(colPlace["applicant_id"]).second[i]].push_back(data.at(colPlace["specialization_desc_2"]).second[i]);
    //     studentPriority[data.at(colPlace["applicant_id"]).second[i]].push_back(data.at(colPlace["specialization_desc_3"]).second[i]);
    //     studentPriority[data.at(colPlace["applicant_id"]).second[i]].push_back(data.at(colPlace["specialization_desc_4"]).second[i]);
    //     studentPriority[data.at(colPlace["applicant_id"]).second[i]].push_back(data.at(colPlace["specialization_desc_5"]).second[i]);
    // }
    // cout<<studentPriority["1"][0]<<endl;
    // cout<<data.at(colPlace["category"]).second[0]<<endl;
    return 0;
}
