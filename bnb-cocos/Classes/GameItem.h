// 创建的包含游戏道具的sprite

#ifndef GameItem_hpp
#define GameItem_hpp

#include "cocos2d.h"
#include "Settings.h"
#include "Character.h"

class GameItem: public cocos2d::Sprite {
public:
    // 道具种类及其数量
    enum ItemTools {
        POPO, POWER, RUN
    };
    constexpr static int toolNumbers = 3;
    
    bool initWithPlayerType(ItemTools type);
    static GameItem* create(ItemTools type);
    // 人物得到道具 对不同道具有不同的效果
    virtual void getItem(character* chara);
    
private:
    ItemTools type;
};



#endif /* GameItem_hpp */
