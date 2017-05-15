#include "Character.h"
#include "Settings.h"

using namespace settings::Character;

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

//    _sprite_width = character_x[type];
//    _sprite_height = character_y[type];
    
    _animation_frames = animation_frames[type];
    
    // 记住加入png
    this->initWithSpriteFrameName("player" + std::to_string(type + 1) + "_down_01.png");
    this->initWithFile(sprite_paths[type]);
    return true;
}

cocos2d::Vec2 character::get_collision_ld() {
    auto pos = this->getPosition();
    auto x = pos.x, y = pos.y;
    x -= grid_size / 2;
    y -= grid_size / 2;
    return cocos2d::Vec2(x, y);
}
cocos2d::Vec2 character::get_collision_rd() {
    auto pos = this->getPosition();
    auto x = pos.x, y = pos.y;
    x += grid_size / 2;
    y -= grid_size / 2;
    return cocos2d::Vec2(x, y);
}
cocos2d::Vec2 character::get_collision_lu() {
    auto pos = this->getPosition();
    auto x = pos.x, y = pos.y;
    x -= grid_size / 2;
    y += grid_size / 2;
    return cocos2d::Vec2(x, y);
}
cocos2d::Vec2 character::get_collision_ru() {
    auto pos = this->getPosition();
    auto x = pos.x, y = pos.y;
    x += grid_size / 2;
    y += grid_size / 2;
    return cocos2d::Vec2(x, y);
}

// 根据方向给出一对碰撞点
std::pair<cocos2d::Vec2, cocos2d::Vec2> character::get_collection_point(int direction) {
    /*
     in:direction, 0->up, 1->down, 2->left, 3->right
     out: collection point(2)
     */
    
    using namespace cocos2d;
    auto cur_pos = this->getPosition();
    switch (direction) {
        case 0:
            return std::make_pair(Vec2(little_grid_size / 2 + cur_pos.x, grid_size / 2+ cur_pos.y), Vec2(-little_grid_size / 2 + cur_pos.x, grid_size / 2 + cur_pos.y));
        case 1:
            return std::make_pair(Vec2(little_grid_size / 2 + cur_pos.x, -grid_size / 2 + cur_pos.y), Vec2(-little_grid_size / 2 + cur_pos.x, -grid_size / 2 + cur_pos.y));
        case 2:
            return std::make_pair(Vec2(-grid_size / 2 + cur_pos.x, -little_grid_size / 2 + cur_pos.y), Vec2(-grid_size / 2 + cur_pos.x, -little_grid_size / 2 + cur_pos.y));
        case 3:
            return std::make_pair(Vec2(grid_size / 2 + cur_pos.x, -little_grid_size / 2 + cur_pos.y), Vec2(grid_size / 2 + cur_pos.x, -little_grid_size / 2 + cur_pos.y));
    }
}

