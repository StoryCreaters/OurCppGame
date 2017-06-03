#include "PlayerController.h"
#include "GameScene.h"
#include "model/Character.cpp"
#include "Settings.h"

USING_NS_CC;

static inline character* getMyplayer() {
    auto scene = GameScene::getCurrentMap();
    return dynamic_cast<character*>(scene->getChildByName("myplayer"));
}

// on "init" you need to initialize your instance
bool PlayerController::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    // add listenner
    initListenner();
    
    
    return true;
}

void PlayerController::initListenner() {
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(PlayerController::myKeyboardPressed, this);
    listener->onKeyReleased = CC_CALLBACK_2(PlayerController::myKeyboardOff, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
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
        _myplayer->changeState(std::make_shared<CharMove>(code));
    }
}

void PlayerController::myKeyboardOff(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    enum T {
        GO_CODE, BUBBLE_CODE
    } code;
    code = GO_CODE;     //默认为go_code
    auto mychara = getMyplayer();
    switch (keyCode) {
        case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
        case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
        case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
        case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
            mychara->changeState(std::make_shared<CharStand>());
    }
}
