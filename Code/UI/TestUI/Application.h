
#ifndef APPLICATION_H
#define APPLICATION_H

#include <iostream>
#include "Login.h"
using namespace std;

class Application {
private:
    Login *loginInstance;
public:
    Application();
    Login* getLoginInstance();
};

#endif // APPLICATION_H
