#pragma once
#include <winsock2.h>
#include <process.h>              
#include <string>
#include <fstream>
#include <string>
#include "../view/GameScene.h"
#include "cocos2d.h"
#pragma comment(lib,"ws2_32.lib")
#include <queue>      //存放数据的队列

<<<<<<< HEAD
=======
class GameScene;


>>>>>>> 92e3e854e26c5cd8b58ee13989019241d9a68e0d

struct recvInfo {
	float Posx;
	float Posy;
	int still;
	int direct;
	int putBubble;
};

<<<<<<< HEAD
=======
struct  BnbClientInformation           //Client 相关信息
{
	SOCKET ClientSock;       //套接字
	sockaddr_in Client;      //Clinet IP port
	int ID;                   //Server分配的ID号码
	DWORD RecvThreadID;        //Server分配接收的线程号
	DWORD SendThreadID;			//Server分配发送的线程号
	bool Active;
};


struct PlayerInfo {
	std::string nickname;
	struct  BnbClientInformation clientInfo;
};


struct RoomInfo {
	std::string name;   //房间名称
	long id;           //房间号
	std::vector <PlayerInfo> playerList;   //玩家列表
	int curNum;        //当前房间里面的人数
};



>>>>>>> 92e3e854e26c5cd8b58ee13989019241d9a68e0d

class GameClient
{
public:
	bool virtual init();
	void acceptProps();
	~GameClient();
	void ClientProcess();    //启动客户处理
<<<<<<< HEAD

	static DWORD WINAPI sendAndRecv(LPVOID lpParam);   //收发消息
	static DWORD WINAPI control(LPVOID lpParam);
=======
	int ClientProcessBefore(int flag);

	static DWORD WINAPI sendAndRecv(LPVOID lpParam);   //收发消息
	static DWORD WINAPI comsumer(LPVOID lpParam);
>>>>>>> 92e3e854e26c5cd8b58ee13989019241d9a68e0d
	//SOCKET相关
public:
	SOCKET ClientSocket;
	struct sockaddr_in ServerAddr;

<<<<<<< HEAD
	char RecvBuf[1024];
	char SendBuf[1024];
=======
>>>>>>> 92e3e854e26c5cd8b58ee13989019241d9a68e0d
	//网络数据处理

private:
	static std::queue <recvInfo> recvQueue;
	HANDLE hMutex;
<<<<<<< HEAD
	GameScene* runningGameScene;
	char *prop;
=======
	GameScene * runningGameScene;
	char *prop;

>>>>>>> 92e3e854e26c5cd8b58ee13989019241d9a68e0d
};
