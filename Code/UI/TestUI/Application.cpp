#include "Application.h"

Application::Application() {
    this->loginInstance = Login::getInstance();
}

Login* Application::getLoginInstance() {
    return this->loginInstance;
}
