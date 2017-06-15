﻿#pragma once
#include <winsock2.h>
#include <process.h>              
#include <string>
#include <fstream>
#include <string>
#include "../view/GameScene.h"
#include "cocos2d.h"
#pragma comment(lib,"ws2_32.lib")
#include <queue>      //存放数据的队列


struct recvInfo {
	float Posx;
	float Posy;
	int still;
	int direct;
	int putBubble;
};


class GameClient
{
public:
	bool virtual init();
	void acceptProps();
	~GameClient();
	void ClientProcess();    //启动客户处理

	static DWORD WINAPI sendAndRecv(LPVOID lpParam);   //收发消息
	static DWORD WINAPI control(LPVOID lpParam);
	//SOCKET相关
public:
	SOCKET ClientSocket;
	struct sockaddr_in ServerAddr;

	char RecvBuf[1024];
	char SendBuf[1024];
	//网络数据处理

private:
	std::queue <recvInfo> recvQueue;
	GameScene* runningGameScene;
	char *prop;
};
