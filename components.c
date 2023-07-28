#include "components.h"
#include <math.h>
#include <string.h>
#define RankNum 5 

//绘制矩形
void drawRectangle(double x, double y, double width, double height) 
{
    MovePen(x, y);
    DrawLine(width, 0);
    DrawLine(0, height);
    DrawLine(-width, 0);
    DrawLine(0, -height);
}

//在矩形中填充颜色
void drawFilledRect(double x, double y, double width, double height) 
{
    StartFilledRegion(1);
    drawRectangle(x, y, width, height);
    EndFilledRegion();
}


//创建按钮 
button *createButton(double x, double y, 
					double width, double height, char text[], 
					zifuchuan cb) 
{
    button *b = malloc(sizeof(button));
    b->x = x;
    b->y = y;
    b->width = width;
    b->height = height;
    strcpy(b->text, text);
    b->callback = cb;
    b->disabled = TRUE;
    return b;
}

//绘制四个角是圆的的矩形
void RoundRectangle(double x, double y, double w, double h) 
{
    double r = 0.05;
    MovePen(x + r, y);
    DrawLine(w - r * 2, 0);
    DrawArc(r, 270, 90);
    DrawLine(0, h - r * 2);
    DrawArc(r, 0, 90);
    DrawLine(r * 2 - w, 0);
    DrawArc(r, 90, 90);
    DrawLine(0, r * 2 - h);
    DrawArc(r, 180, 90);
}

//画按钮
void drawButton(button *b) 
{
    SetPenColor("White");
    StartFilledRegion(1);
    RoundRectangle(b->x, b->y, b->width, b->height);
    EndFilledRegion();
    MovePen(b->x + b->width / 2 - TextStringWidth(b->text) / 3, b->y + b->height / 2 - 0.05);
    
	SetPenColor("Black");
	SetPointSize(25);
    DrawTextString(b->text);
    SetPenColor("Black");
}

//开启按钮
void enableButton(button *b) 
{
    b->disabled = FALSE;
}

//关闭按钮
void disableButton(button *b) 
{
    b->disabled = TRUE;
}

bool isIn(button *b, int xi, int yi)
{
    double x = ScaleXInches(xi), y = ScaleYInches(yi);
    return x >= b->x && x <= b->x + b->width && y >= b->y && y <= b->y + b->height;
}

//将数据插入链表
linkHead insNode(linkHead head, void *data) 
{
    linkNode *newHead = newNode();
    newHead->data = data;
    newHead->next = head;
    
	if (head != NULL)
    {
        head->pre = newHead;
    }
    return newHead;
}

//将节点从链表中删除
linkHead delNode(linkHead head, linkNode *node) 
{
    if (node->pre != NULL)
    {
        node->pre->next = node->next;
    }
    else
    {
        head = node->next;
    }

    if (node->next != NULL)
    {
        node->next->pre = node->pre;
    }

    free(node);
    return head;
}

//新建链表
linkNode *newNode() 
{
    linkNode *head = (linkNode *)malloc(sizeof(linkNode));
    head->pre = head->next = NULL;
    return head;
}

linkHead buttonList; //按钮的链表

//按钮反应
void buttonCallBack(int x, int y, int bt, int event) 
{
    if (bt != LEFT_BUTTON || event != BUTTON_DOWN)
    {
        return;
    }
    linkNode *p = buttonList;
    
    //遍历按钮的链表，检测是否点到了
	while (p != NULL) 
    {
        button *currentButton = p->data;
        if (!currentButton->disabled && isIn(p->data, x, y))
        {
            (*currentButton->callback)();
            return;
        }
        p = p->next;
    }
}

//向按钮链表中插入
void insButton(button *b) 
{
    buttonList = insNode(buttonList, b);
}

//增加成绩记录
void ranking(int count) 
{
    int scores[RankNum+1] = {0}, i = 0;
    int j, index,k;
    FILE *fp = fopen(rankfile, "r");
    if (fp != NULL)
    {
        while (~fscanf(fp, "%d", &scores[i]))
    	{
    		i++;
		}
		for (j = i; j > 0; j--){
   			if (count/1000 > scores[j - 1]){
    			scores[j] = scores[j - 1];}
   			else{
    			break;}
  		}
  		scores[j] = count/1000;
    }
    fclose(fp);
    
    fp = fopen(rankfile, "w");
    for (j = 0; j < RankNum && j <= i; j++)
    {
        fprintf(fp, "%d\n", scores[j]);
    }
    fclose(fp);
}
