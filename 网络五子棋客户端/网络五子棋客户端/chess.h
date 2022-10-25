#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS //vs环境下必须定义，否则无法使用inet_addr函数
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

// 位置
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

// 带文字的按钮类
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
	bool isIn(int point_x, int point_y);	// 判断点是否在按钮范围内
	void draw();							// 绘制按钮
};

//网络套接字
class inter {
	int fd;
public:
	inter(int x) : fd(x) {};
	~inter() = default;
	int sendmessage(string position);
	int getmessage(int& x);
};

//棋盘类
class ChessBoard
{
	HWND window;													// 窗口句柄，方便操作
	bool	is_black = true;										// 轮到黑子下棋还是白子
	unordered_set<int> black_chesses;								// 存储已经下过的黑子坐标，方便检查判定
	unordered_set<int> white_chesses;								// 存储已经下过的白子坐标，方便检查判定
	int		g_Map[15][15] = {};										// 棋盘，1 为黑子，2 为白子，0 为无子
	COLORREF background_color = RGB(255, 205, 150);					// 棋盘背景色
	int left_padding = 30;											// 棋盘左边距
	int top_padding = 33;											// 棋盘上边距
	int spacing = 40;												// 棋盘格子间距
	Position mouse_position = Position{ -1,-1 };					// 鼠标位置
	inter another;													// 另一位朋友的socket描述符
	const int mod = 999906853;										// 棋盘位置手动哈希
	pair<int, int> pre_one = make_pair(-1, -1), pre_two = make_pair(-1, -1);	//悔棋需要的两个历史坐标
	//八个方向，深度优先遍历准备数组
	const vector<vector<int>> dic = { {0, 1}, {0, -1}, {1, 0}, {-1, 0}, {1, 1}, {-1, -1}, {1, -1}, {-1, 1} };

	TextButton initButton = TextButton(left_padding + 16 * spacing + 20, top_padding + 5 * spacing + 75, L"重新开始");
	TextButton regret = TextButton(left_padding + 16 * spacing + 20, top_padding + 6 * spacing + 75, L"悔棋");
public:
	int	who_win = 0;													// 1 为黑子获胜，2 为白子获胜，0 为平局
	bool my_turn = false;

	ChessBoard(HWND wd, int fd) : black_chesses(0), white_chesses(0), another(fd), window(wd) {};
	~ChessBoard() = default;

	bool check_temp(int temp);											// 错误处理函数
	void init();														// 初始化
	void draw(Position last);											// 绘制游戏界面
	void drawPromptBox(const Position& p);								// 绘制提示框
	bool oneWin(bool is_black, int x, int y);							// 判断是否有一方胜利
	bool oleno_turn();													// 我的回合！
	bool another_turn();												// 敌方的回合
	void Regret();														// 悔棋程序
	void set_pre(int x, int y);														// 设置历史坐标
	bool check_regret();												// 检查是否满足悔棋条件
	void play();														// 开始游戏
};