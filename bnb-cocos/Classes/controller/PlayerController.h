#ifndef PlayerController_hpp
#define PlayerController_hpp

#include "cocos2d.h"

using namespace cocos2d;

class PlayerController: public Layer {
public:
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(PlayerController);
private:
    /*
     * LISTEN keyboard up, down, left, right
     */
    void initListenner();
    void myKeyboardPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void myKeyboardOff(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
};


#endif /* PlayerController_hpp */
