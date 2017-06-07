#include "CharacterFSM.h"
#include "CommonUse.h"
#include "GameScene.h"
#include "Character.h"
#include "CommonUse.h"
#include "BaseController.h"

class GameScene;
USING_NS_CC;
// for Stuck Controller, set enabled


inline character* getMyplayer() {
    auto scene = GameScene::getCurrentMap();
    return dynamic_cast<character*>(scene->getChildByName("myplayer"));
}

static inline GameScene* getGameScene() {
    auto scene = Director::getInstance()->getRunningScene();
    return dynamic_cast<GameScene*>(scene->getChildByTag(10));
}


void CharNormal::excute(cocos2d::Sprite* spr) {
    auto scene = Director::getInstance()->getRunningScene();
    auto gameScene =  dynamic_cast<GameScene*>(scene->getChildByTag(10));
    if (gameScene == nullptr) {
        return;
    }
    auto chara = dynamic_cast<character*>(spr);
    gameScene->CharacterMove(chara);
    gameScene->checkGetItem(chara);
}

void CharStuck::excute(cocos2d::Sprite* spr) {
    auto chara = dynamic_cast<character*>(spr);
    auto scene = getGameScene();
    if (scene->checkCollisionWithOther(chara)) {
        chara->changeState(std::make_shared<CharDead>());
    }
}

void CharDead::PreProcess(cocos2d::Sprite* spr) {
    auto game_scene = getGameScene();
    spr->stopAllActions();
    auto chara = dynamic_cast<character*>(spr);
    chara->playDieAnimation();
    chara->runAction(Sequence::create(DelayTime::create(3),CallFuncN::create(
                    [=](Ref* sender) {
                        game_scene->RemoveCharacter(chara);
                    }), NULL));
}

void CharStuck::PreProcess(cocos2d::Sprite *spr) {
    auto game_scene = getGameScene();
    auto chara = dynamic_cast<character*>(spr);
    for (auto &dir: chara->_chara_move) {
        dir = false;
    }
    if (chara == dynamic_cast<character*>(game_scene->getChildByTag(20))) {
//        game_scene->_eventDispatcher->removeEventListenersForType(EventListener::Type::KEYBOARD);
//        log("touch disable");
//        auto controller1 = dynamic_cast<BaseController*>(game_scene->getChildByName("PlayerController"));
//        auto controller2 = dynamic_cast<BaseController*>(game_scene->getChildByName("BubbleController"));
//        controller1->ControllerSetEnabled();
//        controller2->ControllerSetEnabled();
        // TODO: change a better way
        game_scene->removeChildByName("PlayerController");
        game_scene->removeChildByName("BubbleController");
        
    }
    chara->stopAllActions();
    chara->playStuckedAnimation();
    chara->runAction(Sequence::create(DelayTime::create(3),CallFuncN::create(
                        [=](Ref* sender) {
                            chara->changeState(std::make_shared<CharDead>());
                        }), NULL));
}

void CharOnRiding::excute(cocos2d::Sprite *spr) {
    static auto scene = Director::getInstance()->getRunningScene();
    static auto gameScene =  dynamic_cast<GameScene*>(scene->getChildByTag(10));
    if (gameScene == nullptr) {
        // get it again
        gameScene =  dynamic_cast<GameScene*>(scene->getChildByTag(10));
        return;
    }
    auto chara = dynamic_cast<character*>(spr);
    gameScene->CharacterMove(chara);
    gameScene->checkGetItem(chara);
}

void CharOnRiding::PreProcess(cocos2d::Sprite *spr) {
    
}


void CharMove::PreProcess(cocos2d::Sprite* spr) {
    auto player = dynamic_cast<character*>(spr);
    player->stopAllActions();
    for (int i = 0; i < 4; ++i) {
        player->_chara_move[i] = false;
    }
    player->_chara_move[direction] = true;
    std::string next_direction(player->_spriteName + "_"+ std::string(settings::GameScene::direc_string[direction]) +"_");
    auto tmp_f = SpriteFrameCache::getInstance()->getSpriteFrameByName(next_direction + "01.png");
    player->setSpriteFrame(tmp_f);
    runAnimationByName(player, next_direction, 0.1f, player->_animation_frames);
}


void CharStand::PreProcess(cocos2d::Sprite* spr) {
    spr->stopAllActions();
}


//TODO : move guard time to
void CharGuard::PreProcess(cocos2d::Sprite* spr) {
    // 护盾模式, 增添护盾动画
    auto guard_sprite = Sprite::createWithSpriteFrameName("unit_guard_01.png");
    runAnimationByName(guard_sprite, "unit_guard_", 0.3, 4);
    guard_sprite->setScale(1.15f);
    guard_sprite->setName("guard");
    guard_sprite->setAnchorPoint(Vec2(0.15, -0.2));
    spr->addChild(guard_sprite);
    spr->runAction(Sequence::create(DelayTime::create(2.5), CallFuncN::create(
        [=](Ref* sender){
            // DEBUG: fsm not change
            log("used here");
            spr->removeChildByName("guard");
            auto chara = dynamic_cast<character*>(spr);
            chara->changeState(std::make_shared<CharNormal>());
        }), NULL));
}

void CharGuard::excute(cocos2d::Sprite *spr) {
    // DEBUG
    log("excute_guard");
}


// check the state of the character
bool checkStateFireAble(character* chara) {
    auto state_chara = typeid(*(chara->mCurState)).hash_code();
    if (state_chara == typeid(CharNormal).hash_code() || state_chara == typeid(CharOnRiding).hash_code() ||
        state_chara == typeid(CharMove).hash_code() || state_chara == typeid(CharStand).hash_code())
        return true;
    return false;
}
bool checkStateWalkAble(character* chara) {
    auto state_chara = typeid(*(chara->mCurState)).hash_code();
    if (checkStateFireAble(chara) || state_chara == typeid(CharGuard).hash_code())
        return true;
    return false;
}
