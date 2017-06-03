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

		Vec2 pos = runningGameScene->_game_players.at(0)->getPosition();
		char sendData[1024];
		ZeroMemory(sendData, sizeof(sendData));
		sprintf(sendData, "%f %f", pos.x, pos.y);
		outfile << sendData << std::endl;
	
		int ret = send(client.ClientSocket, sendData, strlen(sendData)+sizeof(char), 0);
		if (ret <= 0)
			outfile << "发送错误!\n";
		else
			outfile << "发送成功!\n";
	

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
		sscanf(recvData, "%f %f", &Pos.x,&Pos.y);
		outfile << Pos.x << " " << Pos.y << std::endl;
		runningGameScene->_game_players.at(1)->setPosition(Pos);
		
	}
	outfile.close();
}

