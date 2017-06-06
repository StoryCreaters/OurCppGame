#include "PropController.h"
#include "PropLayer.h"

// propType in prop layer
//enum PropType {
//    ALLPOWER, NEEDLE, RSPEED, GUARD
//};

void PropController::myKeyboardPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    auto propLayer = PropLayer::getPropLayer();
    switch (keyCode) {
        case cocos2d::EventKeyboard::KeyCode::KEY_1:
            log("press digit: %d", cocos2d::EventKeyboard::KeyCode::KEY_1);
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_2:
            log("press digit: %d", cocos2d::EventKeyboard::KeyCode::KEY_2);
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_3:
            log("press digit: %d", cocos2d::EventKeyboard::KeyCode::KEY_3);
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_4:
            log("press digit: %d", cocos2d::EventKeyboard::KeyCode::KEY_4);
            break;
        default:
            break;
    }
 
}
