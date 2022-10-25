#include "chess.h"

void play(int fd) {
	HWND wnd = initgraph(800, 620);		// 创建绘图窗口
	SetWindowText(wnd, L"五子棋");		//设置窗口的标题
	setbkcolor(WHITE);
	setbkmode(TRANSPARENT);				// 设置透明文字输出背景

	ChessBoard chessBoard(wnd, fd);
	chessBoard.my_turn = true;
	do
	{
		chessBoard.init();				// 初始化
		chessBoard.play();				// 开始游戏 
		if (chessBoard.who_win == -1) {
			while(MessageBox(
				wnd,
				L"出现错误",
				L"有可能是对方关闭了链接，请退出",
				MB_YESNO | MB_ICONQUESTION) == IDNO){

			}
			break;
		}
	} while (MessageBox(
		wnd,
		chessBoard.who_win == 1 ? L"恭喜黑方胜利！\n重来一局吗？" : (chessBoard.who_win == 2 ? L"恭喜白方胜利！\n重来一局吗？" : L"居然是平局，太妙了\n重来一局吗？"),
		chessBoard.who_win == 1 ? L"黑子胜利" : (chessBoard.who_win == 2 ? L"白子胜利" : L"平局"),
		MB_YESNO | MB_ICONQUESTION) == IDYES);
	closegraph();	// 关闭绘图窗口（但不会关闭控制台，也就是说你如果用cout输出，这一步之后是可以看得到的控制台）
}

int main()
{
	SOCKET server = 0;
	struct sockaddr_in saddr = { 0 };
	SOCKET client = 0;
	struct sockaddr_in caddr = { 0 };
	int csize = 0;
	char buf[32] = { 0 };
	int r = 0;

	WSADATA wd = { 0 };

	if (WSAStartup(MAKEWORD(2, 2), &wd) != 0)
	{
		cout << "startup error\n";
		return -1;
	}

	//新建一个socket描述符
	server = socket(PF_INET, SOCK_STREAM, 0);

	if (server == INVALID_SOCKET)
	{
		cout << "server socket error\n";

		return -1;
	}

	//命名描述符，绑定在本地的2403端口
	saddr.sin_family = AF_INET;
	saddr.sin_addr.s_addr = htonl(INADDR_ANY);
	saddr.sin_port = htons(2403);

	if (bind(server, (struct sockaddr*)&saddr, sizeof(saddr)) == SOCKET_ERROR)
	{
		cout << "server bind error\n";

		return -1;
	}

	//打开监听
	if (listen(server, 1) == SOCKET_ERROR)
	{
		cout << "server listen error\n";

		return -1;
	}

	csize = sizeof(caddr);
	//接受来自客户端的链接
	client = accept(server, (struct sockaddr*)&caddr, &csize);

	if (client == INVALID_SOCKET)
	{
		cout << "server accept error\n";

		return -1;
	}

	
	play(client);
	closesocket(client);
	closesocket(server);
	return 0;
}