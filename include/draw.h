#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <wincon.h>
#include <Windows.h>

#include "genlib.h"
#include "gcalloc.h"
#include "strlib.h"
#include "extgraph.h"

#define constcount 240
#define consttime 120000 
#define RankNum 5
#define MAX_TEXT_LENGTH 80
#define defaultTimer 1

void DrawBox(double x, double y, double width, double height);
void DrawTriangle(double x, double y, double base, double height);
void DrawCenteredCircle(double x, double y, double r);
void DrawGrid(double x, double y, double width, double height,
              int columns, int rows);
              
void DrawDestination(double x,double y);
void DrawManRight(double x,double y);
void DrawManLeft(double x,double y);
void DrawManUp(double x,double y);
void DrawManDown(double x,double y);
void DrawGameBox(double x,double y);
void DrawGameBox1(double x,double y);
void DrawWallForest(double x,double y);
int  CheckBox();
void DrawBackground();
void DrawSuccess();
void addColor(string name, int x, int y, int z);
void returnMenu();
void RePlayGame();
void ranking(int count); 
void abouttime();
