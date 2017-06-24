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
        return "roomselect " + digit;
    }
    
    // character select 中，有chat / start
    static std::string CharSelect(const std::string & s) {
        // 场景中负责聊天
        return "playerselect " + s;
    }
    
    static std::string OnGame(const std::string &recv) {
        if (recv[0] == 'u') {
            cocos2d::log("%s", recv.c_str());
        }
        return "ongame " + recv;
    }
};

#endif /* MessageDispatcher_hpp */
