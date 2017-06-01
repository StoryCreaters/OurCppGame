#include "WebGameScene.h"
#include "Bubbles.h"
#include "Settings.h"
#include "SimpleAudioEngine.h"
#include "CommonUse.h"
#include "Character.h"
#include <random>

USING_NS_CC;
using namespace settings::GameScene;

Scene* WebGameScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = WebGameScene::create();

	// add layer as a child to scene
	scene->addChild(layer);
	
	// return the scene
	return scene;
}


/*
名称：初始化函数
描述：除了初始化GameScene，还需要初始化客户端，然后还需要其他客户端的角色,并且实现控制
*/
bool WebGameScene::init()
{
	if (!Layer::init())
	{
		return false;
	}


	visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	addCloseMenu();

	// a temporary background
	auto backG = Sprite::create(backGroundPicture);
	addChild(backG, -10);
	backG->setPosition(visibleSize / 2);


	/***** tilemap ******/
	_tileMap = TMXTiledMap::create("gameStart/map01.tmx");
	_tileMap->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	_tileMap->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	_tileMap->setScale(settings::GameScene::_tile_delta_rate);

	_meta = _tileMap->getLayer("Unbroken");
	_background = _tileMap->getLayer("Background");
	addChild(_tileMap, -1);

	// 注意坐标位置差
	offx = (visibleSize.width - _tileMap->getContentSize().width * _tile_delta_rate) / 2;
	offy = (visibleSize.height - _tileMap->getContentSize().height * _tile_delta_rate) / 2;
	TMXObjectGroup *objects = _tileMap->getObjectGroup("player");
	CCASSERT(nullptr != objects, "'Objects' object group not found");
	auto spawnPoint = objects->getObject("SpawnPoint1");
	CCASSERT(!spawnPoint.empty(), "SpawnPoint object not found");
	float x = spawnPoint["x"].asFloat() * _tile_delta_rate;
	float y = spawnPoint["y"].asFloat() * _tile_delta_rate;

	tileLoadProps();

	/*** add character***/
	_myplayer = character::create(character::CHRIS);
	_myplayer->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	_myplayer->setPosition(offx + x, offy + y);
	addChild(_myplayer, 1);
	_game_players.pushBack(_myplayer);

	_my_bubbles = 0;        // bubbles start from 0

							// test
							//    addItems(Vec2(10, 10));


							// 键盘监听
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(GameScene::myKeyboardOnL, this);
	listener->onKeyReleased = CC_CALLBACK_2(GameScene::myKeyboardOffL, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	this->scheduleUpdate();



	//初始化服务端
	client.init();


	_other_num = 0;
	//增加成员
	addCharacter(x, y, character::CHRIS);
	



	return true;
}



bool WebGameScene::addCharacter(float x, float y, character::characterType Type)
{
	character* temp = character::create(Type);
	temp->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	temp->setPosition(offx + x, offy + y);
	addChild(temp, 1);
	_game_players.pushBack(temp);

	_other_num++;
	return true;
}


void WebGameScene::update(float dt)
{
	std::ofstream outfile;
	outfile.open("e:\\log2.txt", std::ios::app);
	bool flag = 0;
	for (auto chara : _game_players) {
		
		outfile << "#"<<flag << " ";
		CharacterMove(chara, flag);
		checkGetItem(chara);
		flag = !flag;
	}
	outfile.close();
}

void WebGameScene::CharacterMove(character* chara ,const int FLAG)
{
	
	std::ofstream outfile;
	outfile.open("e:\\log3.txt", std::ios::app);
	outfile << FLAG << " ";

	const static float dur = 0.1f;
	//TODO: 增加边界检测
	// 获得x y 的上界 下界
	const static float lowerx = offx + 3, upperx = visibleSize.width - offx;
	const static float lowery = offy + 3, uppery = visibleSize.height - offy;

	Vector<FiniteTimeAction *> moves;
	auto in_tile_map = [&](Vec2 pos)->bool {
		if (pos.x >= lowerx && pos.x <= upperx)
			if (pos.y >= lowery && pos.y <= uppery)
				return true;
		return false;
	};

	outfile << FLAG << " ";

	const static int basic_step = 2;
	int curstep = chara->_currentVelocity + basic_step;

	// UP, DOWN, LEFT, RIGHT
	Vec2 delta_pos[4]{ Vec2(0, curstep), Vec2(0, -curstep), Vec2(-curstep, 0), Vec2(curstep, 0) };
	// 判断动作，调整step
	// get exact direction and last move
	for (int index = 0; index < 4; ++index) {
		if (!chara->_chara_move[index]) {
			continue;
		}
		Vec2 cur_delta = delta_pos[index];
		auto test_point = cur_delta;
		if (chara->last_ops == index) {
			test_point += chara->last_move;
			chara->last_move += cur_delta;
		}
		else {
			chara->last_move = cur_delta;
			chara->last_ops = static_cast<settings::directions>(index);
		}

		bool walk(true);           // really move?
		auto deltas = chara->get_collection_point(index);
		auto pos1 = deltas.first, pos2 = deltas.second;

		
		

		outfile << FLAG << " ";
		if (FLAG == 0)
		{
			/*
			******************向服务器传递位置信息*******************
			*/
			char sendData[1024];
			ZeroMemory(sendData, sizeof(sendData));
			sprintf(sendData, "%d %d", pos1, pos2);
			int ret = send(client.ClientSocket, sendData, strlen(sendData), 0);
			if (ret <= 0)
			{
				outfile << "发送错误!\n";
			}
			else
				outfile << "发送成功!\n";
			//********************************************************
		}
		else if (FLAG == 1)
		{
			/*
			******************向服务器接受位置信息*******************
			*/
		
			char recvData[1024];
			ZeroMemory(recvData, sizeof(recvData));
			int ret = recv(client.ClientSocket, recvData, sizeof(recvData), 0);
			Vec2 pos_x, pos_y;
			sscanf(recvData, "%d %d", pos_x, pos_y);
			pos1 = pos_x;
			pos2 = pos_y;
			outfile << pos1.x << pos1.y << " "<< pos2.x << pos2.y << std::endl;
			outfile << "接受成功\n";

			//********************************************************
		}
		outfile.close();




		if (!in_tile_map(pos1 + test_point) || !in_tile_map(pos2 + test_point)) {
			chara->last_move = { 0,0 };
			break;
		}
		else if (!accessAble(pos1 + test_point) || !accessAble(pos2 + test_point)) {
			walk = false;
		}

		if (hasBubble(tileCoordForPosition(pos1 + test_point + Vec2(0, -6))) || hasBubble(tileCoordForPosition(pos2 + test_point) + Vec2(0, -6))) {
			walk = false;
		}
		if (walk) {
			moves.pushBack(Sequence::create(MoveBy::create(dur, cur_delta), CallFuncN::create(
				[=](Ref* sender) {
				chara->last_move -= chara->getMoveVector(index);
			}), NULL));
		}
		else {
			chara->last_move = { 0,0 };
		}
		break;
	}
	if (moves.size())
		chara->runAction(cocos2d::Spawn::create(moves));
}

