#include <windows.h>
#include <Winsock.h>
#include <iostream>
#pragma comment(lib,"ws2_32")
using namespace std;
int main(int argc, char argv[])
{
	WORD wVersion = MAKEWORD(2, 2);
	WSADATA ClientData;
	if (WSAStartup(wVersion, &ClientData)){
		cout << "WSAStartup��ʧ��" << endl;
	}
	SOCKET ClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ClientSocket == INVALID_SOCKET){
		cout << "�׽��ִ�ʧ��" << endl;
	}
	sockaddr_in Clientaddr;
	int duankou;
	cout << "������˿ںţ�";
	cin >> duankou;
	Clientaddr.sin_port = htons(duankou);
	Clientaddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");//inet_addr(),����Ϊһ���ַ�������IP�ַ�����ֵ���ݸ�inet_addr
	Clientaddr.sin_family = AF_INET;
	if (connect(ClientSocket, (LPSOCKADDR)&Clientaddr, sizeof(Clientaddr))){
		cout << "����ʧ�ܣ�" << endl;
		closesocket(ClientSocket);
		WSACleanup();
		return 0;
	}
	cout << "�ͻ��˳�ʼ���ɹ���׼������" << endl;
	while (1)
	{
		cout << "��������Ϣ��";
		char buff[1000];
		cin >> buff;
		if (strcmp(buff, "bye") == 0)
		{
			send(ClientSocket, buff, strlen(buff), 0);
			break;
		}
		cout << "������Ϣ��" << buff << endl;
		if (send(ClientSocket, buff, strlen(buff), 0) < 0){
			cout << "����ʧ��!" << endl;
		}
		else{
			cout << "���ͳɹ�!" << endl;
		}
		cout << "׼��������Ϣ" << endl;
		char  RecMessage[1024];
		int MessageLen = recv(ClientSocket, RecMessage, sizeof(RecMessage), 0);
		//cout << MessageLen << endl;������
		if (MessageLen < 0){
			cout << "����ʧ��" << endl;
		}
		else{
			//RecMessage[MessageLen] = 0X00;
			if (strcmp(RecMessage, "bye") == 0)
			{
				cout << "�������ѹرգ���������" << endl;
				system("pause");
				break;
			}
			cout << "���ܳɹ�����ϢΪ��" << RecMessage << endl;
		}
	}
	closesocket(ClientSocket);
	WSACleanup();
	return 0;
}

