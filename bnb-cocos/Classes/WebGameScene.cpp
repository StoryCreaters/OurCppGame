#include "WebGameScene.h"
#include "Bubbles.h"
#include "Settings.h"
#include "Character.h"
#include "SimpleAudioEngine.h"
#include "BnbGameServer.h"
#include "CommonUse.h"
#include <random>

USING_NS_CC;
using namespace settings::GameScene;

int WebGameScene::_cur_player;
Scene* WebGameScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = WebGameScene::create();

	// add layer as a child to scene
	scene->addChild(layer);
	
	_cur_player = 0;
	// return the scene
	return scene;
}


// on "init" you need to initialize your instance
bool WebGameScene::init()
{

	if (!Layer::init())
	{
		return false;
	}
	//直接用GameScene初始化啊啊啊啊
	/*
		原来GameScene里面的人物就是玩家！
		这里新加的都是电脑。
	*/
	if (!GameScene::init())
	{
		return false;
	}
	
	server.init();//使用之前必须初始化，里面开始server的监听
	

	//创建新玩家
	addCharacter(100, 100, character::MAPLE_WISH);
	
	return true;
}


bool WebGameScene::addCharacter(float x, float y, character::characterType Type)
{
	if (_cur_player >= MAX_NUM)
	{
		
		return false;
	}
	else
	{
		_myplayer[_cur_player] = character::create(Type);
		_myplayer[_cur_player]->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		_myplayer[_cur_player]->setPosition(offx + x, offy + y);
		addChild(_myplayer[_cur_player], 1);
		_game_players.pushBack(_myplayer[_cur_player]);

		_my_bubbles[_cur_player] = 0;        // bubbles start from 0


		//BUG
		server.ProcessGameServer();//搭建一个新的线程

		_cur_player++;
		return true;
	}
}

