#include "CharacterFSM.h"
#include "CommonUse.h"
#include "GameScene.h"
#include "Character.h"
class GameScene;
USING_NS_CC;

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
    if (chara == dynamic_cast<character*>(game_scene->getChildByTag(20))) {
        game_scene->_eventDispatcher->removeEventListenersForType(EventListener::Type::KEYBOARD);
    }
    chara->stopAllActions();
    chara->playStuckedAnimation();
    chara->runAction(Sequence::create(DelayTime::create(3),CallFuncN::create(
                        [=](Ref* sender) {
                            chara->changeState(std::make_shared<CharDead>());
                        }), NULL));
}
