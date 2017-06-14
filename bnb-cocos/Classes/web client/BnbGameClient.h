#pragma once
#include <winsock2.h>
#include <process.h>               //C中的线程 
#include <string>
#include <fstream>
#include <string>
#include "../view/GameScene.h"
#include "cocos2d.h"
#pragma comment(lib,"ws2_32.lib")


class GameClient
{
public:
	bool virtual init();
	void acceptProps();
	~GameClient();
	void ClientProcess();    //启动客户处理
	static DWORD WINAPI Send(LPVOID lpParam);    //发送线程
	static DWORD WINAPI Receive(LPVOID lpParam);  //接受线程

	static DWORD WINAPI sendAndRecv(LPVOID lpParam); 

	//SOCKET相关
public:
	SOCKET ClientSocket;
	struct sockaddr_in ServerAddr;

	char RecvBuf[1024];
	char SendBuf[1024];
	//网络数据处理

private:

	GameScene* runningGameScene;
	char *prop;
};
