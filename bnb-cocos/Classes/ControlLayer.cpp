#include "ControlLayer.h"
USING_NS_CC;

//void ControlLayer::myKeyboardOnL(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
//    GameScene::_optionCode key;
//    enum T {
//        GO_CODE, BUBBLE_CODE
//    } code;
//    code = GO_CODE;     //默认为go_code
//    
//    switch (keyCode) {
//        case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
//            key = GameScene::_optionCode::GO_UP;
//            break;
//        case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
//            key = GameScene::_optionCode::GO_DOWN;
//            break;
//        case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
//            key = GameScene::_optionCode::GO_LEFT;
//            break;
//        case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
//            key = GameScene::_optionCode::GO_RIGHT;
//            break;
//        case cocos2d::EventKeyboard::KeyCode::KEY_SPACE:
//            code = BUBBLE_CODE;
//            break;
//        default:
//            break;
//    }
//    
//    if (code == GO_CODE) {
//        _gameScene->_my_sprite_move[key] = false;       //有移动的趋势
//        std::string next_direction(_gameScene->_myplayer->_spriteName + "_"+ std::string(settings::GameScene::direc_string[direction]) +"_");
//        auto tmp_f = SpriteFrameCache::getInstance()->getSpriteFrameByName(next_direction + "01.png");
//        _gameScene->_myplayer->setSpriteFrame(tmp_f);
//        _gameScene->_myplayer->stopAllActions();
//    }
//    else if (code == BUBBLE_CODE) {
//        _gameScene->setBubble();
//        
//    }
//}

//void ControlLayer::myKeyboardOffL(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
//    GameScene::_optionCode code = DEFAULT;
//    switch (keyCode) {
//        case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
//            code = GameScene::_optionCode::GO_UP;
//            break;
//        case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
//            code = GameScene::_optionCode::GO_DOWN;
//            break;
//        case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
//            code = GameScene::_optionCode::GO_LEFT;
//            break;
//        case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
//            code = GameScene::_optionCode::GO_RIGHT;
//            break;
//        default:
//            break;
//    }
//    // DEBUG
//    // TODO:走路可以用状态机实现
//    if (code != DEFAULT) {
//        for (auto &b : _gameScene->_my_sprite_move)     b = false;
//        _gameScene->_my_sprite_move[code] = true;       //有移动的趋势, 防止爆栈
//        direction = code;
//        
//        // animation and direction
//        std::string next_direction(_gameScene->_myplayer->_spriteName + "_"+ std::string(settings::GameScene::direc_string[code]) +"_");
//        auto anime = getAnimationByName(next_direction, 0.1f, _gameScene->_myplayer->_animation_frames);
//        auto animate = Animate::create(anime);
//        auto player_action = RepeatForever::create(animate);
//        _gameScene->_myplayer->runAction(player_action);
//    }
//}
