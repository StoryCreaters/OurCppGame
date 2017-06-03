#ifndef PlayerController_hpp
#define PlayerController_hpp

#include "cocos2d.h"
#include "BaseController.h"

using namespace cocos2d;

class PlayerController: public BaseController {
public:
    CREATE_FUNC(PlayerController);
private:
    void myKeyboardPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) override;
    void myKeyboardOff(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) override;
};


#endif /* PlayerController_hpp */
