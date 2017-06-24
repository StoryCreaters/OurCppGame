#include "SceneManager.h"
#include "GameScene.h"
#include "LoginScene.h"
#include "CharacterSelect.h"
#include "RoomChooseScene.h"
#include "WebClient.h"
#include "OpenScene.h"

USING_NS_CC;

void SceneManager::toGameScene() {
    WebClient::getInstance()->cur_state = WebClient::ONGAME;
    Director::getInstance()->replaceScene(GameScene::createScene());
}
void SceneManager::toLoginScene() {
    WebClient::getInstance()->cur_state = WebClient::LOGIN_SCENE;
    Director::getInstance()->replaceScene(LoginScene::createScene());
}
void SceneManager::toCharaSelect() {
    WebClient::getInstance()->cur_state = WebClient::CHARACTER_SELECT;
    Director::getInstance()->replaceScene(Players::createScene());
    
}
void SceneManager::toRoomSelect() {
    WebClient::getInstance()->cur_state = WebClient::ROOM_SELECT;
    Director::getInstance()->replaceScene(RoomChoose::createScene());
}

void toStartScene() {
    WebClient::getInstance()->cur_state = WebClient::LOGIN_SCENE;
    Director::getInstance()->replaceScene(OpenScene::createScene());
}
