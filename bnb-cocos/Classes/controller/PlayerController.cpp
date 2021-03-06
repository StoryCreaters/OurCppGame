#include "PlayerController.h"
#include "../view/GameScene.h"
#include "../model/Character.h"
#include "Settings.h"
#include "CharacterFSM.h"

USING_NS_CC;


inline character* getMyplayer() {
    auto scene = GameScene::getCurrentMap();
    return dynamic_cast<character*>(scene->getChildByName("myplayer"));
}

void PlayerController::myKeyboardPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    GameScene::_optionCode code = GameScene::_optionCode::DEFAULT;
    switch (keyCode) {
        case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
            code = GameScene::_optionCode::GO_UP;
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
            code = GameScene::_optionCode::GO_DOWN;
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
            code = GameScene::_optionCode::GO_LEFT;
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
            code = GameScene::_optionCode::GO_RIGHT;
            break;
        default:
            break;
    }
	
    auto _myplayer = getMyplayer();
    if (code != GameScene::_optionCode::DEFAULT) {
		_myplayer->_chara_still = false;
        _myplayer->changeState(std::make_shared<CharMove>(static_cast<int>(code)));
	}
	else {
		_myplayer->_chara_still = true;
	}
}

void PlayerController::myKeyboardOff(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    auto mychara = getMyplayer();
	mychara->_chara_still = true;

    GameScene::_optionCode key;
    switch (keyCode) {
        case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
            key = GameScene::_optionCode::GO_UP;
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
            key = GameScene::_optionCode::GO_DOWN;
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
            key = GameScene::_optionCode::GO_LEFT;
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
            key = GameScene::_optionCode::GO_RIGHT;
            break;
        default:
            return;
    }
    if (typeid(*(mychara->mCurState)).hash_code() == typeid(CharMove).hash_code()) {

        auto realState = dynamic_pointer_cast<CharMove>(mychara->mCurState);
        if (realState->direction == static_cast<int>(key)) {
            // the same direction :stop
            mychara->changeState(std::make_shared<CharStand>());
        }
    }
}
    
