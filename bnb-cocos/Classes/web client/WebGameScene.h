#pragma once

#include "cocos2d.h"
#include "BnbGameClient.h"
#include <vector>

class GameScene;
class character;

class WebGameScene : public cocos2d::Layer 
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();    
	void update(float dt);
	bool checkSyn();
	CREATE_FUNC(WebGameScene);
private:
	GameClient client;
	character* mychara;
	
};