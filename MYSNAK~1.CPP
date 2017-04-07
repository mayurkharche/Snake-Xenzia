#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <graphics.h>
#include <privacy.h>
#include <Record.h>

#define RIGHT 77
#define LEFT 75
#define UP 72
#define DOWN 80
#define POINT 1
#define SNAKE 1
#define HEAD 0

void Print();
void Point();
void displayPoint();
void createcircle(int,int,int);
void ExitGame();
void Right();
void Left();
void Up();
void Down();
void Move();
void Turn();
void Load();

int length,life,len,turn_no;
int score=0;
int Record;

struct coordinate
{
	int x,y,direction;
};

typedef struct coordinate C;

C head,point,turn[500],snake[30];

void main()
{
	int gdriver=DETECT,gmode,errorcode;
	initgraph(&gdriver,&gmode,"C:\\turboc3\\bgi");

	int i;

	privacy();

	Print();

	length=5;
	head.x=20;
	head.y=20;
	head.direction=RIGHT;

	point.x=0;

	Point();
	displayPoint();//x=640 & y=400

	life=3;

	turn[0]=head;

	Move();

	getch();
}

void Load()
{
	int i,j,k;
	char ch=177;
	clrscr();
	outtextxy(250,150,"LOADING.....");
	for(k=0;k<20;k++)
	{
		for(i=0;i<3200;i++)
		{
			for(j=0;j<250;j++);
		}
		outtextxy(k*10+200,170,&ch);
	}
}
void Print()
{
	textcolor(6);
	clrscr();
	settextstyle(7,HORIZ_DIR,2);
	outtextxy(150,150,"Welcome to the mini Snake game.");
	outtextxy(150,170,"press any key to continue.....");
	getch();
	Load();
	clrscr();
	outtextxy(250,7,"Game instructions:");
	outtextxy(250,25,"*************************");
	settextstyle(7,HORIZ_DIR,1);
	outtextxy(10,40,"-> Use arrow keys to move the snake.");
	outtextxy(10,70,"-> You will be provided foods at the several coordinates of the screen which you have to eat.");
	outtextxy(10,100,"->Everytime you eat a food the length of the snake will be increased by 1 element and thus the score.");
	outtextxy(10,130,"-> Here you are provided with three lives.");
	outtextxy(10,170,"->Your life will decrease as you hit the wall or snake's body.");
	outtextxy(10,200,"-> YOu can pause the game in its middle by pressing any key.");
	outtextxy(10,230,"To continue the paused game press any other key once again.");
	outtextxy(10,260,"-> If you want to exit press esc.");
	outtextxy(10,290,"Press any key to play game...");

	if(getch()==27)
		exit(0);
}

void Point()
{
	if(head.x==point.x && head.y==point.y)
	{
		length++;

		point.x=rand()%510;
		for(;(point.x%10)!=0;point.x++);
		point.y=rand()%300;
		for(;(point.y%10)!=0;point.y++);

		if(point.x<=10) point.x+=10;
		if(point.y<=10) point.x+=10;
	}
	else if(point.x==0)
	{
		point.x=rand()%510;
		for(;(point.x%10)!=0;point.x++);
		point.y=rand()%300;
		for(;point.y%10!=0;point.y++);
	}
}

void displayPoint()
{
	char a[50];
	char ch=177;
	int x,y=0;
	clrscr();
	createcircle(point.x,point.y,POINT);
	score++;
	settextstyle(4,HORIZ_DIR,4);
	sprintf(a,"SCORE");
	outtextxy(530,20,a);

	outtextxy(510,120,"RECORD");

	settextstyle(4,HORIZ_DIR,3);
	sprintf(a,"%d",score);
	outtextxy(570,50,a);
	Record=Rec();
	if(score>Record)
	{
		Record=score;
		sprintf(a,"%d",score);
		outtextxy(570,150,a);
	}
	else
	{
		sprintf(a,"%d",Record);
		outtextxy(570,150,a);
	}

      /*	textcolor(6);
	settextstyle(4,HORIZ_DIR,3);
	outtextxy(500,310,"SUBMITTED BY");
	outtextxy(450,340,"MAYUR(38)");
	outtextxy(450,360,"ROHIT(58)"); */
}

void createcircle(int x,int y,int color)
{
	int i;
	for(i=0;i<=5;i++)
	{
		for(i=0;i<=5;i++)
		{
			if(i<=1)
			{
				circle(x,y,i);
				setcolor(2);
			}
			else
			{
				circle(x,y,i);
				setcolor(color);
			}
		}
	}
}

void Move()
{
	int a,i,j,k;
	char arr[10];
	char key;

	do
	{
		Point();
		fflush(stdin);

		len=0;

		for(i=0;i<30;i++)
		{
			snake[i].x=0;
			snake[i].y=0;

			if(i==length)
				break;
		}

		for(j=0;j<31000;j++)
		{
			for(k=0;k<(500/length);k++);
		}

		displayPoint();

		if(head.direction==RIGHT)
		       Right();
		if(head.direction==LEFT)
			Left();
		if(head.direction==UP)
			Up();
		if(head.direction==DOWN)
			Down();

		ExitGame();
	}
	while(!kbhit());

	a=getch();

	if(a==27)
	{
		clrscr();

		if(score>=Record)
			UpdateRec(Record);

		exit(0);
	}

	key=getch();

	if(((key==RIGHT) && (head.direction!=LEFT) && head.direction!=RIGHT) || (key==LEFT && head.direction!=LEFT && head.direction!=RIGHT) || (key==UP && head.direction!=UP && head.direction!=DOWN) || (key==DOWN && head.direction!=DOWN && head.direction!=UP))
	{
		turn_no++;

		turn[turn_no]=head;

		head.direction=key;

		if(key==UP)
			head.y-=10;

		if(key==DOWN)
			head.y+=10;

		if(key==RIGHT)
			head.x+=10;

		if(key==LEFT)
			head.x-=10;

		Move();
	}
	else if(key==27)
	{
		clrscr();

		exit(0);
	}
	else
	{
		Move();
	}
}

void ExitGame()
{
	int i,check=0;
	for(i=4;i<length;i++)
	{
		if(snake[0].x==snake[i].x&&snake[0].y==snake[i].y)
		{
			check++;
		}
		if(i==length||check!=0)
			break;
	}
	if(head.x<=5||head.x>=635||head.y<=5||head.y>=395||check!=0)
	{
		life--;
		score=0;
		if(life>=0)
		{
			head.x=20;
			head.y=20;
			turn_no=0;
			head.direction=RIGHT;
			length=5;
			Move();
		}
		else
		{
			clrscr();
			if(score>=Record)
				UpdateRec(Record);

			settextstyle(7,HORIZ_DIR,1);
			outtextxy(240,150,"All Lives Completed..");
			outtextxy(240,170,"Better Luck Next Time!!!!");
			outtextxy(240,190,"Press any key to EXIT....");
			getch();
			exit(0);
		}
	}
}

void Right()
{
	int i;
	for(i=0;i<=((head.x-turn[turn_no].x)/10)&&len<length;i++)
	{
		snake[len].x=head.x-i*10;
		snake[len].y=head.y;
		if(len==0)
			createcircle(snake[len].x,snake[len].y,HEAD);
		else
			createcircle(snake[len].x,snake[len].y,SNAKE);

		len++;
	}
	Turn();
	if(!kbhit())
		head.x+=10;
}

void Left()
{
	int i;
	for(i=0;i<=((turn[turn_no].x-head.x)/10)&&len<length;i++)
	{
		if(len==0)
			createcircle(head.x+(i*10),head.y,HEAD);
		else
			createcircle(head.x+(i*10),head.y,SNAKE);

		snake[len].x=head.x+i*10;
		snake[len].y=head.y;

		len++;
	}
	Turn();
	if(!kbhit())
		head.x-=10;
}

void Up()
{
	int i;
	for(i=0;i<=((turn[turn_no].y-head.y)/10)&&len<length;i++)
	{
		if(len==0)
			createcircle(head.x,head.y+(i*10),HEAD);
		else
			createcircle(head.x,head.y+(i*10),SNAKE);

		snake[len].y=head.y+i*10;
		snake[len].x=head.x;

		len++;
	}
	Turn();
	if(!kbhit())
		head.y-=10;
}

void Down()
{
	int i;
	for(i=0;i<=((head.y-turn[turn_no].y)/10)&&len<length;i++)
	{
		if(len==0)
			createcircle(head.x,head.y-(i*10),HEAD);
		else
			createcircle(head.x,head.y-(i*10),SNAKE);

		snake[len].x=head.x-i*10;
		snake[len].y=head.y;

		len++;
	}
	Turn();
	if(!kbhit())
		head.y+=10;
}
void Turn()
{
	int i,j,diff;

	for(i=turn_no; i>=0 && len<length; i--)
	{
		if(turn[i].x==turn[i-1].x)
		{
			diff=(turn[i].y-turn[i-1].y)/10;

			if(diff<0)
			{
				for(j=1; j<=(-diff); j++)
				{
					snake[len].x=turn[i].x;
					snake[len].y=turn[i].y+j*10;
					createcircle(snake[len].x,snake[len].y,SNAKE);
					len++;
					if(len==length)
						break;
				}
			}
			else if(diff>0)
			{
				for(j=1;j<=diff;j++)
				{
					snake[len].x=turn[i].x;
					snake[len].y=turn[i].y-j*10;
					createcircle(snake[len].x,snake[len].y,SNAKE);
					len++;
					if(len==length)
						break;
				}
			}
		}
		else if(turn[i].y==turn[i-1].y)
		{
			diff=(turn[i].x-turn[i-1].x)/10;

			if(diff<0)
				for(j=1;j<=(-diff)&&len<length;j++)
				{
					snake[len].x=turn[i].x+j*10;
					snake[len].y=turn[i].y;
					createcircle(snake[len].x,snake[len].y,SNAKE);
					len++;
					if(len==length)
						break;
				}
			else if(diff>0)
			{
				for(j=1;j<=diff&&len<length;j++)
				{
					snake[len].x=turn[i].x-j*10;
					snake[len].y=turn[i].y;
					createcircle(snake[len].x,snake[len].y,SNAKE);
					len++;
					if(len==length)
						break;
				}
			}
		}
	}
}
