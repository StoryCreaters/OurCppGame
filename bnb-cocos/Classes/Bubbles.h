#ifndef Bubbles_hpp
#define Bubbles_hpp

#include "cocos2d.h"

class Bubbles: public cocos2d::Sprite {
public:
    // 根据power 初始化bubble
    bool initWithPower(int power);
    static Bubbles* create(int power);

private:
    int _power;
};

#endif /* Bubbles_hpp */
