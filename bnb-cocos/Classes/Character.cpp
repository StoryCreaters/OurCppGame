#include "Character.h"


character* character::create(characterType type)
{
    character* player = new character();
    if(player && player->initWithPlayerType(type))
    {
        player->autorelease();
        return player;
    }
    else
    {
        delete player;
        player = NULL;
        return NULL;
    }
}

bool character::initWithPlayerType(characterType type)
{
    // 给不同的角色初始化不同属性
    // 这里只做了一个人物真是抱歉了
    // TODO: 更新人物和属性
    switch(type)
    {
        case MAPLE_WISH:
            _spriteName = "GamePlayer/player1.png";
            _startPower = _startBubbles = _startVelocity = 1;
            break;
        case CHRIS:
            _spriteName = "GamePlayer/player2.png";
            break;
        case SHADOWFOX:
            _spriteName = "GamePlayer/player3.png";
            break;
    }
    this->initWithFile(_spriteName);
    return true;
}

