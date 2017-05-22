#pragma once
#include<winsock2.h>
#include <process.h>               //�߳� 
#pragma comment(lib,"ws2_32.lib")


struct  BnbClientInformation           //Client �����Ϣ
{
	SOCKET ServerSock;       //�׽���
	sockaddr_in Client;      //Clinet IP
	int ID;                   //Server�����ID����
	DWORD RecvThreadID;        //Server������յ��̺߳�
	DWORD SendThreadID;			//Server���䷢�͵��̺߳�
	bool Active;					
};

class GameServer
{
private:
	enum {
		MAX_NUM = 3  //�����������
	};
public:
	GameServer();
	~GameServer();

	int ProcessGameServer();    //�̴߳���

	int SendMessageToOneClient(int ID, char *buf);  //��ĳһ��Client������Ϣ

	int CheckSocket();     //��⵱ǰ���õ�ID��
	void CleanSocket(int ID); //���ID�ŵ��׽���
	void SendMessageToAllClient(char *buf, int ID = -1); //������Client������Ϣ

	//Socket ���
public:
	static DWORD WINAPI ListenThread(void *data); //�����߳�

	SOCKET ListenSocket;       //�ȴ��������ݵ�socket
	sockaddr_in Server;        //�󶨵�ַ

	BnbClientInformation AcceptSocket[MAX_NUM];  //Client�������Ϣ
	//���������ݵĴ���
	/*
	���ӣ����������
	*/
public:

};

