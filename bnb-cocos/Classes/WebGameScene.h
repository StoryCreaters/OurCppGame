#pragma once

#include "cocos2d.h"
#include "Character.h"
#include "BnbGameServer.h"
#include "GameScene.h"

//网络对战需要单机版的加上网络，都是is-a的关系，需要继承两个
/*
*/
class WebGameScene : public GameScene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	//创造角色
	bool addCharacter(float x, float y, character::characterType Type);

	CREATE_FUNC(WebGameScene);
private:
	enum {
		MAX_NUM = 3
	};
	character* _myplayer[MAX_NUM];          //Maybe：改成链表更好
	int _my_bubbles[MAX_NUM];
	static int _cur_player;  

	GameServer server;	 //构造一个服务端，只要一个就行了
	
};