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

//���밴ť
void insAll() 
{
    insButton(start);
    insButton(resume);
    insButton(quit);
    insButton(rank);
    insButton(help);
    insButton(back);
}

//������ť
void enableAll() 
{
    enableButton(start);
    enableButton(resume);
    enableButton(quit);
    enableButton(rank);
    enableButton(help);
}

//�رհ�ť
void disableAll() 
{
    disableButton(start);
    disableButton(resume);
    disableButton(quit);
    disableButton(rank);
    disableButton(help);
}

void wordbox(double x, double y, char *b)//����ʼ������ӻ��İ�ť 
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

void drawStartPage(double width, double height) //����ʼ����
{
    SetPenColor("White");
    drawFilledRect(width, height, -width, -height);

    DrawManRight(width / 2 - 1.5, height / 2);
	DrawManLeft(width / 2 - 3.7, height / 2 );
	DrawManUp(width / 2 - 2.7, height / 2+2);
	DrawManDown(width / 2 - 2.7, height / 2-2);
	DrawGameBox(width / 2 - 2.7, height / 2 );
	
	wordbox(width / 2, height / 2 + 2, "��ʼ��Ϸ");
    wordbox(width / 2 + 0.8, height / 2 + 1, "������Ϸ");
    wordbox(width / 2 + 1.6, height / 2, "�˳���Ϸ");
    wordbox(width / 2 + 0.8, height / 2 - 1, "���а�");
    wordbox(width / 2, height / 2 - 2, "����");
}

void closeModal() // �ر�ģ̬��
{
//    enableAll();
    disableButton(back);
    initStartPage();
}

void openModal() // ��ģ̬��
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

void intro() // ����˵��
{
	
    openModal();
    double ox = width * 3 / 8 + 0.2, oy = height * 3 / 4 - 0.5, lineHeight = 0.4;
    SetPointSize(20);
    SetPenColor("Black");
	MovePen(ox, oy);
    DrawTextString("��Ϸ˵����");
    oy -= lineHeight;
    
	MovePen(ox, oy);
    DrawTextString("ͨ�������ͷ�����Ʋ��");
    oy -= lineHeight;
    
	MovePen(ox, oy);
    DrawTextString("��ľͰ�͵�Ŀ�ĵ�");
    oy -= lineHeight;
    
	MovePen(ox, oy);
    DrawTextString("Ŭ�������ʱ���������ٵĲ���������");
    oy -= lineHeight;
    
	MovePen(ox, oy);
    DrawTextString("�����ɱ���ѹ��~");
    oy -= lineHeight;
    
    MovePen(ox, oy);
    DrawTextString("���յķ���=ʣ��ʱ��*ʣ�ಽ��");
    oy -= lineHeight;
    
}

void initStartPage() //��ʼ����ʼ����
{
    width = GetWindowWidth();
    height = GetWindowHeight();

    drawStartPage(width, height);//��ҳ�� 

    double buttonWidth = width / 8;
    double buttonHeight = 1;
    double delta = 0.05;

//    if (start == NULL)
//    {
        start = createButton(width / 2, height / 2 + 2, buttonWidth, buttonHeight, "��ʼ��Ϸ", &startGame);
        resume = createButton(width / 2 + 0.8, height / 2 + 1, buttonWidth, buttonHeight, "������Ϸ", &resumeGame);
        quit = createButton(width / 2 + 1.6, height / 2, buttonWidth, buttonHeight, "�˳���Ϸ", &quitGame);
        rank = createButton(width / 2 + 0.8, height / 2 - 1, buttonWidth, buttonHeight, "���а���", &displayRank);
        help = createButton(width / 2, height / 2 - 2, buttonWidth, buttonHeight, "����", &intro);

        buttonWidth = 0.6, buttonHeight = 0.3, delta = 0.05;
        back = createButton(width * 5 / 8 - buttonWidth - delta, height / 4 + delta, buttonWidth, buttonHeight, "����", &closeModal);

        registerKeyboardEvent(KeyboardEventProcess1);
        registerMouseEvent(buttonCallBack);
        insAll();//��������button 
//    }
    	enableAll();
}

void startGame() //��ʼ��Ϸ
{	
    disableAll();//�ðѰ�ť���� 
    clearScreen();
    RePlayGame();
}

void startGame1() //��ʼ��Ϸ
{	
    disableAll();//�ðѰ�ť���� 
    clearScreen();
    PlayGame();
}

void resumeGame() //������Ϸ
{
    disableAll();//�ðѰ�ť���� 
    loadGame();
}

void quitGame() //�˳���Ϸ
{
    ExitGraphics();//���ú��� 
}

void displayRank() // ��ʾ����
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
    SetFont("΢���ź�"); 
    DrawTextString("����             ����");
    
    
 for (j = 0; j < i; j++)
    {
        oy -= lineHeight;
        MovePen(ox, oy);
        sprintf(buffer, "%-18d%-18d", j + 1, scores[j]);
        DrawTextString(buffer);
    }
 fclose(fp);
}

void KeyboardEventProcess1(int key,int event)//ÿ������������Ϣ����Ҫִ�У����������������ݰ���
{	 
     switch (event) {
	 	case KEY_DOWN:
			 switch (key) {
			     case VK_F1://��ʼ��Ϸ��ݼ� 
			     	startGame();
					 break;
			     case VK_F2://������Ϸ��ݼ� 
			     	resumeGame();
                     break;
			     case VK_F3://�˳���Ϸ��ݼ� 
			     	quitGame();
			     	break;
			     case VK_F4://չʾ���а��ݼ� 
			     	displayRank();
			     	break;
			     case VK_F5://չʾ������ݼ� 
			     	intro();
                     break;
                case VK_ESCAPE://չʾ������ݼ� 
			     	closeModal();
                     break;
			 }
			 break;
		case KEY_UP:
			 break;
	 }	 
}

