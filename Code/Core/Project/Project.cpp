#include "Project.h"
using namespace std;

namespace Project {
Project::Project(){
    currRoundState = 1;
    totalRounds.push_back(currRoundState);
    offerResponsePaths.push_back("coap_response_"+to_string(currRoundState));
}

void Project::setBaseFileSeatMatrix(string fileName,map<string,map<string,uint32_t>> matrix){
    baseFilePath = fileName;
    SeatMatrix temp(matrix);
    currSeatMatrix = temp;
}

void Project::deleteRound(uint32_t roundNumber){
    if(currRoundState == 1){
        //reset the data
    }
    else{
        totalRounds.erase(totalRounds.begin()+roundNumber,totalRounds.end());
        offerResponsePaths.erase(offerResponsePaths.begin()+roundNumber,offerResponsePaths.end());
        currRoundState = roundNumber;
        //reset the data
    }
}

void Project::addRound(){
    totalRounds.push_back(currRoundState + 1);
    offerResponsePaths.push_back("offers_"+to_string(currRoundState+1)+".csv");
    currRoundState++;
}

void Project::switchRound(uint32_t roundNumber){
    //load the data of that round
}

/*void Project::createSeatMatrix(SeatMatrix matrix){
    this->currSeatMatrix = matrix;
}*/

pair<map<string,int>,vector<vector<string>>> Project::loadData(string fileName){
    ifstream file(fileName);
    vector<vector<string>> studData;
    map<string,int> colPlace;
    if(!file.is_open()) throw std::runtime_error("Could not open file");
    string line,colName;
    string val;
    set<string> visited;
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
            if(visited.find(colName) == visited.end()){
                colPlace[colName] = colId;
                visited.insert(colName);
            }
            colId++;
        }
    }
    while(std::getline(file, line))
    {
        line.pop_back();
        vector<string> oneStudentData;
        string temp = "";
        int colId = 0;
        //cout<<line<<endl;
        for(int i=0;i<line.size();i++){
            if(line[i] == ','){
                oneStudentData.push_back(temp);
                //cout<<temp<<endl;
                temp = "";
                colId++;
            }
            else{
                temp += line[i];
            }
        }
        oneStudentData.push_back(temp);
        studData.push_back(oneStudentData);
    }
    return make_pair(colPlace,studData);
}

void Project::loadStudentPriority(){
        for(auto stud : studentData){
        if(stud.at(studentColPlace["specialization_desc_1"]).size() > 0)
        studentPriority[stud.at(studentColPlace["applicant_id"])].push_back(stud.at(studentColPlace["specialization_desc_1"]));
        if(stud.at(studentColPlace["specialization_desc_2"]).size() > 0)
        studentPriority[stud.at(studentColPlace["applicant_id"])].push_back(stud.at(studentColPlace["specialization_desc_2"]));
        if(stud.at(studentColPlace["specialization_desc_3"]).size() > 0)
        studentPriority[stud.at(studentColPlace["applicant_id"])].push_back(stud.at(studentColPlace["specialization_desc_3"]));
        if(stud.at(studentColPlace["specialization_desc_4"]).size() > 0)
        studentPriority[stud.at(studentColPlace["applicant_id"])].push_back(stud.at(studentColPlace["specialization_desc_4"]));
        if(stud.at(studentColPlace["specialization_desc_5"]).size() > 0)
        studentPriority[stud.at(studentColPlace["applicant_id"])].push_back(stud.at(studentColPlace["specialization_desc_5"]));
    }
}

void Project::updateBasedOnCoapData(string coapResponsePath,uint32_t roundNumber){
    pair<map<string,int>,vector<vector<string>>> c = loadData(coapResponsePath);
    
    map<string,int> coapColPlace = c.first; 
    vector<vector<string>> coapData = c.second;
    for(auto row : coapData){
        string id = row[coapColPlace["MTech Application No"]];
        string name = row[coapColPlace["Applicant Name"]];
        string category = row[coapColPlace["Offered Category"]];
        string spec = row[coapColPlace["Program Offered"]];
        string decision = row[coapColPlace["Applicant Decision"]];
        if(decision == "Accept and Freeze"){
            for(int i=0;i<studentData.size();i++){
                if(studentData[i][studentColPlace["applicant_id"]] == id){
                    offeredStudents.push_back(vector<string>{id,name,spec,category});
                    studentData.erase(studentData.begin()+i);
                    break;
                }
            }
        }
        else if(decision == "Retain and Wait"){
            continue;
        }
        else if(decision == "Reject and Wait"){
            for(int i=0;i<studentData.size();i++){
                if(studentData[i][studentColPlace["applicant_id"]] == id){
                    studentData[i][studentColPlace["offer"]] = "No Offer";
                    currSeatMatrix.addSeats(spec,category,1);
                    for(int i=0;i<studentPriority[id].size();i++){
                        if(studentPriority[id][i] == spec){
                            studentPriority[id].erase(studentPriority[id].begin()+i,studentPriority[id].end());
                            break;
                        }
                    }
                    break;
                }
            }
        }
        else{
            // generate an error
        }
    }
}

vector<vector<string>> Project::getOffers(uint32_t roundNumber){
    vector<vector<string>> results;
    for(auto& row : studentData){
        string id = row[studentColPlace["applicant_id"]];
        string name = row[studentColPlace["full_name"]];
        string stud_cat = row[studentColPlace["category"]];
        vector<string> specs = studentPriority[row[studentColPlace["applicant_id"]]];
        for(auto spec : specs){
            string row_cat = "",row_spec = "";
            string temp = "";
            for(int i=0;i<row[studentColPlace["offer"]].size();i++){
                if(row[studentColPlace["offer"]][i] == ','){
                    row_spec = temp;
                    temp = "";
                }
                else
                    temp += row[studentColPlace["offer"]][i];
            }
            row_cat = temp;
            if(spec == row_spec){  //if there is an offer from previous round then don't go further in priority
                results.push_back(vector<string>{id,name,row_spec,row_cat});
                break;
            }
            if(currSeatMatrix.getSeats(spec,"GEN") != 0){
                currSeatMatrix.deleteSeats(spec,"GEN",1);
                if(row[studentColPlace["offer"]] != "No Offer"){
                    currSeatMatrix.addSeats(row_spec,row_cat,1);
                }
                results.push_back(vector<string>{id,name,spec,"GEN"});
                row[studentColPlace["offer"]] = spec+","+"GEN";
                break;
            }
            else if(currSeatMatrix.getSeats(spec,stud_cat) != 0){
                currSeatMatrix.deleteSeats(spec,stud_cat,1);
                if(row[studentColPlace["offer"]] != "No Offer"){
                    currSeatMatrix.addSeats(row_spec,row_cat,1);
                }
                results.push_back(vector<string>{id,name,spec,stud_cat});
                row[studentColPlace["offer"]] = spec+","+stud_cat;
                break;
            }
        }
    }
    return results;
}

void Project::setPriority(map<string,string> priority){
    for(auto it=priority.begin();it!=priority.end();it++){
        string id = it->first;
        string prio = it->second;
        for(auto& row:studentData){
            if(row[studentColPlace["applicant_id"]] == id){
                row[studentColPlace["priority"]] = prio;
            }
        }
    }
}

vector<map<string,string>> Project::sortData(string coapResponsePath="",string directory=""){
    if(currRoundState == 1){
        pair<map<string,int>,vector<vector<string>>> s = loadData(baseFilePath);
        int tolCols = s.first.size();
        s.first["offer"] = tolCols;
        s.first["priority"] = tolCols+1;

        studentColPlace = s.first;
        studentData = s.second;
        for(int i=0;i<studentData.size();i++){
            studentData[i].push_back("No Offer");
            studentData[i].push_back("0");
        }
    }

    if(currRoundState == 1)
        loadStudentPriority();

    // Rule::Rule<string>* currRule = new GateScoreRule();

    if(currRoundState == 1){
        sort(studentData.begin(),studentData.end(),Comparator());
        vector<map<string,string>> groups;
        int g = 0;
        for(int i=0;i<studentData.size()-1;i++){
            if(studentData[i][studentColPlace["gate_score"]] == studentData[i+1][studentColPlace["gate_score"]]){
                if(studentData[i][studentColPlace["date_of_birth"]] == studentData[i+1][studentColPlace["date_of_birth"]]){
                    if(g==0 || g!=i){
                        map<string,string> temp;
                        groups.push_back(temp);
                    }
                    groups[groups.size()-1][studentData[i][studentColPlace["applicant_id"]]] = studentData[i][studentColPlace["full_name"]]; 
                    groups[groups.size()-1][studentData[i+1][studentColPlace["applicant_id"]]] = studentData[i+1][studentColPlace["full_name"]];
                    g=i+1;

                }
            }
        }
        if(groups.size() != 0)
            return groups;
    }
    
    if(currRoundState != 1)
        updateBasedOnCoapData(coapResponsePath,currRoundState);

    vector<vector<string>> results = getOffers(currRoundState);
    ofstream writer(directory+"offers_"+to_string(currRoundState)+".csv");
    writer<<"applicant_id,full_name,Program Offered,Offered Category"<<endl;
    for(auto res:results){
        for(int i=0;i<res.size();i++){
            if(i != res.size()-1)
                writer<<res[i]<<",";
            else
                writer<<res[i]<<endl;
        }
    }
    writer.close();
    return vector<map<string,string>>{};
}

void Project::printCurrState(){
    cout<<"Student Data:::"<<to_string(currRoundState)<<endl;
    printData(studentData);
    cout<<endl<<endl;
    cout<<"Seat Matrix::::"<<to_string(currRoundState)<<endl;
    currSeatMatrix.printSeats();
}
}

// #include <iostream>
// #include <bits/stdc++.h>
// #include "../SeatMatrix/SeatMatrix.h"
// // #include "../Rule/Rule.h"
// using namespace std;

// class Comparator{
//     public:
//         bool operator()(vector<string> a,vector<string> b){
//             return stoi(a[3]) > stoi(b[3]);
//         }
// };

// pair<map<string,int>,vector<vector<string>>> loadStudent(string fileName){
//     ifstream file(fileName);
//     vector<vector<string>> studentData;
//     map<string,int> colPlace;
//     if(!file.is_open()) throw std::runtime_error("Could not open file");
//     string line,colName;
//     string val;
//     set<string> visited;
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
//         vector<string> oneStudentData;
//         string temp = "";
//         int colId = 0;
//         //cout<<line<<endl;
//         for(int i=0;i<line.size();i++){
//             if(line[i] == ','){
//                 oneStudentData.push_back(temp);
//                 //cout<<temp<<endl;
//                 temp = "";
//                 colId++;
//             }
//             else{
//                 temp += line[i];
//             }
//         }
//         oneStudentData.push_back(temp);
//         studentData.push_back(oneStudentData);
//     }
//     return make_pair(colPlace,studentData);
// }

// void printData(vector<vector<string>> data){
//     for(int i=0;i<data.size();i++){
//         for(int j=0;j<data[i].size();j++){
//             cout<<data[i][j]<<" ";
//         }
//         cout<<endl;
//     }
// }

int main(){

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
    
    matrix["MSME"]["GEN"] = 1;
    matrix["MSME"]["OBC"] = 1;
    matrix["MSME"]["SC"] = 1;
    matrix["MSME"]["ST"] = 1;

    Project::Project p;
    p.setBaseFileSeatMatrix("/home/sujeeth/project_graph/SWE/modCOAP.csv",matrix);

    // first round
    p.sortData();

    p.printCurrState();

    p.addRound();

    // round two
    p.sortData("/home/sujeeth/project_graph/SWE/COAP_resp.csv");

    p.printCurrState();

    p.addRound();

    // round three
    p.sortData("/home/sujeeth/project_graph/SWE/COAP_resp_2.csv");

    p.printCurrState();

    // pair<map<string,int>,vector<vector<string>>> s = loadStudent("/home/sujeeth/project_graph/SWE/modCOAP.csv");
    
    // int tolCols = s.first.size();
    // s.first["offer"] = tolCols;
    // s.first["priority"] = tolCols+1;

    // map<string,int> studentColPlace = s.first;
    // vector<vector<string>> studentData = s.second;
    // for(int i=0;i<studentData.size();i++){
    //     studentData[i].push_back("No Offer");
    //     studentData[i].push_back("0");
    // }

    // printData(studentData);
    // cout<<endl;
    // for(auto it=studentColPlace.begin();it!=studentColPlace.end();it++){
    //     cout<<it->first<<": "<<it->second<<endl;
    // }

    // SeatMatrix m(matrix);
    // map<string,vector<string>> studentPriority;
    // // hard coded for now!!!! how to not is still a doubt??
    // for(auto stud : studentData){
    //     if(stud.at(studentColPlace["specialization_desc_1"]).size() > 0)
    //     studentPriority[stud.at(studentColPlace["applicant_id"])].push_back(stud.at(studentColPlace["specialization_desc_1"]));
    //     if(stud.at(studentColPlace["specialization_desc_2"]).size() > 0)
    //     studentPriority[stud.at(studentColPlace["applicant_id"])].push_back(stud.at(studentColPlace["specialization_desc_2"]));
    //     if(stud.at(studentColPlace["specialization_desc_3"]).size() > 0)
    //     studentPriority[stud.at(studentColPlace["applicant_id"])].push_back(stud.at(studentColPlace["specialization_desc_3"]));
    //     if(stud.at(studentColPlace["specialization_desc_4"]).size() > 0)
    //     studentPriority[stud.at(studentColPlace["applicant_id"])].push_back(stud.at(studentColPlace["specialization_desc_4"]));
    //     if(stud.at(studentColPlace["specialization_desc_5"]).size() > 0)
    //     studentPriority[stud.at(studentColPlace["applicant_id"])].push_back(stud.at(studentColPlace["specialization_desc_5"]));
    // }
    // for(auto it = studentPriority.begin();it!=studentPriority.end();it++){
    //     cout<<it->first<<": ";
    //     for(int i = 0;i<it->second.size();i++){
    //         cout<<it->second[i]<<" ";
    //     }
    //     cout<<endl;
    // }

    // // Rule::Rule<string>* currRule = new GateScoreRule();

    // sort(studentData.begin(),studentData.end(),Comparator());

    // printData(studentData); 
    // cout<<endl;   
    // //add cols to student data
    // cout<<"Before seat allocation:::::\n";
    // m.printSeats();

    // vector<vector<string>> results;
    // for(auto& row : studentData){
    //     string id = row[studentColPlace["applicant_id"]];
    //     string name = row[studentColPlace["full_name"]];
    //     string stud_cat = row[studentColPlace["category"]];
    //     vector<string> specs = studentPriority[row[studentColPlace["applicant_id"]]];
    //     for(auto spec : specs){
    //         string row_cat = "",row_spec = "";
    //         string temp = "";
    //         for(int i=0;i<row[studentColPlace["offer"]].size();i++){
    //             if(row[studentColPlace["offer"]][i] == ','){
    //                 row_spec = temp;
    //                 temp = "";
    //             }
    //             else
    //                 temp += row[studentColPlace["offer"]][i];
    //         }
    //         row_cat = temp;
    //         if(spec == row_spec){  //if there is an offer from previous round then don't go further in priority
    //             results.push_back(vector<string>{id,name,row_spec,row_cat});
    //             break;
    //         }
    //         if(m.getSeats(spec,"GEN") != 0){
    //             m.deleteSeats(spec,"GEN",1);
    //             if(row[studentColPlace["offer"]] != "No Offer"){
    //                 m.addSeats(row_spec,row_cat,1);
    //             }
    //             results.push_back(vector<string>{id,name,spec,"GEN"});
    //             row[studentColPlace["offer"]] = spec+","+"GEN";
    //             break;
    //         }
    //         else if(m.getSeats(spec,stud_cat) != 0){
    //             m.deleteSeats(spec,stud_cat,1);
    //             if(row[studentColPlace["offer"]] != "No Offer"){
    //                 m.addSeats(row_spec,row_cat,1);
    //             }
    //             results.push_back(vector<string>{id,name,spec,stud_cat});
    //             row[studentColPlace["offer"]] = spec+","+stud_cat;
    //             break;
    //         }
    //     }
    // }

    // cout<<"After seat allocation:::::\n";
    // m.printSeats();

    // cout<<endl;
    // printData(studentData);

    // cout<<"\n"<<"Offers handed out\n";
    // for(auto res : results){
    //     for(auto col : res){
    //         cout<<col<<"\t";
    //     }
    //     cout<<endl;
    // }

    // pair<map<string,int>,vector<vector<string>>> c = loadStudent("/home/sujeeth/project_graph/SWE/COAP_resp.csv");
    
    // map<string,int> coapColPlace = c.first; 
    // vector<vector<string>> coapData = c.second;

    // for(auto it=coapColPlace.begin();it!=coapColPlace.end();it++){
    //     cout<<it->first<<": "<<it->second<<endl;
    // }
    // cout<<endl;
    // printData(coapData);
    // cout<<endl;
    


    // vector<vector<string>> offeredStudents;
    // for(auto row : coapData){
    //     string id = row[coapColPlace["MTech Application No"]];
    //     string name = row[coapColPlace["Applicant Name"]];
    //     string category = row[coapColPlace["Offered Category"]];
    //     string spec = row[coapColPlace["Program Offered"]];
    //     string decision = row[coapColPlace["Applicant Decision"]];
    //     if(decision == "Accept and Freeze"){
    //         for(int i=0;i<studentData.size();i++){
    //             if(studentData[i][studentColPlace["applicant_id"]] == id){
    //                 offeredStudents.push_back(vector<string>{id,name,spec,category});
    //                 studentData.erase(studentData.begin()+i);
    //                 break;
    //             }
    //         }
    //     }
    //     else if(decision == "Retain and Wait"){
    //         continue;
    //     }
    //     else if(decision == "Reject and Wait"){
    //         for(int i=0;i<studentData.size();i++){
    //             if(studentData[i][studentColPlace["applicant_id"]] == id){
    //                 studentData[i][studentColPlace["offer"]] = "No Offer";
    //                 m.addSeats(spec,category,1);
    //                 for(int i=0;i<studentPriority[id].size();i++){
    //                     if(studentPriority[id][i] == spec){
    //                         studentPriority[id].erase(studentPriority[id].begin()+i,studentPriority[id].end());
    //                         break;
    //                     }
    //                 }
    //                 break;
    //             }
    //         }
    //     }
    //     else{
    //         // generate an error
    //     }
    // }

    // cout<<"After coap response:::::\n";
    // m.printSeats();

    // cout<<"\n"<<" Final Offered Students::::\n";
    // for(auto student:offeredStudents){
    //     for(auto col:student){
    //         cout<<col<<"\t";
    //     }
    //     cout<<endl;
    // }

    // cout<<endl;
    // printData(studentData);

    // cout<<endl;
    // for(auto it = studentPriority.begin();it!=studentPriority.end();it++){
    //     cout<<it->first<<": ";
    //     for(int i = 0;i<it->second.size();i++){
    //         cout<<it->second[i]<<" ";
    //     }
    //     cout<<endl;
    // }
    
    // results.clear();
    // for(auto& row : studentData){
    //     string id = row[studentColPlace["applicant_id"]];
    //     string name = row[studentColPlace["full_name"]];
    //     string stud_cat = row[studentColPlace["category"]];
    //     vector<string> specs = studentPriority[row[studentColPlace["applicant_id"]]];
    //     for(auto spec : specs){
    //         string row_cat = "",row_spec = "";
    //         string temp = "";
    //         for(int i=0;i<row[studentColPlace["offer"]].size();i++){
    //             if(row[studentColPlace["offer"]][i] == ','){
    //                 row_spec = temp;
    //                 temp = "";
    //             }
    //             else
    //                 temp += row[studentColPlace["offer"]][i];
    //         }
    //         row_cat = temp;
    //         if(spec == row_spec){  //if there is an offer from previous round then don't go further in priority
    //             results.push_back(vector<string>{id,name,row_spec,row_cat});
    //             break;
    //         }
    //         if(m.getSeats(spec,"GEN") != 0){
    //             m.deleteSeats(spec,"GEN",1);
    //             if(row[studentColPlace["offer"]] != "No Offer"){
    //                 m.addSeats(row_spec,row_cat,1);
    //             }
    //             results.push_back(vector<string>{id,name,spec,"GEN"});
    //             row[studentColPlace["offer"]] = spec+","+"GEN";
    //             break;
    //         }
    //         else if(m.getSeats(spec,stud_cat) != 0){
    //             m.deleteSeats(spec,stud_cat,1);
    //             if(row[studentColPlace["offer"]] != "No Offer"){
    //                 m.addSeats(row_spec,row_cat,1);
    //             }
    //             results.push_back(vector<string>{id,name,spec,stud_cat});
    //             row[studentColPlace["offer"]] = spec+","+stud_cat;
    //             break;
    //         }
    //     }
    // }
    // cout<<"\n"<<"Offers handed out in round 2\n";
    // for(auto res : results){
    //     for(auto col : res){
    //         cout<<col<<"\t";
    //     }
    //     cout<<endl;
    // }

    // c = loadStudent("/home/sujeeth/project_graph/SWE/COAP_resp_2.csv");
    
    // coapColPlace = c.first; 
    // coapData = c.second;

    // for(auto it=coapColPlace.begin();it!=coapColPlace.end();it++){
    //     cout<<it->first<<": "<<it->second<<endl;
    // }
    // cout<<endl;
    // printData(coapData);
    // cout<<endl;
    

    // for(auto row : coapData){
    //     string id = row[coapColPlace["MTech Application No"]];
    //     string name = row[coapColPlace["Applicant Name"]];
    //     string category = row[coapColPlace["Offered Category"]];
    //     string spec = row[coapColPlace["Program Offered"]];
    //     string decision = row[coapColPlace["Applicant Decision"]];
    //     if(decision == "Accept and Freeze"){
    //         for(int i=0;i<studentData.size();i++){
    //             if(studentData[i][studentColPlace["applicant_id"]] == id){
    //                 offeredStudents.push_back(vector<string>{id,name,spec,category});
    //                 studentData.erase(studentData.begin()+i);
    //                 break;
    //             }
    //         }
    //     }
    //     else if(decision == "Retain and Wait"){
    //         continue;
    //     }
    //     else if(decision == "Reject and Wait"){
    //         for(int i=0;i<studentData.size();i++){
    //             if(studentData[i][studentColPlace["applicant_id"]] == id){
    //                 studentData[i][studentColPlace["offer"]] = "No Offer";
    //                 m.addSeats(spec,category,1);
    //                 for(int i=0;i<studentPriority[id].size();i++){
    //                     if(studentPriority[id][i] == spec){
    //                         studentPriority[id].erase(studentPriority[id].begin()+i,studentPriority[id].end());
    //                         break;
    //                     }
    //                 }
    //                 break;
    //             }
    //         }
    //     }
    //     else{
    //         // generate an error
    //     }
    // }

    // cout<<"After coap response:::::\n";
    // m.printSeats();

    // cout<<"\n"<<"Final Offered Students::::::\n";
    // for(auto student:offeredStudents){
    //     for(auto col:student){
    //         cout<<col<<"\t";
    //     }
    //     cout<<endl;
    // }

    // cout<<endl;
    // printData(studentData);

    // cout<<endl;
    // for(auto it = studentPriority.begin();it!=studentPriority.end();it++){
    //     cout<<it->first<<": ";
    //     for(int i = 0;i<it->second.size();i++){
    //         cout<<it->second[i]<<" ";
    //     }
    //     cout<<endl;
    // }

    // results.clear();
    // for(auto& row : studentData){
    //     string id = row[studentColPlace["applicant_id"]];
    //     string name = row[studentColPlace["full_name"]];
    //     string stud_cat = row[studentColPlace["category"]];
    //     vector<string> specs = studentPriority[row[studentColPlace["applicant_id"]]];
    //     for(auto spec : specs){
    //         string row_cat = "",row_spec = "";
    //         string temp = "";
    //         for(int i=0;i<row[studentColPlace["offer"]].size();i++){
    //             if(row[studentColPlace["offer"]][i] == ','){
    //                 row_spec = temp;
    //                 temp = "";
    //             }
    //             else
    //                 temp += row[studentColPlace["offer"]][i];
    //         }
    //         row_cat = temp;
    //         if(spec == row_spec){  //if there is an offer from previous round then don't go further in priority
    //             results.push_back(vector<string>{id,name,row_spec,row_cat});
    //             break;
    //         }
    //         if(m.getSeats(spec,"GEN") != 0){
    //             m.deleteSeats(spec,"GEN",1);
    //             if(row[studentColPlace["offer"]] != "No Offer"){
    //                 m.addSeats(row_spec,row_cat,1);
    //             }
    //             results.push_back(vector<string>{id,name,spec,"GEN"});
    //             row[studentColPlace["offer"]] = spec+","+"GEN";
    //             break;
    //         }
    //         else if(m.getSeats(spec,stud_cat) != 0){
    //             m.deleteSeats(spec,stud_cat,1);
    //             if(row[studentColPlace["offer"]] != "No Offer"){
    //                 m.addSeats(row_spec,row_cat,1);
    //             }
    //             results.push_back(vector<string>{id,name,spec,stud_cat});
    //             row[studentColPlace["offer"]] = spec+","+stud_cat;
    //             break;
    //         }
    //     }
    // }
    // cout<<"\n"<<"Offers handed out in round 3\n";
    // for(auto res : results){
    //     for(auto col : res){
    //         cout<<col<<"\t";
    //     }
    //     cout<<endl;
    // }

    return 0;
}
