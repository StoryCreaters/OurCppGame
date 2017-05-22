#include "GameItem.h"
#include "Settings.h"
#include <string>

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

bool GameItem::initWithPlayerType(GameItem::ItemTools type)
{
    using namespace settings::Items;
    // 记住加入png
    this->initWithSpriteFrameName(std::string(settings::Items::ItemNames[type]) + "_01.png");
    cocos2d::log("%s", (std::string(settings::Items::ItemNames[type]) + "_01.png").c_str());
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
    }
}
