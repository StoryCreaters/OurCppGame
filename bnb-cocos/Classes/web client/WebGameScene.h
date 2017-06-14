#pragma once

#include "cocos2d.h"
#include "BnbGameClient.h"
#include <vector>

class GameScene;
class character;

class WebGameScene : public cocos2d::Layer //必须继承它，部分函数需要重构
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();    
	void update(float dt) override;
	
	//继承的GameScene里面，已经创建了一个_myplayer，该chara在本client操作
	//所以在这里添加的其他chara都是非本client的
	
	CREATE_FUNC(WebGameScene);
private:
	GameClient client;
	character* mychara;
	
};