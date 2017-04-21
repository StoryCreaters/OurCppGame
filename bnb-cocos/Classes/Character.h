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
    
private:
    std::string _spriteName;
//    int _velocity;      // 人物速度
//    int _power;         // 人物火力
//    int _bubbles;       // 水泡数量
};




#endif /* Character_hpp */
