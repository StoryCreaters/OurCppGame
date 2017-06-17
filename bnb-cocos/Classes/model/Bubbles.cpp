#include "Bubbles.h"
#include "Settings.h"
#include "Character.h"
<<<<<<< HEAD
#include "GameScene.h"
=======
#include "../view/GameScene.h"
>>>>>>> 92e3e854e26c5cd8b58ee13989019241d9a68e0d

USING_NS_CC;

bool Bubbles::initWithPower(int power, character* chara) {
    using namespace settings::Bubbles;
    this->setterCharacter = chara;
    this->_power = power;
    this->initWithFile(bubbles_file);
    _collideable = false;
    this->runAction(Sequence::create(DelayTime::create(0.3),
        CallFuncN::create([=](Ref* sender) {
            _collideable = true;
        }), DelayTime::create(2.7f),
        CallFuncN::create([=](Ref* sender) {
            GameScene::getCurrentMap()->BubbleBoom(this);
        }),NULL));
    return true;
}

Bubbles* Bubbles::create(int power, character* setter) {
    auto *bubble = new Bubbles();
    if (bubble && bubble->initWithPower(power, setter)) {
        bubble->autorelease();
        return bubble;
    } else {
        delete bubble;
        bubble = nullptr;
        return nullptr;
    }
}

