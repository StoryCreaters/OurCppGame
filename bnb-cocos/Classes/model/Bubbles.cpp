#include "Bubbles.h"
#include "Settings.h"
#include "Character.h"
#include "../view/GameScene.h"

<<<<<<< .merge_file_a94020
USING_NS_CC;
=======

>>>>>>> .merge_file_a91868

bool Bubbles::initWithPower(int power, character* chara) {
    using namespace settings::Bubbles;
    this->setterCharacter = chara;
    this->_power = power;
    this->initWithFile(bubbles_file);
    _collideable = false;
<<<<<<< .merge_file_a94020
=======

>>>>>>> .merge_file_a91868
    this->runAction(Sequence::create(DelayTime::create(0.3),
        CallFuncN::create([=](Ref* sender) {
            _collideable = true;
        }), DelayTime::create(2.7f),
        CallFuncN::create([=](Ref* sender) {
<<<<<<< .merge_file_a94020
            GameScene::getCurrentMap()->BubbleBoom(this);
=======
			GameScene::getCurrentMap()->BubbleBoom(this);
>>>>>>> .merge_file_a91868
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

