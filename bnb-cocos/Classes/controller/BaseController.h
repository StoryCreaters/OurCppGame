#ifndef BaseController_hpp
#define BaseController_hpp

#include "cocos2d.h"
// the base of the controller class
class BaseController: public cocos2d::Layer {
public:
    virtual bool init();
//    CREATE_FUNC(BaseController);
    void initListenner();
protected:
    /*** Listen message from keyboard and others ***/
    virtual void myKeyboardPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) = 0;
    virtual void myKeyboardOff(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) = 0;
};



#endif /* PropLayer_hpp */
