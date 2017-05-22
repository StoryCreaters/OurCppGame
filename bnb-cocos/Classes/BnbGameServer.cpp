#include"BnbGameServer.h"
#include"Settings.h"
#include<iostream>
#include<string>
using namespace std;



/*
���ƣ����캯��
����������Socket��ʼ��
*/
GameServer::GameServer()
{
	WSADATA wsaData;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)   //�ж�һ�°���û������汾
	{
		clog << "�޷������׽���Э��ջ.\n";
		return;
	}

	//���ü����׽���
	ListenSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP); //IPv4 STREAM TCP

	if (ListenSocket == INVALID_SOCKET) 
	{
		clog << "�׽��ֳ�ʼ�����󣬴���ţ�" << WSAGetLastError() << endl;
		return;
	}

	//���÷���������Ϣ
	Server.sin_family = PF_INET;
	Server.sin_port = htons(1234);
	Server.sin_addr.s_addr = inet_addr("127.0.0.1");

	//��
	if (bind(ListenSocket, (LPSOCKADDR)&Server, sizeof(Server)) == SOCKET_ERROR)
	{
		clog << "�󶨳�������ţ�" << WSAGetLastError() << endl;
		return;
	}
	
	//����
	if (listen(ListenSocket, 5) == SOCKET_ERROR)
	{
		clog<<"������������ţ�"<< WSAGetLastError() << endl;
		return;
	}

	//��������Ϣ��ʼ��
	for (int i = 0; i < MAX_NUM; i++)
		AcceptSocket[i].ServerSock = NULL;

	clog << "�����ʼ���ɹ�.\n";

}

/*
���ƣ���������
���ã�������Դ�ͷ�
*/
GameServer::~GameServer()
{
	if (ListenSocket != NULL)
		closesocket(ListenSocket);
	WSACleanup();
}