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
    
    /*****碰撞点******/
    // 获取泡泡的碰撞点, l表示左, r表示右, d表示下, u表示上
    cocos2d::Vec2 get_collision_ld();
    cocos2d::Vec2 get_collision_rd();
    cocos2d::Vec2 get_collision_lu();
    cocos2d::Vec2 get_collision_ru();
private:
    // 每个精灵对应的_spriteName
    std::string _spriteName;
    // 人物的身材
    int _sprite_width;
    int _sprite_height;
    
};




#endif /* Character_hpp */
