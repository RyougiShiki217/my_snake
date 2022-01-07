#include<graphics.h>
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#define snake_max 500
char mode;//游戏模式
bool end;
enum DIR
{
	up,
	down,
	left,
	right,
};
struct Snake//蛇的结构体
{
	int size;//蛇的节数(几节圆)
	int dir;//蛇的朝向
	int speed;//蛇行动的速度
	POINT zb[snake_max];//蛇的坐标
}snake;
struct Food
{
	int x;//食物横坐标
	int y;//食物纵坐标
	int r;//食物大小半径
	DWORD color;//食物颜色
	bool flag;//食物是否被吃，被吃为真，没有被吃为假
}food;
void menu()
{
	initgraph(640, 480);//创建窗口
	setbkcolor(RGB(99, 221, 96));//设置窗口颜色
	cleardevice();//清除黑色
	settextcolor(RED);//设置字体颜色
	settextstyle(30,0,"微软雅黑");//设置字体样式
	outtextxy(260, 50, "贪吃蛇游戏");
	outtextxy(350, 90, "By:Shiki & ZeroTwo");
	outtextxy(275, 130, "0.play");
	outtextxy(275, 170, "1.exit");
	char stk = _getch();
	switch (stk)
	{
	case '0':return;
	case '1':exit(0);
	}
}
void game_mode()
{
	initgraph(640, 480);//创建窗口
	setbkcolor(RGB(99, 221, 96));//设置窗口颜色
	cleardevice();//清除黑色
	settextcolor(RED);//设置字体颜色
	settextstyle(30,0,"微软雅黑");//设置字体样式
	outtextxy(260, 50, "请选择是否有围墙");
	outtextxy(260, 90, "0.有");
	outtextxy(260, 130, "1.无");
	mode = _getch();
}
void gameinit()//程序初始化
{
	srand(GetTickCount());
	initgraph(640, 480);//创建窗口
	snake.size = 3;
	snake.speed = 10;
	snake.dir = right;
	for (int i = 0; i <= snake.size; i++)
	{
		snake.zb[i].x = 60 - i * 10;
		snake.zb[i].y = 20;
	}
	food.x = rand() % 640;
	food.y = rand() % 480;
	food.color = RGB(rand() % 256, rand() % 256, rand() % 256);
	food.r = 8;
	food.flag = true;
}
void drawinit()//绘图
{
	BeginBatchDraw();//开始双缓冲绘图
	setbkcolor(RGB(99, 221, 96));//设置窗口颜色
	cleardevice();//清除黑色
	//设置蛇的颜色
	setfillcolor(RED);
	for (int i = 0; i < snake.size; i++)//画蛇
	{
		solidcircle(snake.zb[i].x, snake.zb[i].y, 5);
	}
	if (food.flag)//画食物
	{
		solidcircle(food.x, food.y, food.r);
	}
	EndBatchDraw();//结束双缓冲绘图
}
bool game_over()
{
	settextcolor(RED);
	outtextxy(50, 50, "Game Over");
	outtextxy(50, 70, "0.返回菜单");
	outtextxy(50, 90, "1.退出游戏");
	while (1)
	{
		char flag = _getch();
		switch (flag)
		{
		case '0':return TRUE;
		case '1':exit(0);
		}
	}
}
void snakemove()
{
	for (int i = snake.size - 1; i > 0; i--)//让身体跟着蛇头移动
	{
		snake.zb[i] = snake.zb[i - 1];//每一节要移动的坐标为上一节的坐标
	}
	switch (snake.dir)//蛇头移动
	{
	case right:
		snake.zb[0].x += snake.speed;
		if (snake.zb[0].x >= 640)
		{
			if (mode == '0')
			{
				end = game_over();
			}
			else if(mode == '1')
			{
				snake.zb[0].x = 0;
			}
		}
		break;
	case left:
		snake.zb[0].x -= snake.speed;
		if (snake.zb[0].x <= 0)
		{
			if (mode == '0')
			{
				end = game_over();
			}
			else if (mode == '1')
			{
				snake.zb[0].x = 640;
			}
		}
		break;
	case up:
		snake.zb[0].y -= snake.speed;
		if (snake.zb[0].y <= 0)
		{
			if (mode == '0')
			{
				end = game_over();
			}
			else if (mode == '1')
			{
				snake.zb[0].y = 480;
			}
		}
		break;
	case down:
		snake.zb[0].y += snake.speed;
		if (snake.zb[0].y >= 480)
		{
			if (mode == '0')
			{
				end = game_over();
			}
			else if (mode == '1')
			{
				snake.zb[0].y = 0;
			}
		}
		break;
	}
}
void control()//键盘改变蛇的方向
{
	if (_kbhit())//如果按了建_kbhit()返回真
	{
		switch (_getch())
		{
		case 'w':
		case 'W':
		case 72:
			if (snake.dir != down)
			{
				snake.dir = up;
			}
			break;
		case 's':
		case 'S':
		case 80:
			if (snake.dir != up)
			{
				snake.dir = down;
			}
			break;
		case 'a':
		case 'A':
		case 75:
			if (snake.dir != right)
			{
				snake.dir = left;
			}
			break;
		case 'd':
		case 'D':
		case 77:
			if (snake.dir != left)
			{
				snake.dir = right;
			}
			break;
		}
	}
}
void eatfood()
{
	if (food.flag == true && snake.zb[0].x >= food.x - food.r && snake.zb[0].x <= food.x + food.r && snake.zb[0].y >= food.y - food.r && snake.zb[0].y <= food.y + food.r)
	{
		food.flag = false;
		snake.size++;
	}
	if (!food.flag)//如果食物消失则再创建一个新的食物
	{
		food.x = rand() % 640;
		food.y = rand() % 480;
		food.color = RGB(rand() % 256, rand() % 256, rand() % 256);
		food.r = 8;
		food.flag = true;
	}
}
void pause()//暂停函数
{
	if (_kbhit())
	{
		if (_getch() == ' ')
		{
			while (_getch() != ' ');
		}
	}
}
void eatself()
{
	for (int k = 1; k < snake.size; k++)
	{
		if (snake.zb[0].x >= snake.zb[k].x - 5 && snake.zb[0].x <= snake.zb[k].x + 5 && snake.zb[0].y >= snake.zb[k].y - 5 && snake.zb[0].y <= snake.zb[k].y + 5)
		{
			end = game_over();
		}
	}
}
void game()
{
	end = FALSE;
	gameinit();
	while (1)
	{
		drawinit();
		eatfood();
		eatself();
		if (end)
		{
			break;
		}
		pause();
		snakemove();
		if (end)
		{
			break;
		}
		control();
		Sleep(100);
	}
}