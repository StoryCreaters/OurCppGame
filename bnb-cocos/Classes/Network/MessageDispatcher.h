#ifndef MessageDispatcher_hpp
#define MessageDispatcher_hpp

#include "WebClient.h"
class MessageDispatcher {
public:
//    template <typename T>
//    static std::string Dispatch(WebClient::GameStates state, const T &arg) {
//        
//    }
    static std::string Login(const std::string &name) {
        return "login " + name;
    }
    static std::string RoomSelect(const std::string& digit) {
        return "selectroom " + digit;
    }
};

#endif /* MessageDispatcher_hpp */
