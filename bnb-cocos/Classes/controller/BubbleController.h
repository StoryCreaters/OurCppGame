#ifndef BubbleController_hpp
#define BubbleController_hpp

#include "BaseController.h"

class BubbleController: public BaseController {
public:
    CREATE_FUNC(BubbleController);
private:
    void myKeyboardPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {}
    void myKeyboardOff(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) override;
};

#endif
