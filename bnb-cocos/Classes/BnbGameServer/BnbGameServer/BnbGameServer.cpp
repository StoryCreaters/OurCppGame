#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "BnbGameServer.h"
#include <iostream>

using std::cout;
using std::string;
using std::endl;

static GameServer SendMsg;
/*
名称：构造函数
描述：用于Socket初始化
*/
GameServer::GameServer()
{
	WSADATA wsaData;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)   //判断一下有没有这个版本
	{
		cout << "无法加载套接字协议栈.\n";
		return;
	}

	//设置监听套接字
    ListenSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP); //IPv4 STREAM TCP

	if (ListenSocket == INVALID_SOCKET) 
	{
		cout << "套接字初始化错误，错误号：" << WSAGetLastError() << endl;
		return;
	}

	int port = 1235;
	
	//设置服务器的信息
	Server.sin_family = PF_INET;
	Server.sin_port = htons(port);
	Server.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

	int errornum;
	 //绑定
	bind(ListenSocket, (LPSOCKADDR)&Server, sizeof(Server));
	while ((errornum = WSAGetLastError()) == 10048)
	{
		port++;
		Server.sin_port = htons(port);
		int retval = bind(ListenSocket, (LPSOCKADDR)&Server, sizeof(Server));
		cout << "绑定错误，错误号10048\n";

	}
	cout << "服务器的IP为:"<< Server.sin_addr.S_un.S_addr
		<< " 端口号为: " << port << endl;

	//监听   有listen就有accept
	if (listen(ListenSocket, 5) == SOCKET_ERROR)
	{
		cout<<"监听出错，错误号："<< WSAGetLastError() << endl;
		return;
	}

	//将所有信息初始化
	for (int i = 0; i < MAX_NUM; i++)
		AcceptSocket[i].ClientSock = NULL;

	cout << "网络初始化成功\n";
	return;
}

/*
名称：析构函数
作用：用于资源释放
*/
GameServer::~GameServer()
{
	if (ListenSocket != NULL)
		closesocket(ListenSocket);
	cout << "服务器关闭\n";
	WSACleanup();
	return;
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
			
			//对应前面的listen，这里是对应操作accept
		
			cout << "等待Client连接...\n";
			AcceptSocket[index].ClientSock = accept(
				ListenSocket, 
				(struct sockaddr*)&AcceptSocket[index].Client,
				&ClntLen);

			AcceptSocket[index].ID = index;       //记录这个Client的ID啊，以后要寻找它
			AcceptSocket[index].Active = false;
			
			if (AcceptSocket[index].ClientSock == INVALID_SOCKET)
			{
				cout << "连接错误\n";
				break;
			}
			
			cout << "连接成功\n";
			
			//至此client与server连接成功,欢呼

			cout << "新玩家加入，IP地址为：" << inet_ntoa(AcceptSocket[index].Client.sin_addr)
				  << "  端口号为：" << ntohs(AcceptSocket[index].Client.sin_port) << endl;
	
			//创建接受者线程 
			int ThreadID;     //线程ID

			//把刚刚连接成功的Client建立一个新的线程
			ThreadID =(int)CreateThread(NULL,0, 
				(LPTHREAD_START_ROUTINE)(GameServer::ListenThread), //线程点函数
				(LPVOID)&AcceptSocket[index],0,              //参数
				&AcceptSocket[index].RecvThreadID          //系统分配的ID
			);

			if (!ThreadID)
			{
				cout << "创建线程错误\n";
				ExitThread(AcceptSocket[index].RecvThreadID);
			}

			//至此，新的线程创建成功，可以传输数据了

			cout << "新玩家" << index << "的接受线程创建成功\n";

		}
		else   //玩家已满
		{
			SOCKET Accept = accept(ListenSocket,
				(struct sockaddr*)&Client, &ClntLen);

			if (Accept == INVALID_SOCKET)
			{
				cout << "连接错误\n";
				break;
			}


			cout << "非法请求的玩家的IP的地址为:" << inet_ntoa(Client.sin_addr)
				<< " 端口号为 :" << ntohs(Client.sin_port) << endl;

			send(Accept, "当前用户已满", strlen("当前用户已满") + sizeof(char), 0);

			closesocket(Accept);

			cout << "非法连接玩家已断开\n";
			break;
		}
	}
	return 0;
}

/*
名称：接受线程
描述：Select模式
	首先判断该线程是否可读，如果可读就读取其上的信息
*/
DWORD WINAPI GameServer::ListenThread(void *data) //传进来具体哪个AcceptSocket[xx]的地址
{

	BnbClientInformation *GameSocket = (BnbClientInformation *)data;

	while (true)
	{
		//接收命令 

		char recvBuf[1024];

		fd_set Read;//基于select模式对IO进行管理  

		FD_ZERO(&Read);    //初始化为0
		FD_SET(GameSocket->ClientSock, &Read); //将ClientSock加入队列

		//we only care read
		select(0, &Read, NULL, NULL, NULL);   

		if (FD_ISSET(GameSocket->ClientSock, &Read))  
		{
			//接受客户端的数据
			int result = recv(GameSocket->ClientSock, recvBuf, sizeof(recvBuf), 0);

			if (result > 0)
			{
				recvBuf[result] = 0;

				cout <<	"玩家" << GameSocket->ID << "发送了消息:"
					<< recvBuf << endl;
				
			}
			else 
			{
				
			}
		}

		//发送命令 

		char sendBuf[1024];

		fd_set write;//基于select模式对IO进行管理  

		FD_ZERO(&write);    //初始化为0
		FD_SET(GameSocket->ClientSock, &write); //将ClientSock加入队列

											   //we only care read
		select(0, NULL, &write, NULL, NULL);

		if (FD_ISSET(GameSocket->ClientSock, &write))
		{
			//接受客户端的数据
			strcpy(sendBuf, recvBuf);
			SendMsg.SendMessageToAllClient(sendBuf);
			cout << "服务器向全体发送了消息:"
				<< sendBuf << endl;
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