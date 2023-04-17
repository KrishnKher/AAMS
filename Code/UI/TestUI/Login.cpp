#include "Login.h"

Login::Login() {}

Login *Login::instancePtr = NULL;

bool Login::checkStatus(string username, string password) {
    if(username != this->username || password != this->password) {
        return 0;
    } else {
        return 1;
    }
}

Login* Login::getInstance() {
    if(instancePtr == NULL) {
        instancePtr = new Login();
        return instancePtr;
    } else {
        return instancePtr;
    }
}
