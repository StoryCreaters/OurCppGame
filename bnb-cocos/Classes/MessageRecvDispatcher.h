#ifndef MessageRecvDispatcher_hpp
#define MessageRecvDispatcher_hpp

#include "WebClient.h"
#include "RoomChooseScene.h"
#include "SceneManager.h"
#include "LoginScene.h"
#include "ChatBox.h"
#include "GameScene.h"
#include "CharacterFSM.h"

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
            int seed;
            sin >> seed;
            // 一局游戏中 道具的种子
            UserDefault::getInstance()->setIntegerForKey("PropSeed", seed);
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
        log("game recv:%s", recv.c_str());
        std::stringstream sin(recv);
        std::string code;
        sin >> code;
        if(code == "set") {
            // 传入瓦片坐标，在该点释放炸弹
            std::string charaname;
            sin>> charaname;
            auto chara = GameScene::getCurrentMap()->name2chara.at(charaname);
            GameScene::getCurrentMap()->setBubble(chara);
        } else if (code == "state") {
            // 人物状态: 人物 方向 posx posy
            std::string charname;
            int dir;
            float posx, posy;
            sin >> charname >> dir >> posx >> posy;
            auto chara = GameScene::getCurrentMap()->name2chara.at(charname);
            
            chara->setPosition(Vec2(posx, posy));
            log("dir %d", dir);
            if (dir == 5) {
                chara->changeState(std::make_shared<CharStand>());
            } else if (dir < 4) {
                // 状态变小于4
                chara->changeState(std::make_shared<CharMove>(dir));
            }
        }
    }
};
#endif /* MessageRecvDispatcher_hpp */
