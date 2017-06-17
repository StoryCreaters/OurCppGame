#pragma once

#include "cocos2d.h"
#include "BnbGameClient.h"
<<<<<<< HEAD
#include <vector>

class GameScene;
class character;

class WebGameScene : public cocos2d::Layer 
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();    
=======
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
>>>>>>> 92e3e854e26c5cd8b58ee13989019241d9a68e0d
	~WebGameScene();
	void update(float dt);
	bool checkSyn();
	CREATE_FUNC(WebGameScene);
private:
<<<<<<< HEAD
	GameClient client;
	character* mychara;
	
=======
	

	character * mychara;

>>>>>>> 92e3e854e26c5cd8b58ee13989019241d9a68e0d
};