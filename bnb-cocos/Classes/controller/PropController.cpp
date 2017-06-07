#include "PropController.h"
#include "PropLayer.h"

// propType in prop layer
//enum PropType {
//    ALLPOWER, NEEDLE, RSPEED, GUARD
//};
// the position is magical
// map:pic->index: 4->1, 3->2, 2->3, 1->4
constexpr int reallIndex[] = {3, 2, 1, 0};

void PropController::myKeyboardPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    auto propLayer = dynamic_cast<PropLayer*>(PropLayer::getPropLayer());
    switch (keyCode) {
        case cocos2d::EventKeyboard::KeyCode::KEY_1:
            propLayer->useProp(reallIndex[0]);
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_2:
            propLayer->useProp(reallIndex[1]);
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_3:
            // DEBUG
            propLayer->useProp(reallIndex[2]);
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_4:
            propLayer->useProp(reallIndex[3]);
            break;
        default:
            break;
    }
}
