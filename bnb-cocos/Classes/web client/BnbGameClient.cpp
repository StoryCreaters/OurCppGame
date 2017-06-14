#define _CRT_SECURE_NO_WARNINGS
#include "BnbGameClient.h"
#include "Settings.h"
#include <string>
#include <winsock2.h>
#include <fstream>
#include "WebGameScene.h"
#include "../view/GameScene.h"
#include "../controller/PlayerController.h"
#include "../controller/CharacterFSM.h"
#include <random>

USING_NS_CC;
using namespace settings::GameScene;

using std::fstream;
using std::string;
using std::endl;

#define PORTS 1236      //设置端口号，与Server一致

static inline GameScene* getGameScene() {
	auto scene = Director::getInstance()->getRunningScene();
	return dynamic_cast<GameScene*>(scene->getChildByTag(10));
}

bool GameClient::init()
{
	


	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		return false;
	}

	ServerAddr.sin_family = PF_INET;
	ServerAddr.sin_port = htons(PORTS);
	ServerAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	ClientSocket = socket(PF_INET, SOCK_STREAM, 0);

	if (ClientSocket == INVALID_SOCKET)
	{
	
		WSACleanup(); //释放套接字资源  
		return false;
	}

	if (connect(ClientSocket, (LPSOCKADDR)&ServerAddr,
		sizeof(ServerAddr)) == INVALID_SOCKET)
	{

		closesocket(ClientSocket); //关闭套接字  
		WSACleanup(); //释放套接字资源  
		return false;
	}


	
	return true;
}


//-----------------------------------------------------------------------------  
//函数名：  
//描述：用于调度  
//  
//-----------------------------------------------------------------------------  
void  GameClient::ClientProcess()
{
	
	static bool flag = false;

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

	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Receive, this, 0, &RecvThreadID);

	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Send, this, 0, &SendThreadID);
	
}

//-----------------------------------------------------------------------------  
//函数名：启动发送线程  
//描述：用于数据的发送  
//  
//-----------------------------------------------------------------------------  
DWORD WINAPI GameClient::Send(LPVOID lpParam)
{


	GameClient *Client = (GameClient *)lpParam;
	/*
	发送数据
	*/
	int direct;
	for (direct = 0; direct < 4; ++direct) {
		if (Client->runningGameScene->_game_players.at(0)->_chara_move[direct])
			break;
	}
	int still_1 = Client->runningGameScene->_game_players.at(0)->_chara_still;

	int put_bubble_1 = 0;
	//if (runningGameScene->key == GameScene::BUBBLE)
	//	put_bubble_1 = 1;

	Vec2 pos = Client->runningGameScene->_game_players.at(0)->getPosition();
	//Vec2 broken_tile = runningGameScene->next_ps;

	char sendData[1024];
	ZeroMemory(sendData, sizeof(sendData));

	//传递格式 位置（.x .y) 静止 方向 是否放泡泡了 泡泡炸坏了哪个tile(.x .y)
	sprintf(sendData, "%f %f %d %d %d", pos.x, pos.y, still_1,
		direct, put_bubble_1);

	//发送
	int ret = send(Client->ClientSocket, sendData, strlen(sendData) + sizeof(char), 0);




	return 0;
}

//-----------------------------------------------------------------------------  
//函数名：启动接收线程  
//描述：用于数据的接收  
//  
//-----------------------------------------------------------------------------  
DWORD WINAPI  GameClient::Receive(LPVOID lpParam)
{
	GameClient * Client = (GameClient *)lpParam;

	/*
	接收数据
	*/
	int direct_2;
	int still_2;
	int put_bubble_2 = 0;
	char recvData[1024];
	ZeroMemory(recvData, sizeof(recvData));
	const int size = 22;
	int temp = 0;
	//接收
	int ret2 = recv(Client->ClientSocket, recvData, 1024, 0);
	recvData[ret2] = '\0';

	Vec2 Pos;
	Vec2 broken_tile;
	//接收格式（同上） 
	sscanf(recvData, "%f %f %d %d %d", &Pos.x, &Pos.y, &still_2,
		&direct_2, &put_bubble_2);


	if (broken_tile.x != 0 || broken_tile.y != 0)
	{
		Client->runningGameScene->_meta->removeTileAt(broken_tile);
	}

	/*
	if (put_bubble_2)
	runningGameScene->setBubble(runningGameScene->_game_players.at(1), 1);
	*/
	if (still_2 == true)
	{
		Client->runningGameScene->_game_players.at(1)->changeState(std::make_shared<CharStand>());
	}
	else
	{
		for (int i = 0; i < 4; i++)
			Client->runningGameScene->_game_players.at(1)->_chara_move[i] = false;
		if (direct_2 < 4)
		{
			Client->runningGameScene->_game_players.at(1)->_chara_move[direct_2] = true;
			GameScene::_optionCode code = GameScene::_optionCode::DEFAULT;
			switch (direct_2)
			{
			case 0:
				code = GameScene::_optionCode::GO_UP;
				break;
			case 1:
				code = GameScene::_optionCode::GO_DOWN;
				break;
			case 2:
				code = GameScene::_optionCode::GO_LEFT;
				break;
			case 3:
				code = GameScene::_optionCode::GO_RIGHT;
				break;
			default:
				break;
			}
			Client->runningGameScene->_game_players.at(1)->changeState(std::make_shared<CharMove>(static_cast<int>(code)));
		}
	}


	return 0;
}


void GameClient::acceptProps()
{

	const int MAX = 2 * (sizeof(int) * 15 * 15 + 10 * sizeof(int));
	prop = new char[MAX + 1];
	ZeroMemory(prop, sizeof(prop));
	int ret = recv(this->ClientSocket, prop, MAX, 0);
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
}

GameClient::~GameClient()
{
	delete[]prop;
	closesocket(ClientSocket);
	WSACleanup();
}