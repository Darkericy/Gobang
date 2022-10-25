#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS //vs�����±��붨�壬�����޷�ʹ��inet_addr����
#define WIN32_LEAN_AND_MEAN
#define NO_RESTART 1
#define RESTART 2
#define NO_REGRET 3
#define REGRET 4
#include <WinSock2.h>
#pragma comment(lib,"ws2_32.lib")
typedef struct sockaddr_in sockaddr_in;
typedef struct WSAData WSAData;
typedef struct sockaddr sockaddr;
#include <easyx.h>
#include <time.h>
#include <conio.h>
#include <iostream>
#include <vector>
#include <graphics.h>
#include <unordered_set>
#include <string>
using namespace std;

// λ��
struct Position
{
	int x = 0;		// 0 <= x <= 14
	int y = 0;		// 0 <= y <= 14
	Position() = default;
	Position(int _x, int _y) : x(_x), y(_y) {};
	bool operator==(const Position& b)
	{
		return x == b.x && y == b.y;
	}
};

// �����ֵİ�ť��
class TextButton
{
public:
	TextButton(int x, int y, LPCTSTR str, COLORREF background_color = RGB(255, 205, 150)) :x(x), y(y), str(str), background_color(background_color) {};
	static const int left = 5;
	static const int top = 5;
	static const int roundRadius = 5;
	int x;
	int y;
	LPCTSTR str;
	COLORREF background_color;
	bool isIn(int point_x, int point_y);	// �жϵ��Ƿ��ڰ�ť��Χ��
	void draw();							// ���ư�ť
};

//�����׽���
class inter {
	int fd;
public:
	inter(int x) : fd(x) {};
	~inter() = default;
	int sendmessage(string position);
	int getmessage(int& x);
};

//������
class ChessBoard
{
	HWND window;													// ���ھ�����������
	bool	is_black = true;										// �ֵ��������廹�ǰ���
	unordered_set<int> black_chesses;								// �洢�Ѿ��¹��ĺ������꣬�������ж�
	unordered_set<int> white_chesses;								// �洢�Ѿ��¹��İ������꣬�������ж�
	int		g_Map[15][15] = {};										// ���̣�1 Ϊ���ӣ�2 Ϊ���ӣ�0 Ϊ����
	COLORREF background_color = RGB(255, 205, 150);					// ���̱���ɫ
	int left_padding = 30;											// ������߾�
	int top_padding = 33;											// �����ϱ߾�
	int spacing = 40;												// ���̸��Ӽ��
	Position mouse_position = Position{ -1,-1 };					// ���λ��
	inter another;													// ��һλ���ѵ�socket������
	const int mod = 999906853;										// ����λ���ֶ���ϣ
	pair<int, int> pre_one = make_pair(-1, -1), pre_two = make_pair(-1, -1);	//������Ҫ��������ʷ����
	//�˸�����������ȱ���׼������
	const vector<vector<int>> dic = { {0, 1}, {0, -1}, {1, 0}, {-1, 0}, {1, 1}, {-1, -1}, {1, -1}, {-1, 1} };

	TextButton initButton = TextButton(left_padding + 16 * spacing + 20, top_padding + 5 * spacing + 75, L"���¿�ʼ");
	TextButton regret = TextButton(left_padding + 16 * spacing + 20, top_padding + 6 * spacing + 75, L"����");
public:
	int	who_win = 0;													// 1 Ϊ���ӻ�ʤ��2 Ϊ���ӻ�ʤ��0 Ϊƽ��
	bool my_turn = false;

	ChessBoard(HWND wd, int fd) : black_chesses(0), white_chesses(0), another(fd), window(wd) {};
	~ChessBoard() = default;

	bool check_temp(int temp);											// ��������
	void init();														// ��ʼ��
	void draw(Position last);											// ������Ϸ����
	void drawPromptBox(const Position& p);								// ������ʾ��
	bool oneWin(bool is_black, int x, int y);							// �ж��Ƿ���һ��ʤ��
	bool oleno_turn();													// �ҵĻغϣ�
	bool another_turn();												// �з��Ļغ�
	void Regret();														// �������
	void set_pre(int x, int y);														// ������ʷ����
	bool check_regret();												// ����Ƿ������������
	void play();														// ��ʼ��Ϸ
};