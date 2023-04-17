
#ifndef UIHANDLER_H
#define UIHANDLER_H

#include <iostream>
#include <QMainWindow>
#include "Application.h"
using namespace std;

class UIHandler: public QMainWindow {
private:
    QMainWindow *ui;
    Application *app;

public:
    UIHandler(QMainWindow *ui = NULL);
    //~UIHandler();

    QMainWindow * getUIPointer();

    void checkLoginStatus(string username, string password);
};

#endif // UIHANDLER_H
