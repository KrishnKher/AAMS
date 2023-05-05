#include "User.h"
using namespace std;

// SEE TRY, CATCH, THROW AND HOW TO HANDLE MEMORY EXCEPTIONS!!

  bool User::User::configureUserID(uint32_t userID) { this->userID = userID; return true; }
  uint32_t User::User::fetchUserID() {return this->userID; }

  bool User::User::configureUserName(std::string userName) { this->userName = userName; return true; }
  std::string User::User::fetchUserName() { return this->userName; }

  bool User::User::configureUserLanguage(std::string userLanguage) { this->userLanguage = userLanguage; return true; }
  std::string User::User::fetchUserLanguage() { return this->userLanguage; }

  /* bool User::User::configureUserProject() {};*/
  bool User::User::loadUserProject(ProjectWrapper referenceUserProject) { this->userProjectSeneschal = referenceUserProject; return true; }
  User::ProjectWrapper User::User::fetchUserProject() { return this->userProjectSeneschal; }

  /* bool User::User::configureUserTheme() {};*/
  bool User::User::loadUserTheme(ThemeWrapper referenceUserTheme) { this->userThemeSeneschal = referenceUserTheme; return true; }
  User::ThemeWrapper User::User::fetchUserTheme() { return this->userThemeSeneschal; }



  /* ProjectWrapper(const ProjectWrapper& referenceProject);*/
  /* ProjectWrapper(ProjectWrapper&& project);*/

  bool User::ProjectWrapper::registerProjects(std::vector <std::pair<Project::Project, accessDegree>> unclaimedProjects) {
    for(auto& userProject: unclaimedProjects) {
      this->associatedProjects[userProject.first] = userProject.second;
    }
    return true;
  }

  bool User::ProjectWrapper::registerProjects(std::map <Project::Project, accessDegree> unclaimedProjects) {
    for(auto& userProject: unclaimedProjects) {
      this->associatedProjects[userProject.first] = userProject.second;
    }
    return true;
  }

  bool User::ProjectWrapper::deregisterProjects(std::vector <Project::Project> claimedProjects) {
    for(auto& userProject: claimedProjects) {
      this->associatedProjects.erase(userProject); //What happens to the shared pointer in
    }
    return true;
  }

  std::map <Project::Project, User::accessDegree> User::ProjectWrapper::fetchRegisteredProjects(
                std::vector <shared_ptr<Project::Project>> registeredProjects) {
    std::map <Project::Project, accessDegree> resultProjects;

    for(auto& userProjectPointer: registeredProjects) {
      auto resultProject = this->associatedProjects.find(*userProjectPointer);
      resultProjects[resultProject->first] = resultProject->second;
    }
    return resultProjects;
  }
  std::map <Project::Project, User::accessDegree> User::ProjectWrapper::fetchRegisteredProjects(
                std::vector <Project::Project> registeredProjects) {
    std::map <Project::Project, accessDegree> resultProjects;

    for(auto& userProjectPointer: registeredProjects) {
      auto resultProject = this->associatedProjects.find(userProjectPointer);
      resultProjects[resultProject->first] = resultProject->second;
    }
    return resultProjects;
  }
  std::map <Project::Project, User::accessDegree> User::ProjectWrapper::fetchAllRegisteredProjects() {
    return this->associatedProjects;
  }     

  bool User::ProjectWrapper::openProjects(std::vector<shared_ptr<Project::Project>> requestedProjects) {
    for (auto& projectPointer : requestedProjects) {
      this->activeProjects.insert(projectPointer); // assert?
    }
  }
  bool User::ProjectWrapper::closeProjects(std::vector<shared_ptr<Project::Project>> requestedProjects) {
    for (auto& projectPointer : requestedProjects) {
      this->activeProjects.erase(projectPointer); // assert?
    }
  }

  bool User::ProjectWrapper::openAllProjects() {
    for (auto& projectPointer : this->associatedProjects) {
      std::shared_ptr <Project::Project> activePointer = std::make_shared <Project::Project> (projectPointer.first);
      this->activeProjects.insert(activePointer); // assert?
    }
    return true;
  }

  bool User::ProjectWrapper::closeAllProjects() {
    this->activeProjects.clear();
    return true;
  }

  // std::vector<Project::Project, User::accessDegree> User::ProjectWrapper::fetchAllOpenProjects() {
  //   std::vector<Project::Project, accessDegree> resultProjects;

  //   for(auto setIterator = this->activeProjects.begin(); 
  //           setIterator != this->activeProjects.end(); setIterator++) {
  //           resultProjects.push_back({**setIterator, this->associatedProjects[**setIterator]});
  //         }
  // }

  // std::vector<Project::Project, User::accessDegree> User::ProjectWrapper::fetchAllClosedProjects() {

  // }

  // bool User::ProjectWrapper::configureAccess(std::vector <Project::Project> legacyProjects) {

  // }

  bool User::ProjectWrapper::deleteProject(Project::Project oldProject) {
    this->associatedProjects.erase(oldProject);
    std::shared_ptr oldProjectProxy = make_shared <Project::Project> (oldProject);
    this->activeProjects.erase(oldProjectProxy);
    return true;
  }

  bool User::ProjectWrapper::deleteProject(shared_ptr<Project::Project> oldProject) {
    this->associatedProjects.erase(*oldProject);
    this->activeProjects.erase(oldProject);
    return true;
  }

  bool User::ProjectWrapper::deleteProjects(std::vector <shared_ptr<Project::Project>> requestedProjects) {

    for(auto& oldProject: requestedProjects) {
    this->associatedProjects.erase(*oldProject);
    this->activeProjects.erase(oldProject);
    }
    return true;
  }

  /* ~User::ProjectWrapper::ProjectWrapper() {};*/