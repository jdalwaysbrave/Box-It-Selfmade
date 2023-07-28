#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "graphics.h"
#include "extgraph.h"
#include "draw.h"
#include "genlib.h"
#include "conio.h" 
#include <windows.h>
#include <olectl.h>
#include <stdio.h>
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h> 

#include "pushbox.h"
#include "begin.h"
#include "components.h"


double width;
double height;
static button *start = NULL;
static button *resume = NULL;
static button *quit = NULL;
static button *rank = NULL;
static button *help = NULL;
static button *back = NULL;

void KeyboardEventProcess1(int,int);

//插入按钮
void insAll() 
{
    insButton(start);
    insButton(resume);
    insButton(quit);
    insButton(rank);
    insButton(help);
    insButton(back);
}

//开启按钮
void enableAll() 
{
    enableButton(start);
    enableButton(resume);
    enableButton(quit);
    enableButton(rank);
    enableButton(help);
}

//关闭按钮
void disableAll() 
{
    disableButton(start);
    disableButton(resume);
    disableButton(quit);
    disableButton(rank);
    disableButton(help);
}

void wordbox(double x, double y, char *b)//画开始界面可视化的按钮 
{
    SetPenColor("Brown");

    MovePen(x - 0.15, y - 0.45);
   
    
	SetPenColor("Black");
    drawFilledRect(x - 0.57, y + 0.15, 1.8, 0.6);

    
	MovePen(x + 0.1, y + 0.4);
    SetPenColor("Red");
    SetPointSize(15);
    DrawTextString(b);
}

void drawStartPage(double width, double height) //画开始界面
{
    SetPenColor("White");
    drawFilledRect(width, height, -width, -height);

    DrawManRight(width / 2 - 1.5, height / 2);
	DrawManLeft(width / 2 - 3.7, height / 2 );
	DrawManUp(width / 2 - 2.7, height / 2+2);
	DrawManDown(width / 2 - 2.7, height / 2-2);
	DrawGameBox(width / 2 - 2.7, height / 2 );
	
	wordbox(width / 2, height / 2 + 2, "开始游戏");
    wordbox(width / 2 + 0.8, height / 2 + 1, "继续游戏");
    wordbox(width / 2 + 1.6, height / 2, "退出游戏");
    wordbox(width / 2 + 0.8, height / 2 - 1, "排行榜");
    wordbox(width / 2, height / 2 - 2, "帮助");
}

void closeModal() // 关闭模态框
{
//    enableAll();
    disableButton(back);
    initStartPage();
}

void openModal() // 打开模态框
{
    double modalWidth = width, modalHeight = height;
    disableAll();
    enableButton(back);
    SetPenColor("White");
    StartFilledRegion(1);
    RoundRectangle(width / 2 - modalWidth / 2, height / 2 - modalHeight / 2, modalWidth, modalHeight);
    EndFilledRegion();
    drawButton(back);
}

void intro() // 绘制说明
{
	
    openModal();
    double ox = width * 3 / 8 + 0.2, oy = height * 3 / 4 - 0.5, lineHeight = 0.4;
    SetPointSize(20);
    SetPenColor("Black");
	MovePen(ox, oy);
    DrawTextString("游戏说明：");
    oy -= lineHeight;
    
	MovePen(ox, oy);
    DrawTextString("通过方向箭头来控制柴哥");
    oy -= lineHeight;
    
	MovePen(ox, oy);
    DrawTextString("将木桶送到目的地");
    oy -= lineHeight;
    
	MovePen(ox, oy);
    DrawTextString("努力在最短时间内用最少的步数做到！");
    oy -= lineHeight;
    
	MovePen(ox, oy);
    DrawTextString("放轻松别有压力~");
    oy -= lineHeight;
    
    MovePen(ox, oy);
    DrawTextString("最终的分数=剩余时间*剩余步数");
    oy -= lineHeight;
    
}

void initStartPage() //初始化开始界面
{
    width = GetWindowWidth();
    height = GetWindowHeight();

    drawStartPage(width, height);//画页面 

    double buttonWidth = width / 8;
    double buttonHeight = 1;
    double delta = 0.05;

//    if (start == NULL)
//    {
        start = createButton(width / 2, height / 2 + 2, buttonWidth, buttonHeight, "开始游戏", &startGame);
        resume = createButton(width / 2 + 0.8, height / 2 + 1, buttonWidth, buttonHeight, "继续游戏", &resumeGame);
        quit = createButton(width / 2 + 1.6, height / 2, buttonWidth, buttonHeight, "退出游戏", &quitGame);
        rank = createButton(width / 2 + 0.8, height / 2 - 1, buttonWidth, buttonHeight, "排行榜捏", &displayRank);
        help = createButton(width / 2, height / 2 - 2, buttonWidth, buttonHeight, "帮助", &intro);

        buttonWidth = 0.6, buttonHeight = 0.3, delta = 0.05;
        back = createButton(width * 5 / 8 - buttonWidth - delta, height / 4 + delta, buttonWidth, buttonHeight, "返回", &closeModal);

        registerKeyboardEvent(KeyboardEventProcess1);
        registerMouseEvent(buttonCallBack);
        insAll();//插入所有button 
//    }
    	enableAll();
}

void startGame() //开始游戏
{	
    disableAll();//得把按钮撤掉 
    clearScreen();
    RePlayGame();
}

void startGame1() //开始游戏
{	
    disableAll();//得把按钮撤掉 
    clearScreen();
    PlayGame();
}

void resumeGame() //继续游戏
{
    disableAll();//得把按钮撤掉 
    loadGame();
}

void quitGame() //退出游戏
{
    ExitGraphics();//内置函数 
}

void displayRank() // 显示排名
{	
    openModal();
    
 FILE *fp = fopen(rankfile, "r");
    int scores[RankNum], i = 0, j;
    char buffer[MAX_TEXT_LENGTH];
    while (~fscanf(fp, "%d", &scores[i]))
        i++;
    
 double ox = width * 3 / 8 + 0.2, oy = height * 3 / 4 - 0.5, lineHeight = 0.4;
 	double x=GetWindowWidth();
	double y=GetWindowHeight();
    MovePen(ox, oy);
    SetFont("微软雅黑"); 
    DrawTextString("排名             分数");
    
    
 for (j = 0; j < i; j++)
    {
        oy -= lineHeight;
        MovePen(ox, oy);
        sprintf(buffer, "%-18d%-18d", j + 1, scores[j]);
        DrawTextString(buffer);
    }
 fclose(fp);
}

void KeyboardEventProcess1(int key,int event)//每当产生键盘消息，都要执行，这里用于主界面快捷按键
{	 
     switch (event) {
	 	case KEY_DOWN:
			 switch (key) {
			     case VK_F1://开始游戏快捷键 
			     	startGame();
					 break;
			     case VK_F2://继续游戏快捷键 
			     	resumeGame();
                     break;
			     case VK_F3://退出游戏快捷键 
			     	quitGame();
			     	break;
			     case VK_F4://展示排行榜快捷键 
			     	displayRank();
			     	break;
			     case VK_F5://展示帮助快捷键 
			     	intro();
                     break;
                case VK_ESCAPE://展示帮助快捷键 
			     	closeModal();
                     break;
			 }
			 break;
		case KEY_UP:
			 break;
	 }	 
}

