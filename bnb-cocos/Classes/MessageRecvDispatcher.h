#ifndef MessageRecvDispatcher_hpp
#define MessageRecvDispatcher_hpp

#include "WebClient.h"
#include "RoomChooseScene.h"
#include "SceneManager.h"
#include "LoginScene.h"

class MessageRecvDispatcher {
public:
    static std::string Login(const std::string &recv) {
        if (recv == "login") {
            SceneManager::toRoomSelect();
        } else {
            LoginScene::getLoginScene()->nameRepetition();
        }
    }
    static std::string RoomSelect(const std::string& digit) {
        
    }
};
#endif /* MessageRecvDispatcher_hpp */
