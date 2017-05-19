#include "CharacterFSM.h"
#include "CommonUse.h"
#include "GameScene.h"
#include "Character.h"

USING_NS_CC;

void CharStandState::excute(cocos2d::Sprite* spr) {
    spr->stopAllActions();
}

void CharMoveState::excute(cocos2d::Sprite* spr) {
    // animation of run
    auto cur_char = dynamic_cast<class character*>(spr);
    std::string next_direction(cur_char->_spriteName + "_"+ std::string(settings::GameScene::direc_string[direc]) +"_");
    auto anime = getAnimationByName(next_direction, 0.1f, cur_char->_animation_frames);
    auto animate = Animate::create(anime);
    auto player_action = RepeatForever::create(animate);
    cur_char->runAction(player_action);
    // move
}
