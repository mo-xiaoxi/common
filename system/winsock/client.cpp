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
		cout << "WSAStartup打开失败" << endl;
	}
	SOCKET ClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ClientSocket == INVALID_SOCKET){
		cout << "套接字打开失败" << endl;
	}
	sockaddr_in Clientaddr;
	Clientaddr.sin_port = htons(2012);
	Clientaddr.sin_addr.S_un.S_addr = inet_addr("10.63.255.47");//inet_addr(),参数为一个字符串，将IP字符串的值传递给inet_addr
	Clientaddr.sin_family = AF_INET;
	if (connect(ClientSocket, (LPSOCKADDR)&Clientaddr, sizeof(Clientaddr))){
		cout << "连接失败！" << endl;
		closesocket(ClientSocket);
		WSACleanup();
		return 0;
	}
	cout << "客户端初始化成功，准备交流" << endl;
	while (1)
	{
		cout << "请输入发送信息：" << endl;
		char buff[1000];
		cin >> buff;
		cout << "发送信息：" << buff << endl;
		if (send(ClientSocket, buff, strlen(buff), 0) < 0){
			cout << "发送失败!" << endl;
		}
		else{
			cout << "发送成功!" << endl;
		}
		cout << "准备接受信息" << endl;
		char  RecMessage[1024];
		int MessageLen = recv(ClientSocket, RecMessage, sizeof(RecMessage), 0);
		//cout << MessageLen << endl;测试用
		if (MessageLen < 0){
			cout << "接受失败" << endl;
		}
		else{
			RecMessage[MessageLen] = 0X00;
			cout << "接受成功，信息为：" << RecMessage << endl;
		}
	}
	closesocket(ClientSocket);
	WSACleanup();
	return 0;
}

