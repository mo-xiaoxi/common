#include <iostream>
#include <Winsock.h>
#pragma comment(lib,"ws2_32")
using namespace std;
int main(int argc, char argv[])
{
	WORD Version = MAKEWORD(2, 2);
	WSADATA wsadata;

	if (WSAStartup(Version, &wsadata)){
		cout << "WSAStartup����!" << endl;
		WSACleanup();
	}
	SOCKET ServerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ServerSocket == INVALID_SOCKET){
		cout << "�׽��ִ򿪴���" << endl;

	}

	sockaddr_in ServerAddr;
	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_addr.S_un.S_addr = INADDR_ANY;
	int duankou;
	cout << "������˿ں�:" ;
	cin >> duankou;
	ServerAddr.sin_port = htons(duankou);
	if (bind(ServerSocket, (LPSOCKADDR)&ServerAddr, sizeof(ServerAddr))){
		cout << "�ӿ�����ʧ�ܣ�bind Fail��" << endl;

	}
	if (listen(ServerSocket, 5)){
		cout << "����ʧ�ܣ�listen Fail��" << endl;

	}

	sockaddr_in Clientaddr;
	SOCKET ClientSocket;
	int lAddrlen = sizeof(Clientaddr);
	cout << "��������ʼ���ɹ������ڼ���" << endl;
	int flag = 0;
	while (TRUE){
		ClientSocket = accept(ServerSocket, (LPSOCKADDR)&Clientaddr, &lAddrlen);

		if (ClientSocket == INVALID_SOCKET){
			cout << "����ʧ��" << endl;
		}
		else{
			cout << "���ӵ���ַ:" << inet_ntoa(Clientaddr.sin_addr) << endl;
		}
		while (TRUE){
			cout << "׼��������Ϣ" << endl;
			char RecvMessage[1024];
			int MessageLen = recv(ClientSocket, RecvMessage, sizeof(RecvMessage), 0);
			if (MessageLen < 0){
				cout << "������Ϣʧ��!" << endl;

			}
			else{
				RecvMessage[MessageLen] = 0x00;
				if (strcmp(RecvMessage, "bye") == 0)
				{
					cout << "�ͻ����ѹرգ��˴ν�������!" << endl;
					system("pause");
					cout << "���������������˿ڣ�" << duankou << endl;
					break;
				}
				cout << "���ܳɹ�����ϢΪ��" << RecvMessage << endl;
			}
			cout << "׼��������Ϣ" << endl;
			cout << "��������Ϣ:";
			char  Message[100];
			cin >> Message;
			if (strcmp(Message, "bye") == 0)
			{
				send(ClientSocket, Message, strlen(Message), 0);
				flag = 1;
				break;
			}
			cout << "������Ϣ��" << Message << endl;
			if (send(ClientSocket, Message, strlen(Message), 0) < 0){
				cout << "������Ϣʧ��!" << endl;
			}
			else{
				cout << "������Ϣ�ɹ�!" << endl;
			}

		}
		closesocket(ClientSocket);
		if (flag)
			break;
	}
	closesocket(ServerSocket);
	WSACleanup();
	return 0;

}





