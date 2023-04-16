#include <iostream>
#include <bits/stdc++.h>
using namespace std;

namespace User{

enum class accessDegree {share, edit, view};

class User {
    private: 
    uint userID;
    std::vector <std::pair<shared_ptr<Project>, accessDegree>> projects;
    std::vector <shared_ptr<Project>> openProjects;
    protected:
    public:
    Project& createProject();
    bool deleteProject();

};

class ProjectHandler { // Mediator pattern?

};

}
