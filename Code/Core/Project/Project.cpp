#include "Project.h"
using namespace std;

Project::Project(string fileName){
    currRoundState = 1;
    baseFilePath = fileName;
    totalRounds.push_back(currRoundState);
    coapResponsePaths.push_back("coap_response_"+to_string(currRoundState));
}

void Project::deleteRound(uint roundNumber){

}

void Project::addRound(){
    totalRounds.push_back(currRoundState + 1);
    coapResponsePaths.push_back("coap_response_"+to_string(currRoundState+1));
}

void Project::preProcessData(uint roundNumber){

}

void Project::sort(){

}