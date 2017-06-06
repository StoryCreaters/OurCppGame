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
protected:
    ItemTools type;
};

//// 可使用的道具
//class PropItem : public GameItem {
//public:
//    // CREATE 需要override 一份新的指针
////    static PropItem* create(GameItem::ItemTools type);
//    void getItem(character* chara) override;
//};
//
//// 骑宠
//class RideItem: public GameItem {
//public:
//    void getItem(character* chara) override {log("got RIDE");}
//};
//
//GameItem* ItemFactory(GameItem::ItemTools type) {;
//    if (static_cast<int>(type) < 4) {
//        // 是基础的道具，可以直接写逻辑
//        return GameItem::create(type);
//    } else if (static_cast<int>(type) < 7) {
//        // 是prop, 需要和PropLayer Controller交互
//        log("xxd");
//        return PropItem::create(type);
//    } else {
//        // 是骑宠0.0
//        
//    }
//}

#endif /* GameItem_hpp */
