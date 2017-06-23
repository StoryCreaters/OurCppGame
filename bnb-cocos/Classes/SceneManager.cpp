#include "SceneManager.h"
#include "GameScene.h"
#include "LoginScene.h"
#include "CharacterSelect.h"
#include "RoomChooseScene.h"
#include "WebClient.h"

USING_NS_CC;

void SceneManager::toGameScene() {
    Director::getInstance()->replaceScene(GameScene::createScene());
    WebClient::getInstance()->cur_state = WebClient::ONGAME;
}
void SceneManager::toLoginScene() {
    Director::getInstance()->replaceScene(LoginScene::createScene());
}
void SceneManager::toCharaSelect() {
    Director::getInstance()->replaceScene(Players::createScene());
    WebClient::getInstance()->cur_state = WebClient::CHARACTER_SELECT;
}
void SceneManager::toRoomSelect() {
    Director::getInstance()->replaceScene(RoomChoose::createScene());
    WebClient::getInstance()->cur_state = WebClient::ROOM_SELECT;
}
