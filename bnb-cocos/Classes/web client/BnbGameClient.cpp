﻿#define _CRT_SECURE_NO_WARNINGS
#include "BnbGameClient.h"
#include "Settings.h"
#include <string>
#include <winsock2.h>
#include <fstream>
#include "../view/GameScene.h"
#include "../controller/PlayerController.h"
#include "../controller/CharacterFSM.h"
#include <random>
<<<<<<< .merge_file_a93392




USING_NS_CC;
using namespace settings::GameScene;

=======
#include <cstring>
#include <mutex>
#include "ui/CocosGUI.h"

using namespace ui;

#define CHATPACKAGE 1024
USING_NS_CC;
using namespace settings::GameScene;


>>>>>>> .merge_file_a18468
using std::queue;
using std::fstream;
using std::string;
using std::endl;

#define PORTS 1236      //设置端口号，与Server一致

<<<<<<< .merge_file_a93392
std::queue <recvInfo> GameClient::recvQueue;
=======
extern std::vector <RoomInfo> Rooms;
std::queue <packageInfo> GameClient::recvQueue;
struct PlayerInfo myPlayerInfo;
bool getMsg = false;
std::string Msg;
extern ChatBox *chatting;
static int whichRoom;
int RoomPlayers;
int whichPlayer;
extern int win;

std::mutex g_lock;  
>>>>>>> .merge_file_a18468

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
<<<<<<< .merge_file_a93392
		WSACleanup(); //释放套接字资源  
=======
		WSACleanup(); //释放套接字资源
>>>>>>> .merge_file_a18468
		return false;
	}
	unsigned long ul = 1;
	int ret = ioctlsocket(ClientSocket, FIONBIO, (unsigned long*)&ul); //设置成非阻塞
	if (ret == SOCKET_ERROR)  //设置失败
	{
		outfile << "设置非阻塞失败\n";
<<<<<<< .merge_file_a93392
		closesocket(ClientSocket); //关闭套接字  
		WSACleanup(); //释放套接字资源  
=======
		closesocket(ClientSocket); //关闭套接字
		WSACleanup(); //释放套接字资源
>>>>>>> .merge_file_a18468
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
<<<<<<< .merge_file_a93392
			closesocket(ClientSocket); //关闭套接字  
			WSACleanup(); //释放套接字资源  
=======
			closesocket(ClientSocket); //关闭套接字
			WSACleanup(); //释放套接字资源
>>>>>>> .merge_file_a18468
			return false;
		}
	}

	outfile << "客户端连接成功!\n";
	outfile.close();
<<<<<<< .merge_file_a93392
=======
	Rooms.resize(4);
	for (int i = 0; i < 4; i++)
	{
		Rooms[i].name = "Room" + std::to_string(i);
		Rooms[i].id = 10 + i;
		Rooms[i].curNum = 0;
	}
	char tempBuf[8];
	int retc = recv(ClientSocket, tempBuf, sizeof(tempBuf), 0);
	int id;
	sscanf(tempBuf, "%d", &id);
	myPlayerInfo.clientInfo = { NULL,ServerAddr,id,0,0,0 };
	myPlayerInfo.nickname = std::to_string(ServerAddr.sin_addr.S_un.S_addr) + "_" +
		std::to_string(ServerAddr.sin_port) + "_" + std::to_string(id);


>>>>>>> .merge_file_a18468
	return true;
}


/*
名称：线程处理
描述：主要负责两大线程的处理，一个是收发数据的线程，一个是消费者线程
本函数受到WebGameScene的schedule制约，每一帧执行一次
*/
<<<<<<< .merge_file_a93392
void  GameClient::ClientProcess()
{

	static bool flag = false;

	if (!runningGameScene) {
		runningGameScene = getGameScene();
		if (runningGameScene == nullptr) {
			return;
		}
	}
=======
bool  GameClient::gameThreadProcess(GameScene * gs)
{
	static bool flag = false;

	runningGameScene = gs;
>>>>>>> .merge_file_a18468

	if (flag == false)
	{
		acceptProps();
		flag = true;
	}
<<<<<<< .merge_file_a93392
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
=======

	HANDLE sendThead, recvThread, comsumerThread;
	sendThead = CreateThread(NULL, 0,
		static_cast<LPTHREAD_START_ROUTINE>(GameClient::gameSendThread),
		static_cast<LPVOID>(this), 0,
		NULL
	);
	recvThread = CreateThread(NULL, 0,
		static_cast<LPTHREAD_START_ROUTINE>(GameClient::gameRecvThread),
		static_cast<LPVOID>(this), 0,
		NULL
	);
	comsumerThread = CreateThread(NULL, 0,
		static_cast<LPTHREAD_START_ROUTINE>(GameClient::gameSendThread),
		static_cast<LPVOID>(this), 0,
		NULL
	);
	CloseHandle(sendThead);
	CloseHandle(recvThread);
	CloseHandle(comsumerThread);

	return true;
}


/*
名称：游戏发送数据
描述：发送游戏数据的线程
*/
DWORD WINAPI GameClient::gameSendThread(LPVOID lpParam)
{
	GameClient *Client = static_cast<GameClient *>(lpParam);

	const int PACKAGE = 28;          //每次发送包的长度
	char sendData[1024];
	packageInfo * theReserved = nullptr;
	packageInfo * theSend;
	static int times = 0;
	while (true)
	{
		fd_set wfd;
		FD_ZERO(&wfd);
		FD_SET(Client->ClientSocket, &wfd);
		int sel = select(0, NULL, &wfd, NULL, NULL);
>>>>>>> .merge_file_a18468
		if (sel > 0)
		{
			if (FD_ISSET(Client->ClientSocket, &wfd))
			{
<<<<<<< .merge_file_a93392
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
=======
				theSend = new packageInfo[1];

				character * myplayer = dynamic_cast<character*>(Client->runningGameScene->getChildByName("myplayer"));
				if (myplayer == nullptr)
					break;

				if (myplayer->_chara_die == true)
				{
					send(Client->ClientSocket, "#GAMEOVER_YOUWIN#", strlen("#GAMEOVER_YOUWIN#") + sizeof(char), 0);
					win = 0;
					break;
				}
				if (myplayer->_chara_bubble == true)
					theSend->putBubble = 1;
				else
					theSend->putBubble = 0;

				if (typeid(*(myplayer->mCurState)).hash_code() == typeid(CharMove).hash_code() || theSend->putBubble)
				{
					int direct;
					for (direct = 0; direct < 4; ++direct) {
						if (myplayer->_chara_move[direct])
							break;
					}
					theSend->direct = direct;

					theSend->still = myplayer->_chara_still;

					Vec2 pos = myplayer->getPosition();
					
					theSend->Posx = pos.x;
					theSend->Posy = pos.y;
					
					if (theReserved != nullptr)
					{
						if (!memcmp(theReserved, theSend, sizeof(theReserved)) && !theSend->putBubble)
						{
							times++;
							if (times < 200)  
								continue;
							else
								times = 0;
						}
						else
							memcpy(theReserved, theSend, sizeof(theReserved));
					}
					else
					{
						theReserved = new packageInfo[1];
						memcpy(theReserved, theSend, sizeof(theSend));
					}

					ZeroMemory(sendData, sizeof(sendData));
					//传递格式 位置（.x .y) 静止 方向 是否放泡泡了   
					sprintf(sendData, "%f %f %d %d %d", theSend->Posx, theSend->Posy, theSend->still,
						theSend->direct, theSend->putBubble);

					//发送
					int sendByte = 0;
					while (sendByte < PACKAGE)
					{
						int ret = send(Client->ClientSocket, sendData, strlen(sendData) + sizeof(char), 0);
						sendByte += ret;
					}
					
				}
				delete[]theSend;
			}
		}

	}
	if (theReserved != nullptr)
		delete[]theReserved;
	

	return 1;
}

/*
名称：游戏接收数据
描述：接收游戏数的线程
*/
DWORD WINAPI GameClient::gameRecvThread(LPVOID lpParam)
{
	GameClient *Client = static_cast<GameClient *>(lpParam);
	const int PACKAGE = 28;          //每次发送包的长度
	char recvData[PACKAGE * 100];

	while (true)
	{
		fd_set rfd;
		FD_ZERO(&rfd);
		FD_SET(Client->ClientSocket, &rfd);
		int sel = select(0, &rfd, NULL, NULL, NULL);
		if (sel > 0)
		{
			if (FD_ISSET(Client->ClientSocket, &rfd))
>>>>>>> .merge_file_a18468
			{
				/*
				接收数据
				*/
				int direct_2;
				int still_2;
				int put_bubble_2 = 0;
<<<<<<< .merge_file_a93392
				char recvData[PACKAGE * 100];
=======

>>>>>>> .merge_file_a18468
				ZeroMemory(recvData, sizeof(recvData));

				int temp = 0;
				//接收

				int recvByte = 0;
				int ret;
				while (recvByte < PACKAGE)
				{
<<<<<<< .merge_file_a93392
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




=======
					ret = recv(Client->ClientSocket, recvData, PACKAGE * 100, 0);
					if (ret == SOCKET_ERROR)
						continue;
					recvByte += ret;
				}

				if (recvData[0] == '#')
				{
					win = 1;
					break;
				}
				int len = recvByte / PACKAGE;
				recvData[PACKAGE] = '\0';


				/*
				producer
				*/

				for (int i = 0; i < len; i++)
				{
					packageInfo temp;
					sscanf(recvData + i*PACKAGE, "%f %f %d %d %d", &temp.Posx, &temp.Posy,
						&temp.still, &temp.direct, &temp.putBubble);
	
					g_lock.lock();
					recvQueue.push(temp);
					g_lock.unlock();
				}

			}
		}
	}


}



>>>>>>> .merge_file_a18468
/*
名称：消费者
描述：开的新线程，专门用来pop队列，来达到控制角色的目的
*/
DWORD WINAPI GameClient::comsumer(LPVOID lpParam)
{
<<<<<<< .merge_file_a93392
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

=======
	GameClient *Client = static_cast<GameClient *>(lpParam);

	character * player2 = dynamic_cast<character*>(Client->runningGameScene->getChildByName("player4"));
	while (true)
	{
		packageInfo temp;
		g_lock.lock();
		if (!recvQueue.empty()) {
			temp = recvQueue.front();
			recvQueue.pop();
			g_lock.unlock();
		}
		else {
			g_lock.unlock();
			continue;
		}
>>>>>>> .merge_file_a18468

		Vec2 Pos(temp.Posx, temp.Posy);

		if (temp.putBubble &&
			player2->_currentBubbles <=
			player2->_maxBubbles)
			Client->runningGameScene->setBubble(player2, Pos);

<<<<<<< .merge_file_a93392
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
=======


		if (temp.Posx > 0 && temp.Posy > 0 && temp.Posx < 1000 && temp.Posy < 1000)  //判断一下，万一传输错了
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
>>>>>>> .merge_file_a18468
			}*/
		}
		else
		{
<<<<<<< .merge_file_a93392
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
=======
			continue;
		}



	}


>>>>>>> .merge_file_a18468
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
<<<<<<< .merge_file_a93392
=======
名称: 处理线程在游戏开始之前
描述: 顾名思义
*/
int GameClient::clientProcessBefore(int flag, int which)
{
	static int curNum;

	int whichRoom = -1;
	if (flag == 1)
		whichRoom = which;

	char sendBuf[16];
	ZeroMemory(sendBuf, sizeof(sendBuf));
	sprintf(sendBuf, "%d %d", flag, whichRoom);
	int sec = send(ClientSocket, sendBuf, strlen(sendBuf) + sizeof(char), 0);


	char recvBuf[10000];
	int ret = recv(ClientSocket, recvBuf, sizeof(recvBuf), 0);
	if (ret > 0)
		sscanf(recvBuf, "%d %d %d %d", &curNum, &Rooms[0].curNum, &Rooms[1].curNum, &Rooms[2].curNum, &Rooms[3].curNum);

	return curNum;
}

/*
名称：线程处理房间相关
描述：在CharacterSelect中负责收发数据
*/
int GameClient::clientProcessRoomData(int which)
{
	//发送  内容比较简单，只发送所在房间的号码
	char sendBuf[8];
	sprintf(sendBuf, "%d", which);
	send(ClientSocket, sendBuf, strlen(sendBuf) + sizeof(char), 0);

	//接受   内容稍微复杂
	/*
	接受格式 ：int    #size    Rooms[which].playerlist 有几个玩家
	string #name    Rooms[which].playerlist.nickname  每个中间以|分隔
	*/

	char recvBuf[1024];
	int ret = recv(ClientSocket, recvBuf, sizeof(recvBuf), 0);

	int size;
	std::string str;
	char temp[1024];
	ZeroMemory(temp, sizeof(temp));

	if (ret > 0)
		sscanf(recvBuf, "%d %s", &size, temp);


	str = temp;

	//接受数据的处理 需要把收到的数据本地化
	if (str.size() < 8)
		return 0;

	if (size == Rooms[which].playerList.size())  //如果已经接收完毕，就不再处理
		return 0;

	for (int i = 0; i < size; i++)
	{
		static int pos = 0;
		std::string str1;
		while (pos < str.size() && str[pos] != '|')
		{
			str1 += str[pos];
			pos++;
		}
		pos++;
		struct PlayerInfo temp;
		temp.nickname = str1;
		if (temp.nickname.size() == 0)
			return 0;
		Rooms[which].playerList.push_back(temp);
	}

}

/*
名称：聊天室
描述：聊天数据的线程管理
*/
void GameClient::chat(int Room)
{
	whichRoom = Room;

	HANDLE sendThread, recvThread;
	sendThread = CreateThread(NULL, 0, chatSendThread, (LPVOID)this, 0, NULL);
	CloseHandle(sendThread);
	recvThread = CreateThread(NULL, 0, chatRecvThread, (LPVOID)this, 0, NULL);
	CloseHandle(recvThread);


}

/*
名称：聊天发送数据
描述：专门发送聊天数据的线程，采用select模式管理
*/
DWORD WINAPI GameClient::chatSendThread(LPVOID lpParam)  //聊天室发送消息
{
	GameClient *Client = static_cast<GameClient *>(lpParam);

	char sendBuf[CHATPACKAGE];

	while (true)
	{
		fd_set write;
		FD_ZERO(&write);
		FD_SET(Client->ClientSocket, &write);
		int sel = select(0, NULL, &write, NULL, NULL);
		if (sel > 0)
		{
			if (FD_ISSET(Client->ClientSocket, &write))
			{

				ZeroMemory(sendBuf, sizeof(sendBuf));
				char tempMsg[1024];
				ZeroMemory(tempMsg, sizeof(tempMsg));


				if (!chatting->cur_msg.empty())
				{
					strcpy(tempMsg, chatting->cur_msg.c_str());
					tempMsg[chatting->cur_msg.size()] = '\0';
					sprintf(sendBuf, "%d %s", whichRoom, tempMsg);
				}
				else
					continue;

				send(Client->ClientSocket, sendBuf, strlen(sendBuf) + sizeof(char), 0);

				if (chatting->cur_msg == "#GO_TO_GAME_SCENE!")
				{
					break;
				}

			}

		}

	}

	return 0;
}

/*
名称：聊天接收数据
描述：专门接收聊天数据的线程，采用select模式管理
*/
DWORD WINAPI GameClient::chatRecvThread(LPVOID lpParam)  //聊天室接受消息
{
	GameClient *Client = static_cast<GameClient *>(lpParam);
	char recvBuf[CHATPACKAGE];
	while (true)
	{

		fd_set read;
		FD_ZERO(&read);
		FD_SET(Client->ClientSocket, &read);
		int sel = select(0, &read, NULL, NULL, NULL);
		if (sel > 0)
		{
			if (FD_ISSET(Client->ClientSocket, &read))
			{
				Msg.clear();
				ZeroMemory(recvBuf, sizeof(recvBuf));

				int ret = recv(Client->ClientSocket, recvBuf, CHATPACKAGE, 0);
				if (ret == SOCKET_ERROR)
					continue;

				if (recvBuf[0] == '@')
				{
					sscanf(recvBuf, "@ %d %d", &RoomPlayers, &whichPlayer);
					break;
				}

				Msg = recvBuf;


			}
		}
	}
	return 0;
}

/*
>>>>>>> .merge_file_a18468
名称：析构函数
描述：释放套接字，清理内存
*/
GameClient::~GameClient()
{
	delete[]prop;
	closesocket(ClientSocket);

	WSACleanup();
<<<<<<< .merge_file_a93392
}
=======
}
>>>>>>> .merge_file_a18468
