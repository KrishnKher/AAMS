#include "../../../Core/Login/Login.h"
//#include "../User/User.h"
using namespace std;

int main(){
    Login* l = Login::getInstance();
    cout<<l->checkCredentials("Sujeeth","1234")<<endl;
}
