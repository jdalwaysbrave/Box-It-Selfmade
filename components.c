#include "components.h"
#include <math.h>
#include <string.h>
#define RankNum 5 

//���ƾ���
void drawRectangle(double x, double y, double width, double height) 
{
    MovePen(x, y);
    DrawLine(width, 0);
    DrawLine(0, height);
    DrawLine(-width, 0);
    DrawLine(0, -height);
}

//�ھ����������ɫ
void drawFilledRect(double x, double y, double width, double height) 
{
    StartFilledRegion(1);
    drawRectangle(x, y, width, height);
    EndFilledRegion();
}


//������ť 
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

//�����ĸ�����Բ�ĵľ���
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

//����ť
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

//������ť
void enableButton(button *b) 
{
    b->disabled = FALSE;
}

//�رհ�ť
void disableButton(button *b) 
{
    b->disabled = TRUE;
}

bool isIn(button *b, int xi, int yi)
{
    double x = ScaleXInches(xi), y = ScaleYInches(yi);
    return x >= b->x && x <= b->x + b->width && y >= b->y && y <= b->y + b->height;
}

//�����ݲ�������
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

//���ڵ��������ɾ��
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

//�½�����
linkNode *newNode() 
{
    linkNode *head = (linkNode *)malloc(sizeof(linkNode));
    head->pre = head->next = NULL;
    return head;
}

linkHead buttonList; //��ť������

//��ť��Ӧ
void buttonCallBack(int x, int y, int bt, int event) 
{
    if (bt != LEFT_BUTTON || event != BUTTON_DOWN)
    {
        return;
    }
    linkNode *p = buttonList;
    
    //������ť����������Ƿ�㵽��
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

//��ť�����в���
void insButton(button *b) 
{
    buttonList = insNode(buttonList, b);
}

//���ӳɼ���¼
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
