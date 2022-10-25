//#include "chess.h"
//
//void play(int fd) {
//	HWND wnd = initgraph(800, 620);		// 创建绘图窗口
//	SetWindowText(wnd, L"五子棋");		//设置窗口的标题
//	setbkcolor(WHITE);
//	setbkmode(TRANSPARENT);				// 设置透明文字输出背景
//
//	ChessBoard chessBoard(fd);
//	chessBoard.my_turn = false;
//	do
//	{
//		chessBoard.init();				// 初始化
//		chessBoard.play();				// 开始游戏 
//		if (chessBoard.who_win == -1) {
//			while (MessageBox(
//				wnd,
//				L"出现错误",
//				L"有可能是对方关闭了链接，请退出",
//				MB_YESNO | MB_ICONQUESTION) == IDNO) {
//
//			}
//			break;
//		}
//	} while (MessageBox(
//		wnd,
//		chessBoard.who_win == 1 ? L"恭喜黑方胜利！\n重来一局吗？" : (chessBoard.who_win == 2 ? L"恭喜白方胜利！\n重来一局吗？" : L"居然是平局，太妙了\n重来一局吗？"),
//		chessBoard.who_win == 1 ? L"黑子胜利" : (chessBoard.who_win == 2 ? L"白子胜利" : L"平局"),
//		MB_YESNO | MB_ICONQUESTION) == IDYES);
//	closegraph();	// 关闭绘图窗口（但不会关闭控制台，也就是说你如果用cout输出，这一步之后是可以看得到的控制台）
//}
//
//int main() {
//	SOCKET sock = 0;
//	struct sockaddr_in addr = { 0 };
//	char input[32] = { 0 };
//	char buf[128] = { 0 };
//	int n = 0;
//
//	WSADATA wd = { 0 };
//
//	if (WSAStartup(MAKEWORD(2, 2), &wd) != 0)
//	{
//		cout << "startup error\n";
//
//		return -1;
//	}
//
//	sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
//
//	if (sock == INVALID_SOCKET)
//	{
//		cout << "socker error\n";
//
//		return -1;
//	}
//
//	string ip;
//	int port;
//	cin >> ip;
//	cin >> port;
//
//	addr.sin_family = AF_INET;
//	addr.sin_addr.s_addr = inet_addr(ip.c_str());
//	addr.sin_port = htons(port);
//
//	if (connect(sock, (struct sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR)
//	{
//		cout << "connect error\n";
//
//		return -1;
//	}
//
//	play(sock);
//	closesocket(sock);
//	return 0;
//}