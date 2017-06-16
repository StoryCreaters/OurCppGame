#include "BubbleController.h"
#include "../model/Character.h"
#include "../view/GameScene.h"
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
	gameLayer->OnBubble = true;

	if (checkStateWalkAble(mychara))
	{
		Vec2 pos = gameLayer->getPosition();
		gameLayer->setBubble(mychara, pos);
	}
        
	
}
