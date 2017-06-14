#ifndef PropController_hpp
#define PropController_hpp

#include "cocos2d.h"
#include "BaseController.h"

class PropController: public BaseController {
public:
    friend class PropItem;
    CREATE_FUNC(PropController);
private:
    void myKeyboardPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) override;
    void myKeyboardOff(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {}
};

#endif /* PropController_hpp */
