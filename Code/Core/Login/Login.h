#include <iostream>
#include <bits/stdc++.h>
using namespace std;

namespace Login{
class Login {  //Singleton class
    private: 
        string userName;
        string hashedPassword;
        unique_ptr<User> currUser;
        static unique_ptr<Login> loginInstance; //making Login as a singleton class
        Login() {} //private constructor
    protected:
    public:
        Login(const Login& obj) = delete; //deleting copy constructor
        static unique_ptr<Login> getInstance();
        void setValues(string,string);
        bool checkCredentials(string, string);
        User& createUSer();
        void logout();
        void checkSystemHealth(shared_ptr<MetaSystemHandler>);
};

}
