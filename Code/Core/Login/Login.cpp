#include "Login.h"
using namespace std;

class User{
    int a;
};

Login* Login ::loginInstance = NULL;

bool Login::checkCredentials(string uname, string pwd){
    fstream logFile("log.json",ios::in | ios::out);
    string json((istreambuf_iterator<char>(logFile)),istreambuf_iterator<char>());
    rapidjson::Document doc;
    bool auth = false;
    doc.Parse(json.c_str());
    if (doc.HasParseError()) {
        cerr << "Error parsing JSON: "
             << doc.GetParseError() << endl;
        return 1;
    }
    for(auto& x: doc["validUsers"].GetArray()){
        if(x.MemberBegin()->name.GetString() == uname){
            if(x.MemberBegin()->value.GetString() == pwd){
                auth = true;
                return auth;
            }
            else
                return auth;
        }
    }
    return auth;
}

void Login::setValues(string uname,string pwd/*,User& currUser*/){
    userName = uname;
    hashedPassword = pwd;
    //this->currUser = &currUser; 
}

// TO BE DONE
User& Login::registerUser(string uname,string pwd){
    fstream logFile("log.json",ios::in | ios::out);
    string json((istreambuf_iterator<char>(logFile)),istreambuf_iterator<char>());
    rapidjson::Document doc;
    doc.Parse(json.c_str());
    if (doc.HasParseError()) {
        cerr << "Error parsing JSON: "
             << doc.GetParseError() << endl;
        exit(0);
    }
    
}

void Login::logout(){
    //delete currUser; //delete the curr user
    userName = "";
    hashedPassword = "";
}

Login::~Login(){
    delete loginInstance;
}

int main(){
    Login* l = Login::getInstance();
    cout<<l->checkCredentials("Sujeth","1234")<<endl;
}