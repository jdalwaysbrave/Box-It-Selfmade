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
#include "components.h"
#include "begin.h"

//realboxָ������Ҫ�˵�������Ŀ��countΪʣ�ಽ����lasttimeΪʣ��ʱ�� 
//constcountΪ��ʼ������consttimeΪ��ʼʱ�� 
#define realbox 4
int count=constcount;
int lasttime=consttime;

enum
{
    PRESTATE, 
    PAUSED
};                                          //״̬����

static button *pause, *save, *resume, *quit;  // ��Ϸ������ĸ���ť

static int state;

int FindHumanx();
int FindHumany();
void KeyboardEventProcess(int key, int event);
void clearScreen();
void HumanUp(int x,int y);
void HumanDown(int x,int y);
void HumanLeft(x,y); 
void HumanLeft(x,y); 

int map[14][20] = {
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, //0  �յ�
		{1,3,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}, //1  ǽ
		{1,1,0,0,0,0,1,1,1,0,0,0,0,1,0,0,0,0,0,1}, //3  Ŀ�ĵ�
		{1,0,1,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,1}, //4  ʯ����
		{1,0,0,1,0,1,1,7,0,1,1,1,0,0,0,0,0,0,0,1}, //5  ��
		{1,0,0,0,1,1,1,0,0,0,0,1,0,0,0,0,0,0,0,1}, //7  ľ����
		{1,0,0,0,0,1,0,0,0,7,7,1,1,1,1,3,0,0,0,1}, //8  ����+Ŀ�ĵ� 
		{1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,1},
		{1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,1},
		{1,0,0,0,0,1,1,1,0,0,1,0,0,0,0,0,0,1,0,1},
		{1,0,0,0,0,0,7,0,0,0,0,0,0,0,0,0,0,1,0,1},
		{1,1,0,1,0,1,1,1,1,1,0,1,0,0,0,0,0,1,0,1},
		{1,3,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,3,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		}; 
		
		int map1[14][20] = {
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, //0  �յ�
		{1,3,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}, //1  ǽ
		{1,1,0,0,0,0,1,1,1,0,0,0,0,1,0,0,0,0,0,1}, //3  Ŀ�ĵ�
		{1,0,1,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,1}, //4  ʯ����
		{1,0,0,1,0,1,1,7,0,1,1,1,0,0,0,0,0,0,0,1}, //5  ��
		{1,0,0,0,1,1,1,0,0,0,0,1,0,0,0,0,0,0,0,1}, //7  ľ����
		{1,0,0,0,0,1,0,0,0,7,7,1,1,1,1,3,0,0,0,1}, //8  ����+Ŀ�ĵ� 
		{1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,1},
		{1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,1},
		{1,0,0,0,0,1,1,1,0,0,1,0,0,0,0,0,0,1,0,1},
		{1,0,0,0,0,0,7,0,0,0,0,0,0,0,0,0,0,1,0,1},
		{1,1,0,1,0,1,1,1,1,1,0,1,0,0,0,0,0,1,0,1},
		{1,3,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,3,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		}; 

//��Ϸ��ʼ��		
void GameInit()
{
	SetWindowTitle("�������޵����ɰ�");
	InitGraphics(); 
    initStartPage();
}


//���Ƶ�ͼ
void DrawMap()
{	
	DrawBackground();
	for (int i = 0; i < 14; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			switch (map[i][j])
			{
			case 1:
				DrawWallForest(0.43*j+0.215,0.43*i+0.215);
				break;
			case 2:
				DrawManUp(0.43*j+0.215,0.43*i+0.215);
				break;
			case 3:
				DrawDestination(0.43*j+0.215,0.43*i+0.215);
				break;
			case 4:
				DrawManLeft(0.43*j+0.215,0.43*i+0.215);
				break;
			case 5:
				DrawManRight(0.43*j+0.215,0.43*i+0.215);
				break;
			case 6:
				DrawManDown(0.43*j+0.215,0.43*i+0.215);
				break;
			case 7:
				DrawGameBox1(0.43*j+0.215,0.43*i+0.215);
				break;
			case 8:
				DrawGameBox2(0.43*j+0.215,0.43*i+0.215);
				break;
			case 0:
				break;
			}
		}
		printf("\n");
	}
}

//������Ϸ
void PlayGame()
{
	DrawMap(); 
	initButton();
	registerKeyboardEvent(KeyboardEventProcess);
	registerTimerEvent(&abouttime);
	startTimer(defaultTimer,1000); 
}

void RePlayGame()
{	count=constcount;
	lasttime=consttime;
	int i,j;
    for (int i = 0; i < 14; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			map[i][j]=map1[i][j];
			}
		}
	DrawMap(); 
	initButton();
	registerKeyboardEvent(KeyboardEventProcess);
	registerTimerEvent(&abouttime);
	startTimer(defaultTimer,1000); 
}

//������
void Main()
{
		GameInit();
		return 0;
}

//���˵�x���� 
int FindHumanx(){
	int r;
	int c;
	for (int i = 0; i < 14; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			if (map[i][j] == 5 || map[i][j] == 2|| map[i][j] == 4|| map[i][j] == 6)
			{
				r = i;
				c = j;
			}
		}
	}
	return r;
}

//���˵�y���� 
int FindHumany(){
	int r;
	int c;
	for (int i = 0; i < 14; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			if (map[i][j] == 5 || map[i][j] == 2|| map[i][j] == 4|| map[i][j] == 6)
			{
				r = i;
				c = j;
			}
		}
	}
	return c;
}

//���̻ص����������ڿ������ƶ� 
void KeyboardEventProcess(int key, int event){
	int x,y,z;
	 	x=FindHumanx();
		y=FindHumany();
	if(count!=0&&CheckBox()<realbox){
	switch(event){
		case KEY_DOWN:
	switch (key) {
			     case VK_UP:/*UP*/
			        HumanUp(x,y); 
			        initButton();
                    break;
				 case VK_DOWN:/*DOWN*/
			        HumanDown(x,y); 
			        initButton();
                    break;
				 case VK_LEFT:/*DOWN*/
			        HumanLeft(x,y); 
			        initButton();
                    break; 
				 case VK_RIGHT:/*DOWN*/
			        HumanRight(x,y); 
			        initButton();
                    break; 	               
				}			
				}
			}
	if(count==0&&CheckBox()<realbox){
		DrawFailure();
	} 
	else if(CheckBox()==realbox&&event==KEY_UP){
		DrawSuccess();
		z=count*lasttime;
		ranking(z);
	} 
}

//�������ƶ� 
void HumanUp(int x,int y){ 
	if(map[x+1][y]==0){
	int flag=0;
	flag=map[x][y];
	map[x][y]=map[x+1][y];
	map[x+1][y]=2;
		count--; 
	clearScreen();
	DrawMap();}
	else if(map[x+1][y]==7&&map[x+2][y]==0){
	int flag;
	flag=map[x][y];
	map[x+2][y]=map[x+1][y];
	map[x+1][y]=2; 
	map[x][y]=0;
		count--;
	clearScreen();
	DrawMap();
	}
	else if(map[x+1][y]==7&&map[x+2][y]==3){
	map[x+2][y]=8;
	map[x+1][y]=2;
	map[x][y]=0; 
		count--;
	clearScreen();
	DrawMap();
		
	}
}

//�������ƶ� 
void HumanDown(int x,int y){ 
	if(map[x-1][y]==0){
	int flag;
	flag=map[x][y];
	map[x][y]=map[x-1][y];
	map[x-1][y]=6; 
		count--;
	clearScreen();
	DrawMap();}
	else if(map[x-1][y]==7&&map[x-2][y]==0){
	int flag;
	flag=map[x][y];
	map[x-2][y]=map[x-1][y];
	map[x-1][y]=6; 
	map[x][y]=0;
		count--;
	clearScreen();
	DrawMap();
	
}
else if(map[x-1][y]==7&&map[x-2][y]==3){
	map[x-2][y]=8;
	map[x-1][y]=6;
	map[x][y]=0; 
		count--;
	clearScreen();
	DrawMap();
	
	}
}

//�������ƶ� 
void HumanLeft(x,y){ 
if(map[x][y-1]==0){
	int flag;
	flag=map[x][y];
	map[x][y]=map[x][y-1];
	map[x][y-1]=4; 
		count--;
	clearScreen();
	DrawMap();
	}
	else if(map[x][y-1]==7&&map[x][y-2]==0){
	int flag;
	flag=map[x][y];
	map[x][y-2]=map[x][y-1];
	map[x][y-1]=4; 
	map[x][y]=0;
		count--;
	clearScreen();
	DrawMap();
	}
	else if(map[x][y-1]==7&&map[x][y-2]==3){
	map[x][y-2]=8;
	map[x][y-1]=4;
	map[x][y]=0; 
		count--;
	clearScreen();
	DrawMap();
	}
}

//�������ƶ� 
void HumanRight(x,y){ 
	if(map[x][y+1]==0){
	int flag;
	flag=map[x][y];
	map[x][y]=map[x][y+1];
	map[x][y+1]=5; 
	count--;
	clearScreen();
	DrawMap();}
	else if(map[x][y+1]==7&&map[x][y+2]==0){
	int flag;
	flag=map[x][y];
	map[x][y+2]=map[x][y+1];
	map[x][y+1]=5; 
	map[x][y]=0;
	count--;
	clearScreen();
	DrawMap();
	}
	else if(map[x][y+1]==7&&map[x][y+2]==3){
	map[x][y+2]=8;
	map[x][y+1]=5;
	map[x][y]=0; 
	count--;
	clearScreen();
	DrawMap();
	
	}
}

//����ˢ�£���Ļ 
void clearScreen() 
{
    SetPenColor("White");
    StartFilledRegion(1);
    DrawBox(0, 0, GetWindowWidth(), GetWindowHeight());
    EndFilledRegion();
}

//������Ϸ 
void saveGame()
{
	clearScreen();
    FILE *fp=fopen(savefile,"w");
    fprintf(fp,"%d %d %d\n",lasttime,count,1);
    for (int i = 0; i < 14; i++)
	{
		for (int j = 0; j < 20; j++)
        {

            fprintf(fp,"%d\n",map[i][j]);

        }
    }

    fclose(fp);
    pauseGame();
}



void pauseGame() //��ͣ��Ϸ
{
	


	double	width = GetWindowWidth();
    double	height = GetWindowHeight();
 
    static int PRESTATE;
    if (state == PAUSED) //��ǰ����ͣ���ָ�
    {

        state = PRESTATE;
        strcpy(pause->text, "�ٵ�");

		enableButton(pause);
        disableButton(save);
        disableButton(resume);
        disableButton(quit);
         clearScreen();
    		DrawMap(); 
    		 drawButton(pause);
    		registerKeyboardEvent(KeyboardEventProcess);
        	startTimer(defaultTimer, 1000);
    }
    else //��ǰδ��ͣ������ͣ
    {
    	
        PRESTATE = state;
        state = PAUSED;

    	disableButton(pause);
	    cancelTimer(defaultTimer);
     	clearScreen();
	    wordbox(width / 2, height / 2 + 0.5, "������Ϸ");
        wordbox(width / 2 + 0.8, height / 2 - 0.5, "������Ϸ");
        wordbox(width / 2 + 1.6, height / 2 - 1.5, "�ص����˵�");
	    enableButton(save);
        enableButton(resume);
        enableButton(quit);
    }
}

//�ص����˵� 
void returnMenu() 
{
	clearScreen(); 
    strcpy(pause->text, "��ͣ");
    
	disableButton(pause);
    disableButton(save);
    disableButton(resume);
    disableButton(quit);
    int i,j;
    for (int i = 0; i < 14; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			map[i][j]=map1[i][j];
			}
		}
		count=constcount;
			initStartPage();
	}

//��ʼ����ť
void initButton() 
{
	double	width = GetWindowWidth();
    double	height = GetWindowHeight();
    double buttonWidth = 0.6, buttonHeight = 0.3, delta = 0.05;
    pause = createButton(8, height - buttonHeight - 0.2, buttonWidth, buttonHeight, "+", &pauseGame);
    
//    registerMouseEvent(buttonCallBack);
	insButton(pause);
    drawButton(pause);
    enableButton(pause);
    buttonWidth = width / 8;
    buttonHeight = 1;
    save = createButton(width / 2, height / 2 + 0.5, buttonWidth, buttonHeight, "������Ϸ", &saveGame);
    resume = createButton(width / 2 + 0.8, height / 2 - 0.5, buttonWidth, buttonHeight, "������Ϸ", &pauseGame);
    quit = createButton(width / 2 + 1.6, height / 2 - 1.5, buttonWidth, buttonHeight, "�˳���Ϸ", &returnMenu);
//    registerMouseEvent(buttonCallBack)
	insButton(save);
    insButton(resume);
    insButton(quit);
}

//��鳡�ϵ������Ƿ�ȫ����λ 
int CheckBox(){
	int truebox=0;
	for (int i = 0; i < 14; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			if (map[i][j] == 8)
			{
				truebox++;
			}
		}
	}
	return truebox;	
} 

//��ȡ�浵
void loadGame() 
{	
    FILE *fp = fopen(savefile, "r");
    
	if (fp != NULL)
    {

        if (!~fscanf(fp, "%d\n %d\n",&lasttime,&count))
        	{
        		fclose(fp);
            	return;
			}
		int i,j;
	 while (~fscanf(fp, "%d", &i))
        {
        	 for ( i=0 ; i < 14; i++)
				{
					for (j=0 ; j < 20; j++)
       					{

            				fscanf(fp,"%d",&map[i][j]);

       					 }
    			}
    	}
    	
    	startGame1();

	}
    else
	{

		startGame1();
	 } 
	 
	 fclose(fp);
}

//ʱ��ص����������ڼ�ʱ�������� 
void abouttime(){
	if(lasttime>0){
	lasttime-=1000;
	}
	if(lasttime>0&&count>0&&CheckBox()<realbox){
	DrawBackground1();
	drawButton(pause);}
	if(lasttime==0&&CheckBox()<realbox){
		count=0; 
		DrawFailure();
	} 
}
