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
#define gridwidth 0.43
#include "components.h"
#include "pushbox.h"
#include "begin.h"
char textstring[100]={};
extern count;
extern lasttime;


static button *again;
static button *goback;

//��������������ϷĿ�ĵ� 
void DrawDestination(double x,double y){
 SetPenColor("Brown");
 SetPenSize(4);
 //DrawCenteredCircle(x,y,gridwidth/2);
 MovePen(x,y+gridwidth/4);
 DrawLine(0,-0.7*gridwidth);
 DrawLine(-gridwidth*0.25,0);
 DrawLine(gridwidth*0.5,0);
 SetPenColor("Brown");
 SetPenSize(4);
 SetPenColor("Red");
 StartFilledRegion(1);
 MovePen(x+0.05*gridwidth,y-gridwidth/8);
 DrawLine(gridwidth*3/8,gridwidth*3/16);
 DrawLine(-gridwidth*3/8,gridwidth*3/16);
 DrawLine(0,-gridwidth*3/8);
 EndFilledRegion();
}

//�������ҵ��� 
void DrawManRight(double x,double y){
 SetPenColor("Black");
 SetPenSize(2);
 //DrawCenteredCircle(x,y,gridwidth/2);
 StartFilledRegion(1);
 DrawCenteredCircle(x+0.15*gridwidth,y+gridwidth/4,gridwidth/6);
 EndFilledRegion();
 MovePen(x+0.15*gridwidth,y+gridwidth/12);
 DrawLine(0,-gridwidth*3/8);
 DrawLine(-gridwidth/4,-gridwidth*5/24);
 MovePen(x+0.15*gridwidth,y-gridwidth*7/24);
 DrawLine(0.2*gridwidth,0);
 DrawLine(0,-gridwidth*5/24);
 MovePen(x+0.15*gridwidth,y);
 DrawLine(0.35*gridwidth,0);
 DrawLine(0,gridwidth/6);
 DrawLine(0,-gridwidth/3);
} 

//����������� 
void DrawManLeft(double x,double y){
 SetPenColor("Black");
 SetPenSize(2);
 //DrawCenteredCircle(x,y,gridwidth/2);
 StartFilledRegion(1);
 DrawCenteredCircle(x-0.15*gridwidth,y+gridwidth/4,gridwidth/6);
 EndFilledRegion();
 MovePen(x-0.15*gridwidth,y+gridwidth/12);
 DrawLine(0,-gridwidth*3/8);
 DrawLine(gridwidth/4,-gridwidth*5/24);
 MovePen(x-0.15*gridwidth,y-gridwidth*7/24);
 DrawLine(-0.2*gridwidth,0);
 DrawLine(0,-gridwidth*5/24);
 MovePen(x-0.15*gridwidth,y);
 DrawLine(-0.35*gridwidth,0);
 DrawLine(0,gridwidth/6);
 DrawLine(0,-gridwidth/3);
} 

//�������ϵ��� 
void DrawManUp(double x,double y){
	SetPenColor("Black");
 SetPenSize(2);
 //DrawCenteredCircle(x,y,gridwidth/2);
 StartFilledRegion(1);
 DrawCenteredCircle(x,y-gridwidth/6,gridwidth/3);
 EndFilledRegion();
 MovePen(x,y+gridwidth/6);
 DrawLine(0,gridwidth/3);
 DrawLine(0.3*gridwidth,0);
 DrawLine(-0.6*gridwidth,0);
}

//�������µ��� 
void DrawManDown(double x,double y){
	SetPenColor("Black");
 SetPenSize(2);
 //DrawCenteredCircle(x,y,gridwidth/2);
 StartFilledRegion(1);
 DrawCenteredCircle(x,y+gridwidth/6,gridwidth/3);
 EndFilledRegion();
 MovePen(x,y-gridwidth/6);
 DrawLine(0,-gridwidth/3);
 DrawLine(0.3*gridwidth,0);
 DrawLine(-0.6*gridwidth,0);
}

//����ʯ������ 
void DrawGameBox(double x,double y){
	SetPenColor("Gray");
	StartFilledRegion(1);
    DrawBox(x-gridwidth/2, y-gridwidth/2, gridwidth, gridwidth);
    EndFilledRegion();
	SetPenColor("Black");
	SetPenSize(2);
	DrawBox(x-gridwidth/2, y-gridwidth/2, gridwidth, gridwidth);
	DrawLine(0.1*gridwidth,0.1*gridwidth);
	MovePen(x-gridwidth/2,y+gridwidth/2);
	DrawLine(0.1*gridwidth,-0.1*gridwidth);
	MovePen(x+gridwidth/2,y+gridwidth/2);
	DrawLine(-0.1*gridwidth,-0.1*gridwidth);
	MovePen(x+gridwidth/2,y-gridwidth/2);
	DrawLine(-0.1*gridwidth,0.1*gridwidth);
	DrawBox(x-0.4*gridwidth, y-0.4*gridwidth, 0.8*gridwidth, 0.8*gridwidth);
	SetPenColor("Red");
	SetPenSize(6);
	MovePen(x,y);
	DrawLine(-0.25*gridwidth,0.25*gridwidth);
	MovePen(x,y);
	DrawLine(0.25*gridwidth,0.25*gridwidth);
	MovePen(x,y);
	DrawLine(0.25*gridwidth,-0.25*gridwidth);
	MovePen(x,y);
	DrawLine(-0.25*gridwidth,-0.25*gridwidth);
}

//����δ��λ������ 
void DrawGameBox1(double x,double y){
	SetPenColor("Brown");
	StartFilledRegion(1);
    DrawBox(x-gridwidth/2, y-gridwidth/2, gridwidth, gridwidth);
    EndFilledRegion();
    SetPenColor("Black");
    SetPenSize(2);
    DrawBox(x-gridwidth/2, y-gridwidth/2, gridwidth, gridwidth/6);
    DrawBox(x-gridwidth/2, y+gridwidth/3, gridwidth, gridwidth/6);
    DrawBox(x+gridwidth/3, y-gridwidth/3, gridwidth/6, 2*gridwidth/3);
    DrawBox(x-gridwidth/2, y-gridwidth/3, gridwidth/6, 2*gridwidth/3);
    DrawBox(x-gridwidth/3, y-gridwidth/3, 2*gridwidth/9, 2*gridwidth/3);
    DrawBox(x-1*gridwidth/9, y-gridwidth/3, 2*gridwidth/9, 2*gridwidth/3);
 	SetPenColor("Brown");
 	MovePen(x-gridwidth/3,y+gridwidth/3);
 	StartFilledRegion(1);
    DrawLine(2*gridwidth/3,-gridwidth/2);
    DrawLine(0,-gridwidth/6);
    DrawLine(-2*gridwidth/3,gridwidth/2);
    DrawLine(0,gridwidth/6);
    EndFilledRegion();
    SetPenColor("Black");
    DrawLine(2*gridwidth/3,-gridwidth/2);
    DrawLine(0,-gridwidth/6);
    DrawLine(-2*gridwidth/3,gridwidth/2);
    DrawLine(0,gridwidth/6);}
    
//�������ӹ�λ������ 
void DrawGameBox2(double x,double y){
	SetPenColor("Brown");
	StartFilledRegion(1);
    DrawBox(x-gridwidth/2, y-gridwidth/2, gridwidth, gridwidth);
    EndFilledRegion();
    SetPenColor("Black");
    SetPenSize(2);
    DrawBox(x-gridwidth/2, y-gridwidth/2, gridwidth, gridwidth/6);
    DrawBox(x-gridwidth/2, y+gridwidth/3, gridwidth, gridwidth/6);
    DrawBox(x+gridwidth/3, y-gridwidth/3, gridwidth/6, 2*gridwidth/3);
    DrawBox(x-gridwidth/2, y-gridwidth/3, gridwidth/6, 2*gridwidth/3);
    DrawBox(x-gridwidth/3, y-gridwidth/3, 2*gridwidth/9, 2*gridwidth/3);
    DrawBox(x-1*gridwidth/9, y-gridwidth/3, 2*gridwidth/9, 2*gridwidth/3);
 	SetPenColor("Brown");
 	MovePen(x-gridwidth/3,y+gridwidth/3);
 	StartFilledRegion(1);
    DrawLine(2*gridwidth/3,-gridwidth/2);
    DrawLine(0,-gridwidth/6);
    DrawLine(-2*gridwidth/3,gridwidth/2);
    DrawLine(0,gridwidth/6);
    EndFilledRegion();
    SetPenColor("Black");
    DrawLine(2*gridwidth/3,-gridwidth/2);
    DrawLine(0,-gridwidth/6);
    DrawLine(-2*gridwidth/3,gridwidth/2);
    DrawLine(0,gridwidth/6);
	MovePen(x+0.2*gridwidth,y+0.5*gridwidth);
	DrawLine(0.15*gridwidth,-0.15*gridwidth);
	DrawLine(0.3*gridwidth,0.3*gridwidth);
	DrawLine(-0.15*gridwidth,0.15*gridwidth);
	DrawLine(-0.15*gridwidth,-0.3*gridwidth);
	DrawLine(-0.075*gridwidth,0.15*gridwidth);
	DrawLine(-0.075*gridwidth,-0.15*gridwidth);
	MovePen(x+0.2*gridwidth,y+0.5*gridwidth);
	SetPenColor("Red");
	StartFilledRegion(1);
	DrawLine(0.15*gridwidth,-0.15*gridwidth);
	DrawLine(0.3*gridwidth,0.3*gridwidth);
	DrawLine(-0.15*gridwidth,0.15*gridwidth);
	DrawLine(-0.15*gridwidth,-0.3*gridwidth);
	DrawLine(-0.075*gridwidth,0.15*gridwidth);
	DrawLine(-0.075*gridwidth,-0.15*gridwidth);
	EndFilledRegion();
	}

//������Ϸǽ�壨ʯ�ƣ� 
void DrawWallCity(double x,double y){
	//DrawCenteredCircle(x,y,gridwidth/2);
	SetPenColor("Gray");
	StartFilledRegion(1);
    DrawBox(x-gridwidth/2, y-gridwidth/2, gridwidth, gridwidth);
    EndFilledRegion();
    SetPenColor("Black");
    SetPenSize(4);
    DrawBox(x-gridwidth/2, y-gridwidth/2, gridwidth, gridwidth);
    MovePen(x-gridwidth/2,y);
    DrawLine(gridwidth,0);
    MovePen(x,y);
    DrawLine(0,-gridwidth/2);
}

//������Ϸǽ�� 
void DrawWallForest(double x,double y){
	//DrawCenteredCircle(x,y,gridwidth/2);
	SetPenColor("Green");
	StartFilledRegion(1);
    DrawTriangle(x-gridwidth/4, y+gridwidth/4, gridwidth/2, gridwidth/4);
    EndFilledRegion();
	StartFilledRegion(1);
    DrawTriangle(x-gridwidth/3, y , 2*gridwidth/3, gridwidth/4);
    EndFilledRegion();
    StartFilledRegion(1);
    DrawTriangle(x-gridwidth/2, y-gridwidth/4 , gridwidth, gridwidth/4);
    EndFilledRegion();
    StartFilledRegion(1);
    SetPenColor("Brown");
    DrawBox(x-gridwidth/6, y-gridwidth/2, gridwidth/3, gridwidth/4);
    EndFilledRegion();
    SetPenColor("Black");
    SetPenSize(2);
    DrawTriangle(x-gridwidth/4, y+gridwidth/4, gridwidth/2, gridwidth/4);
    DrawTriangle(x-gridwidth/3, y , 2*gridwidth/3, gridwidth/4);
    DrawTriangle(x-gridwidth/2, y-gridwidth/4 , gridwidth, gridwidth/4);
    DrawBox(x-gridwidth/6, y-gridwidth/2, gridwidth/3, gridwidth/4);
}

//������Ϸ���� 
void DrawBackground(){
    addColor("BACK", 193, 235, 236);
    addColor("BACK1", 200, 199, 185);
    addColor("BACK2", 57, 135, 198);
   	SetPenColor("BACK");
   	double y= 14*gridwidth;
   	double x= 20*gridwidth;
   	StartFilledRegion(1);
   	MovePen(0,0);
   	DrawLine(x,0);
   	DrawLine(0,y);
   	DrawLine(-x,0);
   	DrawLine(0,-y);
   	EndFilledRegion();
   	SetPenColor("Black");
   	SetPenSize(2); 
   	DrawBox(0,14.1*gridwidth, GetWindowWidth(), 0.15*gridwidth);
   	SetPenColor("Brown");
   	StartFilledRegion(1);
   	DrawBox(0,14.1*gridwidth, GetWindowWidth(), 0.15*gridwidth);
   	EndFilledRegion();
   	SetPenColor("Black");
   	DrawBox(20.1*gridwidth, 0, 0.15*gridwidth, GetWindowHeight());
   	SetPenColor("Brown");
   	StartFilledRegion(1);
   	DrawBox(20.1*gridwidth, 0, 0.15*gridwidth, GetWindowHeight());
   	EndFilledRegion();
   	DrawBackground1();
   	DrawBackground2(); 
}

//չʾ�ϲ�״̬������ʾʱ�䡢ʣ�ಽ���� 
void DrawBackground1(){
	SetPenColor("BACK1");
	StartFilledRegion(1);
   	DrawBox(0,14.25*gridwidth, 20.05*gridwidth, 3*gridwidth);
   	EndFilledRegion();
   	SetPenColor("BACK2");
   	StartFilledRegion(1);
   	DrawBox(1.15*gridwidth,14.45*gridwidth, 7.05*gridwidth, 1.5*gridwidth);
   	EndFilledRegion();
   	MovePen(1.35*gridwidth,14.65*gridwidth);
   	SetPenColor("Black");
   	SetFont("΢���ź�"); 
   	SetPointSize(35);
   	sprintf(textstring,"ʣ��ʱ��: %d" ,lasttime/1000);
   	DrawTextString(textstring);
   	SetPenColor("BACK2");
   	StartFilledRegion(1);
   	DrawBox(10.15*gridwidth,14.45*gridwidth, 7.05*gridwidth, 1.5*gridwidth);
   	EndFilledRegion();
   	MovePen(10.35*gridwidth,14.65*gridwidth);
   	SetPenColor("Black");
   	SetFont("΢���ź�"); 
   	SetPointSize(35);
   	sprintf(textstring,"ʣ�ಽ��: %d" ,count);
   	DrawTextString(textstring);
}

//չʾ�Ҳ�״̬�� 
void DrawBackground2(){
	SetPenColor("BACK1");
	StartFilledRegion(1);
   	DrawBox(20.25*gridwidth, 0, 3.1*gridwidth, GetWindowHeight());
   	EndFilledRegion();
   	SetPenColor("BACK2");
}

//��ʧ�ܽ��� 
void DrawFailure(){
	clearScreen();
	int i;		
	double	width = GetWindowWidth();
	double  height = GetWindowHeight();
	double buttonWidth = width / 8;
	double buttonHeight = 1;
	if(again == NULL){
	again = createButton(0.42*GetWindowWidth(),0.37*GetWindowHeight(), buttonWidth, buttonHeight, "��ʼ��Ϸ", &RePlayGame);
	registerMouseEvent(buttonCallBack);
	insButton(again);
	enableButton(again);}
	
	SetPenColor("BACK");
	StartFilledRegion(1);
	DrawBox(0.1*GetWindowWidth(),0.1*GetWindowHeight(),0.8*GetWindowWidth(),0.8*GetWindowHeight());
	EndFilledRegion();
	SetPenSize(1);
	for(i=0;i<15;i++){
	DrawWallCity(0.2*GetWindowWidth()+i*gridwidth,0.8*GetWindowHeight());
	}
	for(i=0;i<15;i++){
	DrawWallCity(0.2*GetWindowWidth()+i*gridwidth,0.2*GetWindowHeight());
	}
	MovePen(0.4*GetWindowWidth(),0.6*GetWindowHeight());
	SetPenColor("Red");
	SetPenSize(40);
	DrawTextString("YOU LOSE");
	SetPenColor("BACK1");
	StartFilledRegion(1);
	DrawBox(0.37*GetWindowWidth(),0.35*GetWindowHeight(),0.25*GetWindowWidth(),0.08*GetWindowHeight());
	EndFilledRegion();
		SetPenColor("Black");
	MovePen(0.42*GetWindowWidth(),0.37*GetWindowHeight());
	DrawTextString("����һ�Σ�");

	
	
}

//���ɹ����� 
void DrawSuccess(){
	clearScreen();
	int i;
	
	double	width = GetWindowWidth();
	double  height = GetWindowHeight();
	double buttonWidth = width / 8;
	double buttonHeight = 1;
	if(goback == NULL){
	goback = createButton(0.42*GetWindowWidth(),0.37*GetWindowHeight(), buttonWidth, buttonHeight, "��ʼ��Ϸ", &initStartPage);
	registerMouseEvent(buttonCallBack);
	insButton(goback);
	enableButton(goback);}
	
	SetPenColor("BACK");
	StartFilledRegion(1);
	DrawBox(0.1*GetWindowWidth(),0.1*GetWindowHeight(),0.8*GetWindowWidth(),0.8*GetWindowHeight());
	EndFilledRegion();
	SetPenSize(1);
	for(i=0;i<15;i++){
	DrawWallCity(0.2*GetWindowWidth()+i*gridwidth,0.8*GetWindowHeight());
	}
	for(i=0;i<15;i++){
	DrawWallCity(0.2*GetWindowWidth()+i*gridwidth,0.2*GetWindowHeight());
	}
	MovePen(0.4*GetWindowWidth(),0.6*GetWindowHeight());
	SetPenColor("Red");
	SetPenSize(40);
	DrawTextString("YOU WIN");
	SetPenColor("BACK1");
	StartFilledRegion(1);
	DrawBox(0.37*GetWindowWidth(),0.45*GetWindowHeight(),0.25*GetWindowWidth(),0.03*GetWindowHeight());
	EndFilledRegion();
	StartFilledRegion(1);
	DrawBox(0.37*GetWindowWidth(),0.35*GetWindowHeight(),0.25*GetWindowWidth(),0.03*GetWindowHeight());
	EndFilledRegion();
		SetPenColor("Black");
	MovePen(0.4*GetWindowWidth(),0.44*GetWindowHeight());
	DrawTextString("�ص����˵�(��_��)");
	MovePen(0.395*GetWindowWidth(),0.34*GetWindowHeight());
	SetPenSize(18);
	sprintf(textstring,"���ķ�����: %d" ,count*lasttime/1000);
	DrawTextString(textstring);
}

//��һ�������� 
void DrawBox(double x, double y, double width, double height)
{
    MovePen(x, y);
    DrawLine(0, height);
    DrawLine(width, 0);
    DrawLine(0, -height);
    DrawLine(-width, 0);
}

//��һ������������ 
void DrawTriangle(double x, double y, double base, double height)
{
    MovePen(x, y);
    DrawLine(base, 0);
    DrawLine(-base / 2, height);
    DrawLine(-base / 2, -height);
}

//��һ��Բ�� 
void DrawCenteredCircle(double x, double y, double r)
{
    MovePen(x + r, y);
    DrawArc(r, 0, 360);
}

//�����������ɫ 
void addColor(string name, int x, int y, int z) 
{
    DefineColor(name, 1.0 * x/255, 1.0 * y/255, 1.0 * z/255);
}

