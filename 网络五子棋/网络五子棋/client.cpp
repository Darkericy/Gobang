//#include "chess.h"
//
//void play(int fd) {
//	HWND wnd = initgraph(800, 620);		// ������ͼ����
//	SetWindowText(wnd, L"������");		//���ô��ڵı���
//	setbkcolor(WHITE);
//	setbkmode(TRANSPARENT);				// ����͸�������������
//
//	ChessBoard chessBoard(fd);
//	chessBoard.my_turn = false;
//	do
//	{
//		chessBoard.init();				// ��ʼ��
//		chessBoard.play();				// ��ʼ��Ϸ 
//		if (chessBoard.who_win == -1) {
//			while (MessageBox(
//				wnd,
//				L"���ִ���",
//				L"�п����ǶԷ��ر������ӣ����˳�",
//				MB_YESNO | MB_ICONQUESTION) == IDNO) {
//
//			}
//			break;
//		}
//	} while (MessageBox(
//		wnd,
//		chessBoard.who_win == 1 ? L"��ϲ�ڷ�ʤ����\n����һ����" : (chessBoard.who_win == 2 ? L"��ϲ�׷�ʤ����\n����һ����" : L"��Ȼ��ƽ�֣�̫����\n����һ����"),
//		chessBoard.who_win == 1 ? L"����ʤ��" : (chessBoard.who_win == 2 ? L"����ʤ��" : L"ƽ��"),
//		MB_YESNO | MB_ICONQUESTION) == IDYES);
//	closegraph();	// �رջ�ͼ���ڣ�������رտ���̨��Ҳ����˵�������cout�������һ��֮���ǿ��Կ��õ��Ŀ���̨��
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