#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include "../../Libraries/rapidjson/include/rapidjson/document.h"
#include "../../Libraries/rapidjson/include/rapidjson/writer.h"
#include "../../Libraries/rapidjson/include/rapidjson/filereadstream.h"
#include "../../Libraries/rapidjson/include/rapidjson/filewritestream.h"
using namespace std;

string LOG = "log.txt";

class Login {  //Singleton class
    private: 
        string userName;
        string hashedPassword;
        //User* currUser;
        uint lastRegisteredUser;
        fstream logFile;
        static Login* loginInstance; //making Login as a singleton class
        //private constructor
        Login() : logFile("log.json",ios::in | ios::out){
            //loginInstance = NULL;
            userName = "";
            hashedPassword = "";
            lastRegisteredUser = 0;
        }
    protected:
    public:
        //Login(const Login& obj) = delete; //deleting copy constructor
        static Login* getInstance(){
            if (loginInstance == NULL){
                loginInstance = new Login();
                return loginInstance;
            }
            else{
                return loginInstance;
            }
        }
        //void setValues(string uname,string pwd,User currUser);
        bool checkCredentials(string uname, string pwd);
        //User& registerUser();
        void logout();
        ~Login();
        //void checkSystemHealth(weak_ptr<MetaSystemHandler>);
};