#include <iostream>
#include <Winsock.h>
#pragma comment(lib,"ws2_32")
using namespace std;
int main(int argc, char argv[])
{
	WORD Version = MAKEWORD(2, 2);
	WSADATA wsadata;

	if (WSAStartup(Version, &wsadata)){
		cout << "WSAStartup出错!" << endl;
		WSACleanup();
	}
	SOCKET ServerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ServerSocket == INVALID_SOCKET){
		cout << "套接字打开错误" << endl;

	}

	sockaddr_in ServerAddr;
	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_addr.S_un.S_addr = INADDR_ANY;
	ServerAddr.sin_port = htons(2012);
	if (bind(ServerSocket, (LPSOCKADDR)&ServerAddr, sizeof(ServerAddr))){
		cout << "接口捆绑失败（bind Fail）" << endl;

	}
	if (listen(ServerSocket, 5)){
		cout << "监听失败（listen Fail）" << endl;

	}

	sockaddr_in Clientaddr;
	SOCKET ClientSocket;
	int lAddrlen = sizeof(Clientaddr);
	cout << "服务器初始化成功，正在监听" << endl;


		ClientSocket = accept(ServerSocket, (LPSOCKADDR)&Clientaddr, &lAddrlen);

		if (ClientSocket == INVALID_SOCKET){
			cout << "连接失败" << endl;
		}
		else{
			cout << "连接到地址:" << inet_ntoa(Clientaddr.sin_addr) << endl;
		}
	while (TRUE){
		cout << "准备接受信息" << endl;
		char RecvMessage[1024];
		int MessageLen = recv(ClientSocket, RecvMessage, sizeof(RecvMessage), 0);
		if (MessageLen<0){
			cout << "接受信息失败" << endl;

		}
		else{
			RecvMessage[MessageLen] = 0x00;
			cout <<"接受成功，信息为：" <<RecvMessage << endl;
		}
		cout << "准备发送信息" << endl;
		cout << "请输入发送信息" << endl;
		char  Message[100] ;
		cin >> Message;
		cout << "发送信息：" << Message << endl;
		if (send(ClientSocket, Message, strlen(Message), 0)<0){
			cout << "发送信息失败" << endl;
		}
		else{
			cout << "发送信息成功" << endl;
		}
	
	}
	closesocket(ClientSocket);
	closesocket(ServerSocket);
	WSACleanup();
	return 0;

}





