#ifndef USER_H
#define USER_H

#include <bits/stdc++.h>

#include <iostream>
using namespace std;

namespace User {

enum class accessDegree { share, edit, view };
using std::pair<shared_ptr<Project>, accessDegree> userProjectData;

constexpr uint kDefaultUserID = 0;
constexpr std::string kDefaultUserName = "User";
constexpr std::string kDefaultUserLanguage = "English";

class User {
 private:
  uint userID;
  std::string userName;
  std::string userLanguage;
  User::Project userProjectSeneschal;
  User::Theme userThemeSeneschal;

 protected:
  friend class User::Project;
  friend class User::Theme;

 public:
  User()
      : userID(kDefaultUserID),
        userName(kDefaultUserName),
        userLanguage(kDefaultUserLanguage){};
  User(uint userID);
  User(const User& parentUser);
  User(User&& user);

  bool configureUserID(uint userID);
  uint fetchUserID();

  bool configureUserName(std::string userName);
  std::string fetchUserName();

  bool configureUserLanguage(std::string userLanguage);
  std::string fetchUserLanguage();

  bool configureUserProject();
  bool loadUserProject(User::Project referenceUserProject);
  User::Project fetchUserProject();

  bool configureUserTheme();
  bool loadUserTheme(User::Theme referenceUserTheme);
  User::Theme fetchUserTheme();

  ~User();
};

class Project {
 private:
  std::vector<userProject> assosciatedProjects;
  std::vector<shared_ptr<Project>> openProjects;

 protected:
 public:
  Project() : assosciatedProjects({}), openProjects({}){};
  Project(const Project& referenceProject);
  Project(Project&& project);

  bool registerProjects(std::vector<userProject> unclaimedProjects);
  bool deregisterProjects(std::vector<userProject> claimedProjects);

  std::vector<shared_ptr<Project>> fetchRegisteredProjects();

  bool openProjects(std::vector<shared_ptr<Project>> requestedProjects);
  bool closeProjects(std::vector<shared_ptr<Project>> requestedProjects);

  std::vector<shared_ptr<Project>> fetchOpenProjects();
  std::vector<shared_ptr<Project>> fetchClosedProjects();

  bool deleteProjects(std::vector<shared_ptr<Project>> requestedProjects);

  ~Project();
};

class Theme {
 private:
  std::vector<int> preferredThemes;  // not actually an int!!
 protected:
 public:
  Theme() : preferredThemes({}){};
  Theme(const Theme& referenceTheme);
  Theme(Theme&& theme);

  ~Theme();
};

}  // namespace User

#endif USER_H
