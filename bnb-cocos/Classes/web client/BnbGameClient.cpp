#define _CRT_SECURE_NO_WARNINGS
#include "BnbGameClient.h"
#include "Settings.h"
#include <string>
#include <winsock2.h>
#include <fstream>
#include "../view/GameScene.h"
#include "../controller/PlayerController.h"
#include "../controller/CharacterFSM.h"
#include <random>

USING_NS_CC;
using namespace settings::GameScene;

using std::queue;
using std::fstream;
using std::string;
using std::endl;

#define PORTS 1236      //设置端口号，与Server一致

extern std::vector <RoomInfo> Rooms;
std::queue <recvInfo> GameClient::recvQueue;

static inline GameScene* getGameScene() {
	auto scene = Director::getInstance()->getRunningScene();
	return dynamic_cast<GameScene*>(scene->getChildByTag(10));
}

/*
名称：初始化
描述：主要负责连接到服务端
*/
bool GameClient::init()
{
	std::fstream outfile;
	outfile.open("e:\\log2.txt", std::ios::app);

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
	unsigned long ul = 1;
	int ret = ioctlsocket(ClientSocket, FIONBIO, (unsigned long*)&ul); //设置成非阻塞
	if (ret == SOCKET_ERROR)  //设置失败
	{
		outfile << "设置非阻塞失败\n";
		closesocket(ClientSocket); //关闭套接字  
		WSACleanup(); //释放套接字资源  
		return false;
	}
	outfile << "设置非阻塞成功\n";

	if (connect(ClientSocket, (LPSOCKADDR)&ServerAddr,
		sizeof(ServerAddr)) < 0)
	{
		fd_set wfd;
		struct timeval tm;

		FD_ZERO(&wfd);
		FD_SET(ClientSocket, &wfd);
		tm.tv_sec = 0.1;
		tm.tv_usec = 0;
		int sel = select(ClientSocket, NULL, &wfd, NULL, &tm);
		if (sel <= 0)
		{
			outfile << "连接失败\n";
			closesocket(ClientSocket); //关闭套接字  
			WSACleanup(); //释放套接字资源  
			return false;
		}
	}

	outfile << "客户端连接成功!\n";
	outfile.close();
	Rooms.resize(4);
	for (int i = 0; i < 4; i++)
	{
		Rooms[i].name = "Room" + std::to_string(i);
		Rooms[i].id = 100000 + i;
		Rooms[i].curNum = 0;
	}
	return true;
}


/*
名称：线程处理
描述：主要负责两大线程的处理，一个是收发数据的线程，一个是消费者线程
本函数受到WebGameScene的schedule制约，每一帧执行一次
*/
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
	HANDLE hThread1;
	HANDLE hThread2;
	hThread1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)sendAndRecv, this, 0, NULL);

	hThread2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)comsumer, this, 0, NULL);
	CloseHandle(hThread1);
	CloseHandle(hThread2);


	hMutex = CreateMutex(nullptr, TRUE, TEXT("Control"));
	if (hMutex)
	{
		if (ERROR_ALREADY_EXISTS == GetLastError())
		{
			return;
		}
	}
	WaitForSingleObject(hMutex, INFINITE);
	ReleaseMutex(hMutex);
	ReleaseMutex(hMutex);
}


/*
名称：收发函数
描述：专门处理收发数据的线程函数，采用异步、非阻塞模式。
*/
DWORD WINAPI GameClient::sendAndRecv(LPVOID lpParam)
{
	GameClient *Client = (GameClient *)lpParam;
	GameClient *Client2 = (GameClient *)lpParam;
	const int PACKAGE = 28;          //每次发送包的长度

	{
		WaitForSingleObject(Client->hMutex, INFINITE);

		fd_set wfd, rfd;
		FD_ZERO(&wfd);
		FD_ZERO(&rfd);

		FD_SET(Client->ClientSocket, &wfd);
		FD_SET(Client2->ClientSocket, &rfd);

		int sel = select(0, &rfd, &wfd, NULL, NULL);
		if (sel > 0)
		{
			if (FD_ISSET(Client->ClientSocket, &wfd))
			{
				/*
				发送数据
				*/
				character * myplayer = dynamic_cast<character*>(Client->runningGameScene->getChildByName("myplayer"));
				if (myplayer == nullptr)
					return 0;

				int direct;
				for (direct = 0; direct < 4; ++direct) {
					if (myplayer->_chara_move[direct])
						break;
				}

				int still_1 = myplayer->_chara_still;

				int put_bubble_1 = 0;

				if (myplayer->_chara_bubble== true)
					put_bubble_1 = 1;


				Vec2 pos = myplayer->getPosition();
				//Vec2 broken_tile = runningGameScene->next_ps;

				char sendData[1024];
				ZeroMemory(sendData, sizeof(sendData));

				//传递格式 位置（.x .y) 静止 方向 是否放泡泡了 泡泡炸坏了哪个tile(.x .y)
				sprintf(sendData, "%f %f %d %d %d", pos.x, pos.y, still_1,
					direct, put_bubble_1);

				//发送

				int sendByte = 0;
				while (sendByte < PACKAGE)
				{
					int ret = send(Client->ClientSocket, sendData, strlen(sendData) + sizeof(char), 0);
					sendByte += ret;
				}

			}


			if (FD_ISSET(Client2->ClientSocket, &rfd))
			{
				/*
				接收数据
				*/
				int direct_2;
				int still_2;
				int put_bubble_2 = 0;
				char recvData[PACKAGE * 100];
				ZeroMemory(recvData, sizeof(recvData));

				int temp = 0;
				//接收

				int recvByte = 0;
				int ret;
				while (recvByte < PACKAGE)
				{
					ret = recv(Client2->ClientSocket, recvData, PACKAGE * 100, 0);
					recvByte += ret;
				}


				int len = recvByte / PACKAGE;
				recvData[PACKAGE] = '\0';

				/*
				producer
				*/
				for (int i = 0; i < len; i++)
				{
					recvInfo temp;
					sscanf(recvData + i*PACKAGE, "%f %f %d %d %d", &temp.Posx, &temp.Posy,
						&temp.still, &temp.direct, &temp.putBubble);

					recvQueue.push(temp);
				}

			}
		}

		ReleaseMutex(Client->hMutex);
	}

	WaitForSingleObject(Client->hMutex, INFINITE);

	return 1;
}




/*
名称：消费者
描述：开的新线程，专门用来pop队列，来达到控制角色的目的
*/
DWORD WINAPI GameClient::comsumer(LPVOID lpParam)
{
	GameClient *Client = (GameClient *)lpParam;

	if (recvQueue.empty() == true)
	{
		return 0;
	}

	character * player2 = dynamic_cast<character*>(Client->runningGameScene->getChildByName("player4"));

	//fstream outfile("e:\\text.txt");
	WaitForSingleObject(Client->hMutex, INFINITE);
	while (true)
	{
		recvInfo temp;
		if (!recvQueue.empty())
			temp = recvQueue.front();
		else
		{
			ReleaseMutex(Client->hMutex);
			break;
		}


		Vec2 Pos(temp.Posx, temp.Posy);

		if (temp.putBubble &&
			player2->_currentBubbles <=
			player2->_maxBubbles)
			Client->runningGameScene->setBubble(player2, Pos);

		/*
		outfile << "queue size: " << recvQueue.size() << " |";
		outfile << "消费者: " << temp.Posx << " " << temp.Posy << " "
		<< temp.still << " " << temp.direct << " " << temp.putBubble << endl;
		*/

		if (temp.Posx > 0 && temp.Posy > 0)  //判断一下，万一传输错了
		{

			player2->setPosition(temp.Posx, temp.Posy);
			/*
			if (temp.still == true)
			{
			player2->changeState(std::make_shared<CharStand>());
			}
			else
			{
			if (temp.direct < 4)
			{
			GameScene::_optionCode code = GameScene::_optionCode::DEFAULT;
			switch (temp.direct)
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
			//DEBUG

			if (code != GameScene::_optionCode::DEFAULT)
			player2->changeState(std::make_shared<CharMove>(static_cast<int>(code)));
			}
			}*/
		}
		else
		{
			ReleaseMutex(Client->hMutex);
			break;
		}

		

		if (!recvQueue.empty())
			recvQueue.pop();
		else
		{
			ReleaseMutex(Client->hMutex);
			break;
		}


	}
	ReleaseMutex(Client->hMutex);
	//outfile.close();

	WaitForSingleObject(Client->hMutex, INFINITE);
	return 1;

}


/*
名称：接受道具
描述：专门用来接受道具分布信息的函数
作用单一，只执行一次
*/
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


/*
名称: 处理线程在游戏开始之前
描述: 顾名思义
*/
int GameClient::ClientProcessBefore(int flag)
{
	static int curNum;

	char buff[8];
	ZeroMemory(buff, sizeof(buff));
	sprintf(buff, "%d", flag);
	int sec = send(ClientSocket, buff, strlen(buff)+sizeof(char), 0);
	
	std::fstream outfile("e:\\text.txt",std::ios::app);
	outfile << "sec :" << sec << " flag:" << flag << "\n";
	outfile.close();

	char buf[10000];
	int ret = recv(ClientSocket, buf, sizeof(buf), 0);
	if (ret > 0)
		sscanf(buf, "%d %d %d %d",&curNum, &Rooms[0].curNum, &Rooms[1].curNum, &Rooms[2].curNum, &Rooms[3].curNum);
		
	return curNum;
}



/*
名称：析构函数
描述：释放套接字，清理内存
*/
GameClient::~GameClient()
{
	delete[]prop;
	closesocket(ClientSocket);

	WSACleanup();
}