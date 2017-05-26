// 准备开始游戏的界面
#ifndef ToStart_hpp
#define ToStart_hpp

#include "cocos2d.h"

class ToStart : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    // implement the "static create()" method manually
    
    CREATE_FUNC(ToStart);
};



#endif /* ToStart_hpp */
