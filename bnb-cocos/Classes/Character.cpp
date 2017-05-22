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
    
    // 初始化运动状态
    last_move = {0, 0};
    last_ops = settings::DEFAULT;
    
    // 属性设置
    _spriteName = sprite_names[type];
    
    _maxBubbles = max_bubbles[type];
    _currentBubbles = start_bubbles[type];
    _currentPower = start_powers[type];
    _maxPower = max_powers[type];
    _currentVelocity = start_velocity[type];
    _maxVelocity = max_velocity[type];
    
    _animation_frames = animation_frames[type];
    
    // 记住加入png
    this->initWithSpriteFrameName("player" + std::to_string(type + 1) + "_down_01.png");
    this->initWithFile(sprite_paths[type]);
    return true;
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

cocos2d::Vec2 character::getMoveVector() {
    using namespace cocos2d;
    const static int basic_step = 2;
    int curstep = _currentVelocity + basic_step;
    Vec2 delta_pos[4] = {Vec2(0, curstep), Vec2(0, -curstep), Vec2(-curstep, 0), Vec2(curstep, 0)};
    for (int i = 0; i < 4; ++i) {
        if (_chara_move[i]) {
            return delta_pos[i];
        }
    }
}

cocos2d::Vec2 character::getMoveVector(int index) {
    using namespace cocos2d;
    const static int basic_step = 2;
    int curstep = _currentVelocity + basic_step;
    Vec2 delta_pos[4] = {Vec2(0, curstep), Vec2(0, -curstep), Vec2(-curstep, 0), Vec2(curstep, 0)};
    return delta_pos[index];
}

