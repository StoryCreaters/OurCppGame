#ifndef Bubbles_hpp
#define Bubbles_hpp

#include "cocos2d.h"
class character;
class Bubbles: public cocos2d::Sprite {
public:
    // 根据power 初始化bubble
    bool initWithPower(int power, character* setter);
    static Bubbles* create(int power, character* setter);
    int get_power() const {return _power;}
    character* setterCharacter;
private:
    int _power;
};

#endif /* Bubbles_hpp */
