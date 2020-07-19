#pragma once
#include <map>
#include <core/header/header.hpp>

typedef struct {
   std::string email;
   std::string password;
   std::string name;
   std::string lastName;   
} UserInformation;

class UserServiceException : public std::exception {
   std::string _message;
public:
   UserServiceException(const std::string & message) : 
                         _message(message) { }
   const char * what() const throw() {
      return _message.c_str();
   }
};
// alias declaration of our In Memory database...
using UserDatabase = std::map<std::string, UserInformation>;
class UserService {
public:
   void signUp(const UserInformation & userInfo)  
        throw(UserServiceException);
   bool signOn(const std::string email, 
               const std::string password, 
               UserInformation & userInfo);
};