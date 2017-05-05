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

    int _startVelocity;      // 人物速度
    int _maxVelocity;
    int _currentVelocity;
    
    int _startPower;         // 人物火力
    int _maxPower;
    int _currentPower;
    
    int _startBubbles;       // 水泡数量
    int _maxBubbles;
    int _currentBubbles;
private:
    std::string _spriteName;
};




#endif /* Character_hpp */
