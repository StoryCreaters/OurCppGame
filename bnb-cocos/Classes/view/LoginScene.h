#ifndef LoginScene_hpp
#define LoginScene_hpp

#include "cocos2d.h"

USING_NS_CC;

class LoginScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    void addLogin();
    void changeScene();
    
    static LoginScene* getLoginScene() {
        auto layer = dynamic_cast<LoginScene*>(Director::getInstance()->getRunningScene()->getChildByName("LoginScene"));
        assert(layer == nullptr);
        return layer;
    }
    
    // implemxent the "static create()" method manually
    CREATE_FUNC(LoginScene);
};


#endif /* LoginScene_hpp */
