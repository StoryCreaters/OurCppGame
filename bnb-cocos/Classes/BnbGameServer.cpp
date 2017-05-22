#include"BnbGameServer.h"
#include"Settings.h"
#include<iostream>
#include<string>
using namespace std;



/*
名称：构造函数
描述：用于Socket初始化
*/
GameServer::GameServer()
{
	WSADATA wsaData;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)   //判断一下爱有没有这个版本
	{
		clog << "无法加载套接字协议栈.\n";
		return;
	}

	//设置监听套接字
	ListenSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP); //IPv4 STREAM TCP

	if (ListenSocket == INVALID_SOCKET) 
	{
		clog << "套接字初始化错误，错误号：" << WSAGetLastError() << endl;
		return;
	}

	//设置服务器的信息
	Server.sin_family = PF_INET;
	Server.sin_port = htons(1234);
	Server.sin_addr.s_addr = inet_addr("127.0.0.1");

	//绑定
	if (bind(ListenSocket, (LPSOCKADDR)&Server, sizeof(Server)) == SOCKET_ERROR)
	{
		clog << "绑定出错，错误号：" << WSAGetLastError() << endl;
		return;
	}
	
	//监听
	if (listen(ListenSocket, 5) == SOCKET_ERROR)
	{
		clog<<"监听出错，错误号："<< WSAGetLastError() << endl;
		return;
	}

	//将所有信息初始化
	for (int i = 0; i < MAX_NUM; i++)
		AcceptSocket[i].ServerSock = NULL;

	clog << "网络初始化成功.\n";

}

/*
名称：析构函数
作用：用于资源释放
*/
GameServer::~GameServer()
{
	if (ListenSocket != NULL)
		closesocket(ListenSocket);
	WSACleanup();
}