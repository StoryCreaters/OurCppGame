#include "Character.h"
#include "Settings.h"
#include "CommonUse.h"
#include "CharacterFSM.h"
#include "GameScene.h"
#include "BubbleController.h"
#include "PlayerController.h"

using namespace settings::Character;
character* character::getMychara() {
    return dynamic_cast<character*>(GameScene::getCurrentMap()->getChildByName("myplayer"));
}

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
    mCurState = std::make_shared<CharNormal>();
    _animation_frames = animation_frames[type];
    curSetBubbles = 0;
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


void character::playStuckedAnimation() {
    runAnimationByName(this, "stuck", 0.5, 4);
}

void character::playDieAnimation() {
    runAnimationByName(this, "die", 0.5, 4);
}
void character::playAliveAnimation() {
    runAnimationByName(this, "alive", 0.5, 4);
}

void character::excute() {
    this->mCurState->excute(this);
}

void character::changeState(std::shared_ptr<State> next_state) {
    this->mCurState = next_state;
    this->mCurState->PreProcess(this);
}

// motiable state of character
void character::setGuard() {
    this->_guard = true;
    auto guard_sprite = Sprite::createWithSpriteFrameName("unit_guard_01.png");
    runAnimationByName(guard_sprite, "unit_guard_", 0.3, 4);
    guard_sprite->setScale(1.15f);
    guard_sprite->setName("guard");
    guard_sprite->setAnchorPoint(Vec2(0.15, -0.2));
    this->addChild(guard_sprite);
    // 使用guard的动作, 而不是sprite的
    guard_sprite->runAction(Sequence::create(DelayTime::create(2.5), CallFuncN::create(
            [=](Ref* sender){
                guard_sprite->removeFromParent();
                this->_guard = false;
             }), NULL));
}

bool character::isGuard() {return _guard;}

void character::powerup() {
    this->runAction(Sequence::create(CallFuncN::create(
          [=](Ref* sender){
              _currentPower = _currentVelocity = _currentBubbles = 8;
          }),
          DelayTime::create(30),
          CallFuncN::create([=](Ref* sender) {
              _currentPower = _maxPower   ,
              _currentVelocity = _maxVelocity,
              _currentBubbles = _maxBubbles;
          }),NULL));
}// 道具-人参果

void character::RideOn() {
    
}
bool character::isRiding() {
    return _isRiding;
}


bool character::isStucked() {
    return typeid(CharStuck).hash_code() == typeid(*mCurState).hash_code();
}

void character::UseNeedle() {
    if (isStucked()) {
        /** resume controller **/
        auto game_scene = GameScene::getCurrentMap();
        // TODO: Change a better way
//        auto controller1 = dynamic_cast<BaseController*>(game_scene->getChildByName("PlayerController"));
//        auto controller2 = dynamic_cast<BaseController*>(game_scene->getChildByName("BubbleController"));
//        controller1->ControllerSetAbled();
//        controller2->ControllerSetAbled();
        auto playerController = PlayerController::create();
        playerController->setName("PlayerController");
        addChild(playerController);
        auto bubbleController = BubbleController::create();
        bubbleController->setName("BubbleController");
        addChild(bubbleController);
        setSpriteFrame(_spriteName + "_down_01.png");
        changeState(std::make_shared<CharStand>());
    }
    
}

void character::rideSpeedUp() {
    // temporary empty
}
