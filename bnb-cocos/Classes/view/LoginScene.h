#ifndef LoginScene_hpp
#define LoginScene_hpp

#include "cocos2d.h"

class LoginScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    void addLogin();
    
    // implemxent the "static create()" method manually
    CREATE_FUNC(LoginScene);
};


#endif /* LoginScene_hpp */
