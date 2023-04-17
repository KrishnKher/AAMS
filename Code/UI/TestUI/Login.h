
#ifndef LOGIN_H
#define LOGIN_H

#include <iostream>
using namespace std;

class Login {
private:
    static Login *instancePtr;
    Login();

    //Change in final implementation
    string username = "root";
    string password = "root";
public:
    Login(const Login &obj) = delete;
    bool checkStatus(string username, string password);
    static Login* getInstance();
};

#endif // LOGIN_H
