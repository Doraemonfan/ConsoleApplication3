
#include "stdafx.h"
#include <graphics.h>
#include <conio.h>
#define Width 640
#define High 480

int ball_x, ball_y, radius, ball_v_x, ball_v_y;
int ball_2_x, ball_2_y, radius_2, ball_2_v_x, ball_2_v_y;
int bar_1_length, bar_1_width, bar_1_left, bar_1_right, bar_1_top, bar_1_bottom;
int bar_2_length, bar_2_width, bar_2_left, bar_2_right, bar_2_top, bar_2_bottom;
int bar_move_step;
int isFail;


void startup() {
	ball_x = Width / 2;
	ball_y = High / 2;
	radius = 20;
	ball_v_x = 1;
	ball_v_y = 1;

	ball_2_x = Width / 4;
	ball_2_y = High / 3;
	radius_2 = 20;
	ball_2_v_x = -1;
	ball_2_v_y = -1;
	
	bar_1_length = High / 4;
	bar_1_width = radius;
	bar_1_left = radius;
	bar_1_right = bar_1_left + bar_1_width;
	bar_1_top = High / 2 - bar_1_length / 2;
	bar_1_bottom = bar_1_top + bar_1_length;

	bar_2_length = High / 4;
	bar_2_width = radius;
	bar_2_right = Width - radius;
	bar_2_left = bar_2_right - bar_2_width;
	bar_2_top = High / 2 - bar_2_length / 2;
	bar_2_bottom = bar_2_top + bar_2_length;

	bar_move_step = 2;
	isFail = 0;

	initgraph(Width, High);
	BeginBatchDraw();
}

void show() {
	setcolor(WHITE);
	setfillcolor(GREEN);
	fillcircle(ball_x, ball_y, radius);
	setfillcolor(YELLOW);
	fillcircle(ball_2_x, ball_2_y, radius_2);
	
	setcolor(WHITE);
	setfillcolor(BLUE);
	fillrectangle(bar_1_left, bar_1_top, bar_1_right, bar_1_bottom);
	fillrectangle(bar_2_left, bar_2_top, bar_2_right, bar_2_bottom);

	if (isFail) {
		settextcolor(RED);
		settextstyle(64, 0, _T("ËÎÌו"));
		outtextxy(Width / 4, High / 3, _T("Game over!"));
		FlushBatchDraw();
		system("pause");
		exit(0);
	}
	
	FlushBatchDraw();
	Sleep(5);

	setcolor(BLACK);
	setfillcolor(BLACK);
	fillcircle(ball_x, ball_y, radius);
	fillcircle(ball_2_x, ball_2_y, radius_2);
	fillrectangle(bar_1_left, bar_1_top, bar_1_right, bar_1_bottom);
	fillrectangle(bar_2_left, bar_2_top, bar_2_right, bar_2_bottom);
}

void updateWithoutInput() {

	if (ball_y - radius== 0 || ball_y + radius == High) ball_v_y = -ball_v_y;

	if (ball_x - radius == bar_1_right && ball_y >= bar_1_top && ball_y <= bar_1_bottom) ball_v_x = -ball_v_x;
	else if (ball_x + radius == bar_2_left && ball_y >= bar_2_top && ball_y <= bar_2_bottom) ball_v_x = -ball_v_x;

	if (ball_2_y - radius_2 == 0 || ball_2_y + radius_2 == High) ball_2_v_y = -ball_2_v_y;

	if (ball_2_x - radius_2 == bar_1_right && ball_2_y >= bar_1_top && ball_2_y <= bar_1_bottom) ball_2_v_x = -ball_2_v_x;
	else if (ball_2_x + radius_2 == bar_2_left && ball_2_y >= bar_2_top && ball_2_y <= bar_2_bottom) ball_2_v_x = -ball_2_v_x;

	int distance_2 = (ball_x - ball_2_x) * (ball_x - ball_2_x) + (ball_y - ball_2_y) * (ball_y - ball_2_y);
	int sum_radius_2 = (radius + radius_2) * (radius + radius_2);
	if (distance_2 <= sum_radius_2) {
		int temp;
		temp = ball_v_x; ball_v_x = ball_2_v_x; ball_2_v_x = temp;
		temp = ball_v_y; ball_v_y = ball_2_v_y; ball_2_v_y = temp;
	}

	if ((ball_x < 0 || ball_x > Width) || (ball_2_x < 0 || ball_2_x > Width)) isFail = 1;
	ball_x += ball_v_x;
	ball_y += ball_v_y;

	ball_2_x += ball_2_v_x;
	ball_2_y += ball_2_v_y;
}

void updateWithInput() {
	//if (_kbhit()) {
		if ((GetAsyncKeyState(0x57) & 0x80000) && bar_1_top > radius) bar_1_top -= bar_move_step;
		if ((GetAsyncKeyState(0x53) & 0x80000) && bar_1_bottom < High - radius) bar_1_top += bar_move_step;
		if ((GetAsyncKeyState(VK_UP) & 0x80000) && bar_2_top > radius) bar_2_top -= bar_move_step;
		if ((GetAsyncKeyState(VK_DOWN) & 0x80000) && bar_2_bottom < High - radius) bar_2_top += bar_move_step;
		
		bar_1_bottom = bar_1_top + bar_1_length;
		bar_2_bottom = bar_2_top + bar_2_length;
	//}
}

int main() {
	
	startup();
	for (;;) {
		show();
		updateWithoutInput();
		updateWithInput();
	}
	EndBatchDraw();
	closegraph();
	return 0;
}