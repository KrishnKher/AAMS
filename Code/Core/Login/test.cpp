#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include "../libraries/rapidjson/include/rapidjson/document.h"
#include "../libraries/rapidjson/include/rapidjson/writer.h"
#include "../libraries/rapidjson/include/rapidjson/filereadstream.h"
#include "../libraries/rapidjson/include/rapidjson/filewritestream.h"
using namespace std;

int main(){
    fstream logFile("log.json",ios::in | ios::out);
    string json((istreambuf_iterator<char>(logFile)),
                istreambuf_iterator<char>());
  
    // Create a Document object 
      // to hold the JSON data
    rapidjson::Document doc;
  
    // Parse the JSON data
    doc.Parse(json.c_str());

    if (doc.HasParseError()) {
        cerr << "Error parsing JSON: "
             << doc.GetParseError() << endl;
        return 1;
    }
    cout<<doc["validUsers"].GetArray().FindMember("Sujeeth")->name.GetString()<<endl;
    return 0;
}