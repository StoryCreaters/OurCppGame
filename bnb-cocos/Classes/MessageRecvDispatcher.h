#ifndef MessageRecvDispatcher_hpp
#define MessageRecvDispatcher_hpp

#include "WebClient.h"
#include "RoomChooseScene.h"

class MessageRecvDispatcher {
public:
    static std::string Login(const std::string &recv) {
        if (recv == "login") {
            Director::getInstance()->replaceScene(RoomChoose::createScene());
        } else {
            
        }
    }
    static std::string RoomSelect(const std::string& digit) {
        
    }
};
#endif /* MessageRecvDispatcher_hpp */
