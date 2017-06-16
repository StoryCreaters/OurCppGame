#pragma once

#include "cocos2d.h"
#include "BnbGameClient.h"
#include "../model/Character.h"

#include <vector>

class character;
class GameClient;

extern "C" GameClient client;

class WebGameScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	~WebGameScene();
	void update(float dt);
	bool checkSyn();
	CREATE_FUNC(WebGameScene);
private:
	

	character * mychara;

};