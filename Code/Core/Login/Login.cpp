#include "Login.h"
using namespace std;

Login *Login ::loginInstance = NULL;

bool Login::checkCredentials(string userName, string password) {
  fstream logFile("log.json", ios::in | ios::out);
  string json((istreambuf_iterator<char>(logFile)), istreambuf_iterator<char>());
  rapidjson::Document doc;
  bool auth = false;

  doc.Parse(json.c_str());
  if (doc.HasParseError()) {
    cerr << "Error parsing JSON: " << doc.GetParseError() << endl;
    return 1;
  }

  for (auto &entry : doc["validUsers"].GetArray()) {
    if (entry.MemberBegin()->name.GetString() == userName) {
      if (entry.MemberBegin()->value.GetString() == password) {
        auth = true;
      }
      break;
    }
  }
  return auth;
}

int main() {
  Login *l = Login::getInstance();
  cout << l->checkCredentials("Sujeth", "1234") << endl;
}