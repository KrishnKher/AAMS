#include "Login.h"
using namespace std;

Login* Login ::loginInstance = NULL;
int main(){
    Login* l = Login::getInstance();
}