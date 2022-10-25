#include "chess.h"
//��ť����ʵ��
bool TextButton::isIn(int point_x, int point_y)
{
	if (point_x >= x && point_x <= x + textwidth(str) + 2 * left && point_y >= y && point_y <= y + textheight(str) + 2 * top)
		return true;
	else
		return false;
}

void TextButton::draw()
{
	auto pstyle = std::make_shared<LINESTYLE>();
	getlinestyle(pstyle.get());
	setlinestyle(PS_SOLID, 1);
	COLORREF tempColor = getfillcolor();
	setfillcolor(background_color);         // �����ɫ����
	fillroundrect(x, y, x + textwidth(str) + 2 * left, y + textheight(str) + 2 * top, roundRadius, roundRadius);
	setfillcolor(tempColor);
	setlinestyle(pstyle.get());
	outtextxy(x + left, y + top, str);
}

//���̺���ʵ��
void ChessBoard::Regret() {
	if (pre_one.first != -1) {
		g_Map[pre_one.first][pre_one.second] = 0;
	}
	if (pre_two.first != -1) {
		g_Map[pre_two.first][pre_two.second] = 0;
	}
	draw(Position(pre_one.first, pre_one.second));
	pre_one = make_pair(-1, -1);
}

bool ChessBoard::check_regret() {
	if (black_chesses.size() + white_chesses.size() >= 2 && pre_one.first != -1) {
		return true;
	}
	return false;
}

void ChessBoard::set_pre(int x, int y) {
	pre_two = pre_one;
	pre_one = make_pair(x, y);
}

bool ChessBoard::check_temp(int temp) {
	if (temp == 0 || temp == SOCKET_ERROR) {
		who_win = -1;
		return true;
	}
	return false;
}

void ChessBoard::init()
{
	// ������ʼ��
	is_black = true;
	who_win = 0;
	black_chesses.clear();
	white_chesses.clear();
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			g_Map[i][j] = 0;
		}
	}
	// ����󻺳���
	draw(Position(top_padding, left_padding));
	flushmessage();
}

void ChessBoard::drawPromptBox(const Position& p)
{
	// ������������ɫ����ʾ��
	COLORREF linecolor = getlinecolor();
	int half_spacing = spacing / 2;
	int length = spacing / 3;
	int x = p.x * spacing + left_padding;
	int y = p.y * spacing + top_padding;
	setlinestyle(PS_SOLID, 2);
	setlinecolor(RED);
	// ���Ͻ�
	line(x - half_spacing, y - half_spacing, x - half_spacing, y - half_spacing + length);	// ��
	line(x - half_spacing, y - half_spacing, x - half_spacing + length, y - half_spacing);	// ��
	setlinecolor(YELLOW);
	// ���Ͻ�
	line(x + half_spacing, y - half_spacing, x + half_spacing, y - half_spacing + length);	// ��
	line(x + half_spacing, y - half_spacing, x + half_spacing - length, y - half_spacing);	// ��
	setlinecolor(GREEN);
	// ���Ͻ�
	line(x - half_spacing, y + half_spacing, x - half_spacing, y + half_spacing - length);	// ��
	line(x - half_spacing, y + half_spacing, x - half_spacing + length, y + half_spacing);	// ��
	setlinecolor(BLUE);
	// ���½�
	line(x + half_spacing, y + half_spacing, x + half_spacing, y + half_spacing - length);	// ��
	line(x + half_spacing, y + half_spacing, x + half_spacing - length, y + half_spacing);	// ��
	setlinecolor(linecolor);
}

void ChessBoard::draw(Position last)
{
	BeginBatchDraw();						// ��ʼ�������ƣ���ֹ��˸�õ�
	setlinestyle(PS_SOLID, 2);
	cleardevice();							// ����
	// ������
	setfillcolor(background_color);         // �����ɫ����
	solidrectangle(0, 0, 14 * spacing + left_padding * 2, 14 * spacing + top_padding * 2);
	settextcolor(BLACK);
	int number = 0;
	// ���꣨��ֵ��
	TCHAR strnum[15][3] = { _T("1"),_T("2") ,_T("3") ,_T("4"),_T("5") ,_T("6") ,_T("7"),_T("8"),_T("9"),_T("10"), _T("11"),_T("12") ,_T("13") ,_T("14"),_T("15") };
	// ���꣨��ĸ��
	TCHAR strabc[15][3] = { _T("A"),_T("B") ,_T("C") ,_T("D"),_T("E") ,_T("F") ,_T("G"),_T("H"),_T("I"),_T("J"), _T("K"),_T("L") ,_T("M") ,_T("N"),_T("O") };
	// ������
	for (int i = 0; i < 15; i++)
	{
		outtextxy(left_padding + number - 6, top_padding - 23, strnum[i]);
		outtextxy(left_padding - 14, top_padding + number - 6, strabc[i]);
		number += spacing;
	}
	setlinecolor(BLACK);
	for (int x = 0; x < 15; x++)				// ������
		line(left_padding, x * spacing + top_padding, 14 * spacing + left_padding, x * spacing + top_padding);
	for (int y = 0; y < 15; y++)				// ������
		line(y * spacing + left_padding, top_padding, y * spacing + left_padding, 14 * spacing + top_padding);
	// �������λ
	for (int i : {3, 7, 11})
	{
		for (int j : {3, 7, 11})
		{
			setfillcolor(BLACK);
			fillcircle(i * spacing + left_padding, j * spacing + top_padding, 4);
		}
	}
	for (int x = 0; x < 15; x++)				// ������
	{
		for (int y = 0; y < 15; y++) {
			if (g_Map[x][y] == 1) {
				setfillcolor(BLACK);
				fillcircle(x * spacing + left_padding, y * spacing + top_padding, 15);
			}
			else if (g_Map[x][y] == 2) {
				setfillcolor(WHITE);
				fillcircle(x * spacing + left_padding, y * spacing + top_padding, 15);
			}
		}
	}
	// ���һ�����ӻ�����ʾ�߿�
	if (black_chesses.size() == white_chesses.size())
	{
		if (!white_chesses.empty())
		{
			drawPromptBox(last);
		}
	}
	else
	{
		if (!black_chesses.empty())
		{
			drawPromptBox(last);
		}
	}
	if (mouse_position.x != -1)
	{
		drawPromptBox(mouse_position);
	}

	LOGFONT* font = new LOGFONT();
	gettextstyle(font);
	settextstyle(30, 0, L"����", 0, 0, 4, false, false, false, 0, OUT_TT_ONLY_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH);
	settextcolor(BLACK);
	outtextxy(15 * spacing + 2 * left_padding, top_padding, L"������");
	settextstyle(font);

	// �������¿�ʼ��ť
	initButton.draw();
	regret.draw();

	EndBatchDraw(); // ������������
}

bool ChessBoard::oneWin(bool is_black, int x, int y)
{
	for (int i = 0; i < 8; ++i) {
		int nx = x, ny = y;
		bool win = true;
		for (int j = 1; j < 5; ++j) {
			nx += dic[i][0];
			ny += dic[i][1];
			int step = nx * mod + ny;
			if (is_black) {
				if (black_chesses.find(step) == black_chesses.end()) {
					win = false;
					break;
				}
			}
			else {
				if (white_chesses.find(step) == white_chesses.end()) {
					win = false;
					break;
				}
			}
		}
		if (win) {
			who_win = is_black ? 1 : 2;
			return true;
		}
	}
	return false;
}

bool ChessBoard::oleno_turn() {
	ExMessage msg;
	msg = getmessage(EX_MOUSE);				// ��ȡ�����Ϣ
	//��������������
	if (msg.x >= left_padding && msg.x < 14 * spacing + left_padding && msg.y >= top_padding && msg.y < 14 * spacing + top_padding) {
		//�ж����Ŀǰ��λ��
		int x = (msg.x - left_padding + spacing / 2) / spacing;
		int y = (msg.y - top_padding + spacing / 2) / spacing;
		mouse_position.x = x;
		mouse_position.y = y;
		Position temp(x, y);
		switch (msg.message) {
		case WM_MOUSEMOVE:
			draw(temp);
			break;
		case WM_LBUTTONDOWN:
			if (g_Map[x][y] == 0) {
				if (is_black) {
					g_Map[x][y] = 1;
					black_chesses.insert(x * mod + y);
				}
				else {
					g_Map[x][y] = 2;
					white_chesses.insert(x * mod + y);
				}
				set_pre(x, y);
				draw(temp);
				string s1 = to_string(x);
				string s2 = to_string(y);
				another.sendmessage(s1);
				another.sendmessage(s2);
				if (oneWin(is_black, x, y)) {
					return true;
				}
				is_black = !is_black;
				my_turn = !my_turn;
			}
			else {
				draw(temp);
			}
		}
	}
	//�������
	else {
		if (msg.message == WM_LBUTTONDOWN) {
			//����Ƿ�㵽�����¿�ʼ���߻��尴ť
			Position temp(left_padding, top_padding);
			//���¿�ʼ�������
			if (initButton.isIn(msg.x, msg.y))
			{
				MessageBox(window, L"��Է����������������ĵȴ�", L"�ؿ���", MB_OK);
				string x = to_string(msg.x);
				string y = to_string(msg.y);
				another.sendmessage(x);
				another.sendmessage(y);
				int ret;
				auto temp = another.getmessage(ret);
				if (check_temp(temp)) {
					return true;
				}
				if (ret == RESTART) {
					MessageBox(window, L"�Է��������������", L"�ɹ�", MB_OK);
					init();
					draw(Position(-1, -1));
				}
				else {
					MessageBox(window, L"�Է��ܾ����������", L"ʧ��", MB_OK);
				}
			}
			if (regret.isIn(msg.x, msg.y)) {
				if (!check_regret()) {
					MessageBox(window, L"��ϧ�㲢�������������", L"���壿", MB_OK);
					return false;
				}
				MessageBox(window, L"��Է����������������ĵȴ�", L"���壿", MB_OK);
				string x = to_string(msg.x);
				string y = to_string(msg.y);
				another.sendmessage(x);
				another.sendmessage(y);
				int ret;
				auto temp = another.getmessage(ret);
				//ʱ�̼��������ܵ�������
				if (check_temp(temp)) {
					return true;
				}
				if (ret == REGRET) {
					MessageBox(window, L"�Է��������������", L"�ɹ�", MB_OK);
					Regret();
				}
				else {
					MessageBox(window, L"�Է��ܾ����������", L"ʧ��", MB_OK);
				}
			}
		}
	}
	return false;
}

bool ChessBoard::another_turn() {
	int x, y;
	auto temp = another.getmessage(x);
	//���ִ���
	if (check_temp(temp)) {
		return true;
	}

	temp = another.getmessage(y);
	//���ִ���
	if (check_temp(temp)) {
		return true;
	}

	Position fallen(x, y);
	//����Ƿ�������¿�ʼ�����ն�
	if (initButton.isIn(x, y))
	{
		int ret;
		if (MessageBox(window, L"�Է��������ؿ�����", L"�ؿ���", MB_YESNO | MB_ICONQUESTION) == IDYES) {
			ret = RESTART;
			another.sendmessage(to_string(ret));
			init();
			draw(Position(-1, -1));
		}
		else {
			ret = NO_RESTART;
			another.sendmessage(to_string(ret));
		}
		return false;
	}
	//����
	if (regret.isIn(x, y)) {
		int ret;
		if (MessageBox(window, L"�Է������˻���", L"����", MB_YESNO | MB_ICONQUESTION) == IDYES) {
			ret = REGRET;
			another.sendmessage(to_string(ret));
			Regret();
		}
		else {
			ret = NO_REGRET;
			another.sendmessage(to_string(ret));
		}
		return false;
	}
	if (g_Map[x][y] == 0) {
		if (is_black) {
			g_Map[x][y] = 1;
			black_chesses.insert(x * mod + y);
		}
		else {
			g_Map[x][y] = 2;
			white_chesses.insert(x * mod + y);
		}
		set_pre(x, y);
		draw(fallen);
		if (oneWin(is_black, x, y)) {
			return true;
		}
		is_black = !is_black;
		my_turn = !my_turn;
	}
	else {
		draw(fallen);
	}
	return false;
}

void ChessBoard::play()
{
	ExMessage msg;
	while (black_chesses.size() < 113)		// ��Ϸ��ѭ��
	{
		if (my_turn) {
			if (oleno_turn()) {
				return;
			}
		}
		else {
			if (another_turn()) {
				return;
			}
		}
	}
}

//����ӿ�
int inter::sendmessage(string line) {
	return send(fd, line.c_str(), line.size() + 1, 0);
}

int inter::getmessage(int& x) {
	char buf[10];
	auto p = recv(fd, buf, 10, 0);

	//��ʱsocket��û������
	if (p == SOCKET_ERROR) {
		return p;
	}
	x = stoi(buf);

	return p;
}