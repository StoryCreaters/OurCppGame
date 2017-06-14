﻿#include "WebGameScene.h"
#include "GameScene.h"
#include <random>

USING_NS_CC;
using namespace settings::GameScene;

static inline GameScene* getGameScene() {
	auto scene = Director::getInstance()->getRunningScene();
	return dynamic_cast<GameScene*>(scene->getChildByTag(1));
}



bool WebGameScene::init()
{
	if (!Layer::init())
	{
		return false;
	}


	//初始化服务端
	client.init();

	

	this->scheduleUpdate();

	
	return true;
	
}

void WebGameScene::update(float dt) {
	static bool flag = false;
	std::ofstream outfile;
	
	if (!runningGameScene) {
		runningGameScene = getGameScene();
		if (runningGameScene == nullptr) {
			return;
		}
	}
	if (flag == false)
	{
		acceptProps();
		flag = true;
	}
	

	outfile.open("e:\\log3.txt", std::ios::app);
	outfile << "多少个players：" << runningGameScene->_game_players.size() << std::endl;
	/*
	############以下代码仅供测试，测试完毕后将会封装到BnbGameClient中############
	*/
	if (runningGameScene->_game_players.size() == 2)
	{
		{
			/*
			发送数据
			*/
			character * _play_1 = runningGameScene->_game_players.at(0);

			char direct_1[2];
			int direct;
			for (direct = 0; direct < 4; ++direct) {
				if (_play_1->_chara_move[direct])
					break;
			}

			int put_bubble_1 = 0;
			if (runningGameScene->key == GameScene::BUBBLE)
				put_bubble_1 = 1;

			Vec2 pos = _play_1->getPosition();
			Vec2 broken_tile = runningGameScene->next_ps;

			char sendData[1024];
			ZeroMemory(sendData, sizeof(sendData));

			//传递格式 位置（.x .y) 方向 是否放泡泡了 泡泡炸坏了哪个tile(.x .y)
			sprintf(sendData, "%f %f %d %d %f %f", pos.x, pos.y,
				direct, put_bubble_1, broken_tile.x, broken_tile.y);

			outfile << sendData << std::endl;
			//发送
			int ret = send(client.ClientSocket, sendData, strlen(sendData) + sizeof(char), 0);
			if (ret <= 0)
				outfile << "发送错误!\n";
			else
				outfile << "发送成功!\n";
		}

//*******************************************************************************************

		{
			/*
			接收数据
			*/
			int direct_2;
			int put_bubble_2 = 0;
			char recvData[1024];
			ZeroMemory(recvData, sizeof(recvData));
			const int size = 22;
			int temp = 0;
			//接收
			int ret2 = recv(client.ClientSocket, recvData, 1024, 0);
			recvData[ret2] = '\0';

			if (ret2 <= 0)
				outfile << "接受错误!\n";
			else
				outfile << "接受成功!\n";

			outfile << "#recvData: " << recvData << std::endl;
			Vec2 Pos;
			Vec2 broken_tile;
				//接收格式（同上） 
				sscanf(recvData, "%f %f %d %d %f %f", &Pos.x, &Pos.y,
					&direct_2, &put_bubble_2, &broken_tile.x, &broken_tile.y);

			if (broken_tile.x != 0 || broken_tile.y != 0)
			{
				runningGameScene->_meta->removeTileAt(broken_tile);
			}
			
			if (put_bubble_2)
				runningGameScene->setBubble(runningGameScene->_game_players.at(1), 1);
			for (int i = 0; i < 4; i++)
				runningGameScene->_game_players.at(1)->_chara_move[i] = false;
			if (direct_2 < 4)
				runningGameScene->_game_players.at(1)->_chara_move[direct_2] = true;
			runningGameScene->CharacterMove(runningGameScene->_game_players.at(1));
			runningGameScene->_game_players.at(1)->setPosition(Pos);
		}
	}
	outfile.close();
}



void WebGameScene::acceptProps()
{

	const int MAX = 2 * (sizeof(int) * 15 * 15 + 10 * sizeof(int));
	prop = new char[MAX + 1];
	ZeroMemory(prop, sizeof(prop));
	int ret = recv(client.ClientSocket, prop, MAX, 0);
	prop[ret] = '\0';

	std::array<std::array<int, 15>, 15> dist;
	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 15; j++)
			sscanf(prop + 2 * (i * 15 + j), "%d ", &dist[i][j]);


	while (!runningGameScene) {
		runningGameScene = getGameScene();
		if (runningGameScene == nullptr) {
			continue;
		}
	}

	

	// 加载地图的对应的道具
	for (int x = 0; x < 15; ++x)
		for (int y = 0; y < 15; ++y)
			if (!runningGameScene->hasCollisionInGridPos(Vec2(x, y))) {
				runningGameScene->prop_on_map[x][y] = dist[x][y] - 1;
			}

	std::ofstream outfile2;
	outfile2.open("e:\\log4.txt", std::ios::app);
	outfile2 << "-------------------------------\n";
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
			outfile2 << runningGameScene->prop_on_map[i][j] << " ";
		outfile2 << "\n";
	}
	outfile2.close();
}

WebGameScene::~WebGameScene()
{
	delete[] prop;
}