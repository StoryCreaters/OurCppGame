#include "WebGameScene.h"
#include "../view/GameScene.h"
#include "../controller/PlayerController.h"
#include "../controller/CharacterFSM.h"
#include <random>

USING_NS_CC;
using namespace settings::GameScene;

static inline GameScene* getGameScene() {
	auto scene = Director::getInstance()->getRunningScene();
	return dynamic_cast<GameScene*>(scene->getChildByTag(10));
}



bool WebGameScene::init()
{
	if (!Layer::init())
	{
		return false;
	}


	//初始化服务端
	client.init();

	this->schedule(schedule_selector(WebGameScene::update),0.15);

	
	return true;
	
}

void WebGameScene::update(float dt) {
	
	client.ClientProcess();

}



