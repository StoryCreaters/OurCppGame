#include "GameItem.h"
#include "Settings.h"
#include <string>
#include "PropLayer.h"
#include "../view/GameScene.h"
// TODO : figure out how to deal with derived create
GameItem* GameItem::createWithType(GameItem::ItemTools type) {
    return GameItem::create(type);
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
}

GameItem* GameItem::create(GameItem::ItemTools type)
{
    GameItem* player = new GameItem();
    if(player && player->initWithPlayerType(type))
    {
        player->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(player);
    }
    return player;
}

//PropItem* create(GameItem::ItemTools type) {
//    auto player = new PropItem();
//    if(player && player->initWithPlayerType(type))
//    {
//        player->autorelease();
//    }
//    else
//    {
//        CC_SAFE_DELETE(player);
//    }
//    return player;
//}

bool GameItem::initWithPlayerType(GameItem::ItemTools type)
{
    using namespace settings::Items;
    // 记住加入png
    this->initWithSpriteFrameName(std::string(settings::Items::ItemNames[type]) + "_01.png");
    this->type = type;
    return true;
}

// 可以作为虚函数，不同的道具触发不同的getItem
void GameItem::getItem(character* chara) {
    if (type == GameItem::POPO) {
        if (chara->_currentBubbles != chara->_maxBubbles) {
            ++(chara->_currentBubbles);
        }
    } else if (type == GameItem::POWER) {
        if (chara->_currentPower != chara->_maxPower) {
            ++(chara->_currentPower);
        }
    } else if (type == GameItem::RUN) {
        if (chara->_currentVelocity != chara->_maxVelocity) {
            ++(chara->_currentVelocity);
        }
    } else if (type == GameItem::MAXPOWER) {
        chara->_currentPower = chara->_maxPower;
    } else {
        auto prop_layer = dynamic_cast<PropLayer*>(GameScene::getCurrentMap()->getChildByName("PropLayer"));
        if (prop_layer == nullptr) {
            //log("呜呜呜");
        }
        prop_layer->addProp(static_cast<int>(type) - 4);
    }
}




