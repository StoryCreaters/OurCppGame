#ifndef Bubbles_hpp
#define Bubbles_hpp

#include "cocos2d.h"
USING_NS_CC;

class character;
class Bubbles: public cocos2d::Sprite {
public:
    // 根据power 初始化bubble

    bool initWithPower(int power, character* setter);
    static Bubbles* create(int power, character* setter);
    int get_power() const {return _power;}
    character* setterCharacter;
    int isCollideable() const {return _collideable;}
private:
    int _power;
    bool _collideable;
};

#endif /* Bubbles_hpp */
