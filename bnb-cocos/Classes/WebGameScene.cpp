#include "WebGameScene.h"
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

	std::ofstream outfile;
	outfile.open("e:\\log3.txt", std::ios::app);
	if (!runningGameScene) {
		runningGameScene = getGameScene();
		if (runningGameScene == nullptr) {
			outfile << "return\n";
			outfile.close();
			return;
		}
	}

	outfile << "多少个players：" << runningGameScene->_game_players.size() << std::endl;
	if (runningGameScene->_game_players.size() == 2)
	{

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
		char sendData[1024];
		ZeroMemory(sendData, sizeof(sendData));
		sprintf(sendData, "%f %f %d %d", pos.x, pos.y , direct, put_bubble_1);
		outfile << sendData << std::endl;
		
		int ret = send(client.ClientSocket, sendData, strlen(sendData)+sizeof(char), 0);
		if (ret <= 0)
			outfile << "发送错误!\n";
		else
			outfile << "发送成功!\n";
	



		int direct_2;
		int put_bubble_2 = 0;
		char recvData[1024];
		ZeroMemory(recvData, sizeof(recvData));
		const int size = 22;
		int temp = 0;
		
		int ret2 = recv(client.ClientSocket, recvData, 1024, 0);
		recvData[ret2] = '\0';
			
		if (ret2 <= 0)
			outfile << "接受错误!\n";
		else
			outfile << "接受成功!\n";
	
		outfile << "#recvData: " << recvData << std::endl;
		Vec2 Pos;
		sscanf(recvData, "%f %f %d %d", &Pos.x,&Pos.y, &direct_2,&put_bubble_2);
		outfile << Pos.x << " " << Pos.y << " " << direct_2 << std::endl;

		if(put_bubble_2)
			runningGameScene->setBubble(runningGameScene->_game_players.at(1),1);
		for (int i = 0; i < 4; i++)
			runningGameScene->_game_players.at(1)->_chara_move[i] = false;
		if (direct_2 < 4)
			runningGameScene->_game_players.at(1)->_chara_move[direct_2] = true;
		runningGameScene->CharacterMove(runningGameScene->_game_players.at(1));
		runningGameScene->_game_players.at(1)->setPosition(Pos);
		
	}
	outfile.close();
}

