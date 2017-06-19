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
#include "ChatBox.h"

class GameScene;



struct recvInfo {
	float Posx;
	float Posy;
	int still;
	int direct;
	int putBubble;
};

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




class GameClient
{
public:
	bool virtual init();
	void acceptProps();
	~GameClient();
	void ClientProcess();    //启动客户处理
	int ClientProcessBefore(int flag, int which);

	int ClientProcessRoomData(int which);

	static DWORD WINAPI sendAndRecv(LPVOID lpParam);   //收发消息
	static DWORD WINAPI comsumer(LPVOID lpParam);   //消费者

	
	void chat(int whichRoom);
	static DWORD WINAPI chatSendThread(LPVOID lpParam);  //聊天室发送消息
	static DWORD WINAPI chatRecvThread(LPVOID lpParam);  //聊天室接受消息

	//SOCKET相关
public:
	SOCKET ClientSocket;
	struct sockaddr_in ServerAddr;

	//网络数据处理

private:
	static std::queue <recvInfo> recvQueue;
	HANDLE hMutex;
	GameScene * runningGameScene;
	char *prop;
	
	
};
