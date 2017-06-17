#include "BubbleController.h"
<<<<<<< HEAD
#include "Character.h"
#include "GameScene.h"
=======
#include "../model/Character.h"
#include "../view/GameScene.h"
>>>>>>> 92e3e854e26c5cd8b58ee13989019241d9a68e0d
#include "CharacterFSM.h"

USING_NS_CC;

inline character* getMyplayer() {
    auto scene = GameScene::getCurrentMap();
    return dynamic_cast<character*>(scene->getChildByName("myplayer"));
}

void BubbleController::myKeyboardOff(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    if (keyCode != EventKeyboard::KeyCode::KEY_SPACE)
        return;
    auto gameLayer = GameScene::getCurrentMap();
    auto mychara = dynamic_cast<character*>(gameLayer->getChildByName("myplayer"));
<<<<<<< HEAD
    if (checkStateWalkAble(mychara))
        gameLayer->setBubble(mychara);
=======
	mychara->_chara_bubble = true;
	Vec2 Pos = mychara->getPosition();
    if (checkStateWalkAble(mychara))
        gameLayer->setBubble(mychara, Pos);
	mychara->_chara_bubble = false;

>>>>>>> 92e3e854e26c5cd8b58ee13989019241d9a68e0d
}
