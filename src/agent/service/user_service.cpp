#include <mutex>
#include "user_service.hpp"

UserDatabase usersDB;
std::mutex usersDBMutex;
void UserService::signUp(const UserInformation & userInfo) throw(UserServiceException) {
   
   std::unique_lock<std::mutex> lock { usersDBMutex };
   if (usersDB.find(userInfo.email) != usersDB.end()) {
      throw UserServiceException("user already exists!");
   }
   usersDB.insert(
      std::pair<std::string, UserInformation>(userInfo.email, 
                                              userInfo));   
}
bool UserService::signOn(const std::string email, 
                         const std::string password, 
                         UserInformation & userInfo) {   
   if (usersDB.find(email) != usersDB.end()) {
      auto ui = usersDB[email];
      if (ui.password == password) {
         userInfo = ui;
         return true;
      }         
   }
   return false;
}