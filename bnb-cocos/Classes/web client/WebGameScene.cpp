#include "WebGameScene.h"
#include "../view/GameScene.h"
#include "../controller/PlayerController.h"
#include "../controller/CharacterFSM.h"
<<<<<<< HEAD
=======
#include "../view/CharacterSelect.h"
>>>>>>> 92e3e854e26c5cd8b58ee13989019241d9a68e0d
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
<<<<<<< HEAD

	//初始化服务端
	client.init();

	this->schedule(schedule_selector(WebGameScene::update));

	
	return true;
	
}

void WebGameScene::update(float dt) {
	
	client.ClientProcess();
	
=======
	
	//初始化服务端
	//client.init();

	this->schedule(schedule_selector(WebGameScene::update));


	return true;

}

void WebGameScene::update(float dt) {

	client.ClientProcess();

>>>>>>> 92e3e854e26c5cd8b58ee13989019241d9a68e0d
}

bool WebGameScene::checkSyn()
{
	return true;
}

WebGameScene::~WebGameScene()
{
	this->unschedule(schedule_selector(WebGameScene::update)); //取消自定义函数的定时器
}

