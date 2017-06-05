// 创建的包含游戏道具的sprite

#ifndef GameItem_hpp
#define GameItem_hpp

#include "cocos2d.h"
#include "Settings.h"
#include "Character.h"

using namespace cocos2d;

class GameItem: public cocos2d::Sprite {
public:
    
    // 道具种类及其数量
    enum ItemTools {
        POPO, POWER, RUN, MAXPOWER, NEEDLE, GUARD, UPPER
    };
    constexpr static int toolNumbers = 7;
    
    // 创建道具
    static GameItem* create(ItemTools type);
    static GameItem* createWithType(ItemTools type);
    
    bool initWithPlayerType(ItemTools type);
    
    // 人物得到道具 对不同道具有不同的效果
    virtual void getItem(character* chara);
private:
    ItemTools type;
};

// 可使用的道具
class PropItem : public GameItem {
public:
    void getItem(character* chara) override {log("got prop");}
};

// 骑宠
class RideItem: public GameItem {
public:
    void getItem(character* chara) override {log("got RIDE");}
};


#endif /* GameItem_hpp */
