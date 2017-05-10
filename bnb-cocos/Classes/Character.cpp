#include "Character.h"
#include "Settings.h"

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
    using namespace settings::Character;
    
    // 属性设置
    _spriteName = sprite_names[type];
    
    _maxBubbles = max_bubbles[type];
    _currentBubbles = start_bubbles[type];
    _currentPower = start_powers[type];
    _maxPower = max_powers[type];
    _currentVelocity = start_velocity[type];
    _maxVelocity = max_velocity[type];

    _sprite_width = character_x[type];
    _sprite_height = character_y[type];
    
    this->initWithFile(sprite_paths[type]);
    return true;
}

cocos2d::Vec2 character::get_collision_ld() {
    auto pos = this->getPosition();
    auto x = pos.x, y = pos.y;
    x -= _sprite_width / 2;
    y -= _sprite_height / 2;
    return cocos2d::Vec2(x, y);
}
cocos2d::Vec2 character::get_collision_rd() {
    auto pos = this->getPosition();
    auto x = pos.x, y = pos.y;
    x += _sprite_width / 2;
    y -= _sprite_height / 2;
    return cocos2d::Vec2(x, y);
}
cocos2d::Vec2 character::get_collision_lu() {
    auto pos = this->getPosition();
    auto x = pos.x, y = pos.y;
    x -= _sprite_width / 2;
    y += _sprite_height / 2;
    return cocos2d::Vec2(x, y);
}
cocos2d::Vec2 character::get_collision_ru() {
    auto pos = this->getPosition();
    auto x = pos.x, y = pos.y;
    x += _sprite_width / 2;
    y += _sprite_height / 2;
    return cocos2d::Vec2(x, y);
}

