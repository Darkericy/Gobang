#include "chess.h"

void play(int fd) {
	HWND wnd = initgraph(800, 620);		// ������ͼ����
	SetWindowText(wnd, L"������");		//���ô��ڵı���
	setbkcolor(WHITE);
	setbkmode(TRANSPARENT);				// ����͸�������������

	ChessBoard chessBoard(wnd, fd);
	chessBoard.my_turn = true;
	do
	{
		chessBoard.init();				// ��ʼ��
		chessBoard.play();				// ��ʼ��Ϸ 
		if (chessBoard.who_win == -1) {
			while(MessageBox(
				wnd,
				L"���ִ���",
				L"�п����ǶԷ��ر������ӣ����˳�",
				MB_YESNO | MB_ICONQUESTION) == IDNO){

			}
			break;
		}
	} while (MessageBox(
		wnd,
		chessBoard.who_win == 1 ? L"��ϲ�ڷ�ʤ����\n����һ����" : (chessBoard.who_win == 2 ? L"��ϲ�׷�ʤ����\n����һ����" : L"��Ȼ��ƽ�֣�̫����\n����һ����"),
		chessBoard.who_win == 1 ? L"����ʤ��" : (chessBoard.who_win == 2 ? L"����ʤ��" : L"ƽ��"),
		MB_YESNO | MB_ICONQUESTION) == IDYES);
	closegraph();	// �رջ�ͼ���ڣ�������رտ���̨��Ҳ����˵�������cout�������һ��֮���ǿ��Կ��õ��Ŀ���̨��
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

	//�½�һ��socket������
	server = socket(PF_INET, SOCK_STREAM, 0);

	if (server == INVALID_SOCKET)
	{
		cout << "server socket error\n";

		return -1;
	}

	//���������������ڱ��ص�2403�˿�
	saddr.sin_family = AF_INET;
	saddr.sin_addr.s_addr = htonl(INADDR_ANY);
	saddr.sin_port = htons(2403);

	if (bind(server, (struct sockaddr*)&saddr, sizeof(saddr)) == SOCKET_ERROR)
	{
		cout << "server bind error\n";

		return -1;
	}

	//�򿪼���
	if (listen(server, 1) == SOCKET_ERROR)
	{
		cout << "server listen error\n";

		return -1;
	}

	csize = sizeof(caddr);
	//�������Կͻ��˵�����
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