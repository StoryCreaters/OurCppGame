#ifndef ControlLayer_hpp
#define ControlLayer_hpp

#include "cocos2d.h"
#include "GameScene.h"

class ControlLayer : public cocos2d::Layer
{
public:
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(ControlLayer);
    
    void myKeyboardOnL(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void myKeyboardOffL(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    
private:
//    GameScene* _gameScene;
//    GameScene::_optionCode direction;
};

#endif /* ControlLayer_hpp */
