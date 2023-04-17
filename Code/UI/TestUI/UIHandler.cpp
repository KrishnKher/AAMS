#include "UIHandler.h"
#include "Login.h"

UIHandler::UIHandler(QMainWindow *ui) {
    this->ui = ui;
}

QMainWindow * UIHandler::getUIPointer() {
    return this->ui;
}

void UIHandler::checkLoginStatus(string username, string password) {
    bool status = app->getLoginInstance()->checkStatus(username, password);
    if(status) {

    } else {

    }
}
