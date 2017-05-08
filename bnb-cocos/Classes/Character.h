#ifndef Character_hpp
#define Character_hpp

#include "cocos2d.h"


class character: public cocos2d::Sprite {
public:
    // 显示怪物类型的枚举变量
    // 建立不同的 enemy type
    enum characterType {
        MAPLE_WISH,
        CHRIS,
        SHADOWFOX
    };
    
    bool initWithPlayerType(characterType type);
    
    static character* create(characterType type);

    /*************人物属性，基本属性可以尽量写在配置类里面***************/
    int _maxVelocity;
    int _currentVelocity;
    
    int _maxPower;
    int _currentPower;
    
    int _maxBubbles;
    int _currentBubbles;
    
private:
    // 每个精灵对应的_spriteName
    std::string _spriteName;
    
    
};




#endif /* Character_hpp */
