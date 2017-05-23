#define _CRT_SECURE_NO_WARNINGS
#include"BnbGameServer.h"
#include"Settings.h"
#include<iostream>
#include<string>

USING_NS_CC;
using namespace std;

/*
名称：构造函数
描述：用于Socket初始化
*/
GameServer::GameServer()
{
	WSADATA wsaData;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)   //判断一下有没有这个版本
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
	Server.sin_addr.s_addr = inet_addr("127.0.0.1"); //本机地址

	 //绑定
	bind(ListenSocket, (LPSOCKADDR)&Server, sizeof(Server));
	/*
	if (bind(ListenSocket, (LPSOCKADDR)&Server, sizeof(Server)) == SOCKET_ERROR)  //???不应该报错啊
	{
		clog << "绑定出错，错误号：" << WSAGetLastError() << endl;
		return;
	}*/
	
	//监听
	if (listen(ListenSocket, 5) == SOCKET_ERROR)
	{
		clog<<"监听出错，错误号："<< WSAGetLastError() << endl;
		return;
	}

	//将所有信息初始化
	for (int i = 0; i < MAX_NUM; i++)
		AcceptSocket[i].ClientSock = NULL;

	/*
	此处要在后台上显示：
	“网络初始化成功”
	*/

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


/*
名称：检测ID
描述：用于检测当前没有用的ID号
*/
int GameServer::CheckSocket()
{
	for (int i = 0; i < MAX_NUM; i++)
	{
		if (AcceptSocket[i].ClientSock == NULL)
			return i;
	}
	return -1;
}

/*
名称：线程处理
描述：为每一个新玩家创建一个接受线程
	  如果人数达到上限，就拒绝
*/
int GameServer::ProcessGameServer()
{
	while (true)
	{
		int index = CheckSocket();
		sockaddr_in Client;

		int ClntLen = sizeof(Client);

		if (index != -1) //玩家未满
		{
			AcceptSocket[index].ClientSock = accept( 
				ListenSocket,
				(struct sockaddr*)&AcceptSocket[index].Client,
				&ClntLen
			);
			AcceptSocket[index].ID = index;
			AcceptSocket[index].Active = false;
			
			if (AcceptSocket[index].ClientSock == INVALID_SOCKET)
			{
				clog << "连接出错,错误号：" << WSAGetLastError() << endl;
				break;
			}

			/*
			此处要在后台上显示：
			“新玩家加入，IP地址为%d，端口号为%d”
			inet_ntoa(AcceptSocket[index].Client.sin_addr
			ntohs(AcceptSocket[index].Client.sin_port
			*/
			
			//创建接受者线程 
			int ThreadID;     //线程ID

			ThreadID =(int)CreateThread(NULL,0,
				(LPTHREAD_START_ROUTINE)(GameServer::ListenThread),
				(void*)&AcceptSocket[index],0,
				&AcceptSocket[index].RecvThreadID
			);

			if (!ThreadID)
			{
				clog << "创建线程失败\n";
				ExitThread(AcceptSocket[index].RecvThreadID);
			}

			/*
			此处要在后台上显示：
			“新玩家ID%d的接收线程创建成功”
			index
			*/

		}
		else   //玩家已满
		{
			SOCKET Accept = accept(ListenSocket,
				(struct sockaddr*)&Client, &ClntLen);

			if (Accept == INVALID_SOCKET)
			{
				clog << "连接出错，错误号：" << WSAGetLastError() << endl;
				break;
			}

			/*
			此处要在后台上显示：
			“非法请求的玩家IP地址为%d，端口号为%d”
			inet_ntoa(Client.sin_addr),
			ntohs(Client.sin_port)
			*/

			send(Accept, "当前用户已满", strlen("当前用户已满") + sizeof(char), 0);

			closesocket(Accept);

			/*
			此处要在后台上显示：
			“非法连接玩家已断开”
			*/
		}
	}
	return 0;
}

/*
名称：接受线程
描述：Select模式
	首先判断该线程是否可读，如果可读就读取其上的信息
*/
DWORD WINAPI GameServer::ListenThread(void *data)
{

	BnbClientInformation *GameSocket = (BnbClientInformation *)data;

	while (true)
	{
		//接收数据  
		char buf[1024];
		fd_set Read;//基于select模式对IO进行管理  

		FD_ZERO(&Read);    //初始化为0
		FD_SET(GameSocket->ClientSock, &Read); //将ClientSock加入队列

		//we only care read
		select(0, &Read, NULL, NULL, NULL);   //select 判断套接字能否写入

		if (FD_ISSET(GameSocket->ClientSock, &Read))  //判断是否存在
		{
			int result = recv(GameSocket->ClientSock, buf, sizeof(buf), 0);

			if (result > 0)
			{
				buf[result] = 0;
				/*
				此处要在后台上显示：
				“玩家ID%d接收到消息%s”
				GameSocket->ID
				buf
				*/
				fflush(0);
			}
			else
			{
				clog << "接收错误\n";
			}
		}
	}
	return 1;
}

/*
名称：发送信息给一个client
描述：发送信息给一个client
*/
int GameServer::SendMessageToOneClient(int ID, const string & str)
{
	if (ID < 0)
		return 0;

	/*
	此处要在后台上显示：
	“向玩家ID%d发送消息%s”
	ID
	buf
	*/
	int oneSend = send(AcceptSocket[ID].ClientSock,
		str.c_str(), str.size() + sizeof(char), 0);

	if (oneSend == SOCKET_ERROR)
	{
		clog << "发送错误\n";
		AcceptSocket[ID].ClientSock = NULL;
	}
	return 1;
}

/*
名称：全发送
描述：给所有Client发送信息
*/
void GameServer::SendMessageToAllClient(const string & str, int ID)
{
	/*
	此处要在后台上显示：
	“向全体玩家发送消息%s”
	buf
	*/
	for (int i = 0; i < MAX_NUM; i++)
	{
		if (AcceptSocket[i].ClientSock != NULL && i != ID && AcceptSocket[ID].Active)
			SendMessageToOneClient(i, str);
	}
}

/*
名称：清理Socket
描述：清理退出游戏的线程
*/
void GameServer::CleanSocket(int ID)
{
	if (ID < 0)
		return;

	char send[20];
	sprintf(send, "#DD i%d*", ID);
	SendMessageToAllClient(send, ID);

	/*
	此处要在后台上显示：
	“玩家[%d]退出游戏”
	ID
	*/

	AcceptSocket[ID].Active = false;
	closesocket(AcceptSocket[ID].ClientSock);
	AcceptSocket[ID].ClientSock = NULL;

	/*
	此处要在后台上显示：
	“正在关闭他的接收线程为%d\n”
	AcceptSocket[ID].RecvThreadID
	*/
	ExitThread(AcceptSocket[ID].RecvThreadID);

	
	/*
	此处要在后台上显示：
	“关闭成功”
	*/
}