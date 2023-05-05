#ifndef USER_H
#define USER_H

#include <iostream>
#include <bits/stdc++.h>
#include "../Project/Project.h"
using namespace std;

namespace User {

enum class accessDegree { share, edit, view };

const uint32_t kDefaultUserID = 0;
const std::string kDefaultUserName = "User";
const std::string kDefaultUserLanguage = "English";

class User {
 private:
  uint32_t userID;
  std::string userName;
  std::string userLanguage;
  ProjectWrapper userProjectSeneschal;
  ThemeWrapper userThemeSeneschal;

 protected:
  friend class ProjectWrapper;
  friend class ThemeWrapper;

 public:
  User(uint32_t userID = kDefaultUserID, std::string userName = kDefaultUserName,
      std::string userLanguage = kDefaultUserLanguage)
      : userID(userID),
        userName(userName),
        userLanguage(userLanguage) {};
  /* User(const User& parentUser);*/
  /* User(User&& user);*/

  bool configureUserID(uint32_t userID);
  uint32_t fetchUserID();

  bool configureUserName(std::string userName);
  std::string fetchUserName();

  bool configureUserLanguage(std::string userLanguage);
  std::string fetchUserLanguage();

  /* bool configureUserProject();*/
  bool loadUserProject(ProjectWrapper referenceUserProject);
  ProjectWrapper fetchUserProject();

  /* bool configureUserTheme();*/
  bool loadUserTheme(ThemeWrapper referenceUserTheme);
  ThemeWrapper fetchUserTheme();

  /* ~User();*/
};

struct projectComparator {
  bool operator () (const Project::Project project1, const Project::Project project2) const {
    return true;
  }
};

class ProjectWrapper {
 private:
  std::map <Project::Project, accessDegree, projectComparator> associatedProjects;
  std::set <shared_ptr<Project::Project>> activeProjects;

 protected:
 public:
  ProjectWrapper(std::map <Project::Project, accessDegree, projectComparator> associatedProjects = {}, 
                  std::set <shared_ptr<Project::Project>> activeProjects = {})
  : associatedProjects(associatedProjects), activeProjects(activeProjects) {};
  // ProjectWrapper(std::map <Project::Project, accessDegree> associatedProjects = {}, 
  //                 std::vector <shared_ptr<Project::Project>> openProjects = {})
  // : associatedProjects(associatedProjects) { // do something about open projects
  // };
  /* ProjectWrapper(const ProjectWrapper& referenceProject);*/
  /* ProjectWrapper(ProjectWrapper&& project);*/

  shared_ptr<Project::Project> createProject();

  bool registerProjects(std::vector <std::pair<Project::Project, accessDegree>> unclaimedProjects);
  bool registerProjects(std::map <Project::Project, accessDegree> unclaimedProjects);
  bool deregisterProjects(std::vector <Project::Project> claimedProjects);

  std::map <Project::Project, accessDegree> fetchRegisteredProjects(
                std::vector <shared_ptr<Project::Project>> registeredProjects);
  std::map <Project::Project, accessDegree> fetchRegisteredProjects(
                std::vector <Project::Project> registeredProjects);
  std::map <Project::Project, accessDegree> fetchAllRegisteredProjects();       

  bool openProjects(std::vector<shared_ptr<Project::Project>> requestedProjects);
  bool closeProjects(std::vector<shared_ptr<Project::Project>> requestedProjects);

  bool openAllProjects();
  bool closeAllProjects();

  std::vector <Project::Project, accessDegree> fetchAllOpenProjects();
  std::vector <Project::Project, accessDegree> fetchAllClosedProjects();

  bool configureAccess(std::vector <Project::Project> legacyProjects);

  bool deleteProject(Project::Project oldProject);

  bool deleteProject(shared_ptr <Project::Project> oldProject);

  bool deleteProjects(std::vector <shared_ptr <Project::Project>> requestedProjects);

  ~ProjectWrapper();
};

// Taruvata.
class ThemeWrapper {
 private:
  std::vector<int> preferredThemes;  // not actually an int!!
 protected:
 public:
  ThemeWrapper() : preferredThemes({}){};
  /* Theme(const Theme& referenceTheme);*/
  /* Theme(Theme&& theme);*/

  ~ThemeWrapper();
};

}  // namespace User

#endif USER_H