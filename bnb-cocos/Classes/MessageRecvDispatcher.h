#ifndef MessageRecvDispatcher_hpp
#define MessageRecvDispatcher_hpp

#include "WebClient.h"
#include "RoomChooseScene.h"
#include "SceneManager.h"
#include "LoginScene.h"
#include "ChatBox.h"
#include "GameScene.h"

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
        log("room select : %s", digit.c_str());
        if (digit[0] == 'j') {
            SceneManager::toCharaSelect();
        }
        int rooms[4];
        std::stringstream sin(digit);
        for (int i = 0; i <= 4; i++) {
            sin >> rooms[i];
        }
        RoomChoose::getRoomChooseScene()->changeRooms(rooms);
    }
    
    static std::string CharSelect(const std::string &recv) {
        std::stringstream sin(recv);
        std::string parse;
        sin >> parse;
        if (parse == "chat") {
            std::string name, msg;
            sin >>name;
            std::getline(sin, msg);
            ChatBox::getChatBox()->addChatLine(name, msg);
        } else if (parse == "start") {
            int digits;     //人数
            sin >> digits;
            std::string chara;
            int pos, type;
            std::map<std::string, std::pair<int, int>> name2pair_pos_type;
            for (int i = 0; i < digits; ++i) {
                sin >> chara;
                sin >> pos >> type;
                name2pair_pos_type[chara] = std::make_pair(pos, type - 1);
                log("chara data:%s %d %d", chara.c_str(), pos, type);
            }
            
            auto scene = GameScene::createSceneWithMap(name2pair_pos_type);
            Director::getInstance()->replaceScene(scene);
            WebClient::getInstance()->cur_state = WebClient::ONGAME;
        }
    }
    
    static std::string OnGame(const std::string &recv) {
        
    }
};
#endif /* MessageRecvDispatcher_hpp */
