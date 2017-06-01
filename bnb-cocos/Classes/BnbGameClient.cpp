#define _CRT_SECURE_NO_WARNINGS
#include"BnbGameClient.h"
#include"Settings.h"
#include<string>
#include<winsock2.h>
#include <fstream>
USING_NS_CC;
using std::fstream;
using std::string;
using std::endl;

#define PORTS 1236

bool GameClient::init()
{
	std::ofstream outfile;
	outfile.open("e:\\log2.txt");

	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		outfile << "无法加载套接字协议栈\n";
		return false;
	}

	ServerAddr.sin_family = PF_INET;
	ServerAddr.sin_port = htons(PORTS);
	ServerAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	ClientSocket = socket(PF_INET, SOCK_STREAM, 0);

	if (ClientSocket == INVALID_SOCKET)
	{
		outfile << "套接字初始化错误\n";
		WSACleanup(); //释放套接字资源  
		return false;
	}

	if (connect(ClientSocket, (LPSOCKADDR)&ServerAddr,
		sizeof(ServerAddr)) == INVALID_SOCKET)
	{
		outfile << "连接服务器出现错误\n";
		closesocket(ClientSocket); //关闭套接字  
		WSACleanup(); //释放套接字资源  
		return false;
	}

	outfile <<"连接服务器成功\n";
	outfile.close();
	return true;
}

//-----------------------------------------------------------------------------  
//函数名：启动发送线程  
//描述：用于数据的发送  
//  
//-----------------------------------------------------------------------------  
DWORD WINAPI GameClient::Send(LPVOID lpParam)
{
	/*{"你好吗"},
	{"跟我来"},
	{"我正在这处地区"},
	{"请求支援"},
	{"我正在攻击"},
	{"前面有敌人"},
	{"大家快跑"},
	{"你们要顶住"},
	*/

	char chatinfo[8][100] =
	{
		{ "#CU i0*t0*x-2.0f*y4.0f*z-4.0f*uliubing*h100*s0*" },
		{ "#CU i0*t0*x-2.0f*y5.0f*z24.0f*uliubing*h100*s0*" },
		{ "#CU i0*t0*x12.0f*y4.0f*z8.0f*uliubing*h100*s0*" },
		{ "#CU i0*t0*x2.0f*y3.0f*z9.0f*uliubing*h100*s0*" },
		{ "#CU i0*t0*x2.0f*y5.0f*z7.0f*uliubing*h100*s0*" },
		{ "#CU i0*t0*x-2.0f*y3.0f*z8.0f*uliubing*h100*s0*" },
		{ "#HC i0*c2*I4*" },
		{ "#NC i0*t0*x2.0f*y4.0f*z4.0f*uliubing*" },

	};

	GameClient *Client = (GameClient *)lpParam;

	while (true)
	{
		//模拟测试的流量格式  
		if (Client->ClientSocket != NULL)
		{
			Sleep(10000);
			//三种不同的发送格式  
			// int temp = rand()%9 ;  
			//int iSend = send( Client-> ClientSocket,chatinfo[temp],strlen(chatinfo[temp]),0);  

			/*char  Send[200];
			printf("请输入要发送的信息:");
			cin>> Send;
			int iSend = send(  Client-> ClientSocket, Send,strlen( Send),0 );

			printf("发送信息为:%s\n", Send);
			*/
			int temp = rand() % 8;
			char sendbuf[1024];
			strcpy(Client->SendBuf, chatinfo[temp]);
			strcpy(sendbuf, Client->SendBuf);
			
			int iSend = send(Client->ClientSocket, sendbuf, strlen(sendbuf), 0);
			printf("要发送的信息是:%s\n", sendbuf);

			if (iSend <= 0)
			{
				if (Client->ClientSocket != NULL)
					closesocket( Client-> ClientSocket);
				 Client-> ClientSocket = NULL;
				printf("发送线程关闭\n");
				printf("发送[%d]\n接收[%d]\n",  Client-> SendThreadID,  Client-> RecvThreadID);
				ExitThread( Client-> SendThreadID);
				ExitThread( Client-> RecvThreadID);
				printf("发送线程关闭\n");
				return 0;
			}
		}
	}
	return 0;
}

//-----------------------------------------------------------------------------  
//函数名：启动接收线程  
//描述：用于数据的接收  
//  
//-----------------------------------------------------------------------------  
DWORD WINAPI  GameClient:: Receive(LPVOID lpParam)
{
	 GameClient * Client = ( GameClient *)lpParam;

	while (true)
	{
		fd_set  Read;
		int ret;
		FD_ZERO(& Read);
		FD_SET( Client-> ClientSocket, & Read);

		ret = select(0, & Read, NULL, NULL, NULL);


		if (FD_ISSET( Client-> ClientSocket, & Read) &&  Client-> ClientSocket != NULL)
		{

			//通过缓冲区交互  
			char recvbuf[1024];
			ZeroMemory(recvbuf, 1024);
			int iLen = recv( Client-> ClientSocket, recvbuf, 1024, 0);
			recvbuf[iLen] = '\0';
			ZeroMemory( Client-> RecvBuf, 1024);
			strcpy( Client-> RecvBuf, recvbuf);
			printf(" 接收到信息为:%s\n",  Client-> RecvBuf);

			 

			fflush(0);

			if (iLen == SOCKET_ERROR || iLen <= 0 || iLen != (int)strlen(recvbuf))
			{
				printf("接收出现错误号:%d\n", WSAGetLastError());
				if ( Client-> ClientSocket != NULL)
					closesocket( Client-> ClientSocket);
				 Client-> ClientSocket = NULL;
				printf("接收线程关闭\n");
				printf("发送[%d]\n接收[%d]\n",  Client-> SendThreadID,  Client-> RecvThreadID);
				ExitThread( Client-> RecvThreadID);
				ExitThread( Client-> SendThreadID);
				printf("接收线程关闭\n");
				return 0;
			}

		}
	}
	return 0;
}
//----------------------------------------------------------------------------  
//  
//  
//-----------------------------------------------------------------------------  
int  GameClient:: SendMsg(char *buf)
{
	int iSend = send( ClientSocket, buf, strlen(buf), 0);

	if (iSend != (int)strlen(buf))
		printf("发送失败\n");

	ZeroMemory(buf, strlen(buf));

	return 1;
}
//-----------------------------------------------------------------------------  
//函数名：  
//描述：用于调度  
//  
//-----------------------------------------------------------------------------  
void  GameClient:: ClientProcess()
{
	HANDLE  Recv,  Send;


	 Recv = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) Receive, this, 0, & RecvThreadID);
	CloseHandle( Recv);

	Sleep(2000);
	 Send = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) Send, this, 0, & SendThreadID);
	CloseHandle( Send);
}

//-----------------------------------------------------------------------------  
//函数名：  
//描述:用于资源的释放  
//  
//-----------------------------------------------------------------------------  
void  GameClient:: CleanUp()
{
	closesocket( ClientSocket);
	WSACleanup();
}

