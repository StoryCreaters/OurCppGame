#ifndef SwallowTouch_hpp
#define SwallowTouch_hpp

#include "cocos2d.h"

class SwallowTouch : public cocos2d::LayerColor
{
public:
    SwallowTouch(void);
    ~SwallowTouch(void);
    
    virtual bool init();
    
    CREATE_FUNC(SwallowTouch);
    
    void menuCallBack(cocos2d::Ref* sender);
    
};


#endif /* SwallowTouch_hpp */
