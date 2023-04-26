#ifndef USER_H
#define USER_H

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

namespace User{

enum class accessDegree {share, edit, view};

class User {
    private: 
    uint userID;

    std::vector <std::pair<shared_ptr<Project>, accessDegree>> assosciatedProjects;
    std::vector <shared_ptr<Project>> openProjects;

    std::vector <Theme> preferedThemes; // Define theme!!
    protected:
    public:
    User(); 
    User(uint userID);
    User(const User& parentUser);
    User(User&& user);

    bool setUserID(uint userID);
    uint fetchUserID();

    bool registerProjects(std::vector <>);
    bool deregisterProjects();

    Project& createProject();
    bool fetchOpenProjects();
    bool deleteProject(Project& project);

    ~User();
};

class ProjectHandler { // Mediator/Facade pattern?

};

}

#endif USER_H
