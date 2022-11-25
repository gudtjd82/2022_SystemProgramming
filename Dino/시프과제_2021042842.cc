/* Standard Header */
#include <stdio.h>
#include <stdlib.h>

/* Linux Standard Header */
#include <unistd.h>

/* Header == API == Library */
#include <ncurses.h>

#define DINO_HEIGHT	13
#define CACTUS_HEIGHT	5
#define CACTUS_SPEED	3
#define GRAVITY		3

void DrawDinosaur(int);
void DrawCactus(int, int);
int _kbhit(void);
int GetKeyDown(void);
void DrawScore(int, int, int, int);
int is_crashed(int, int, int);	//공룡과 선인장 충돌 확인
int is_scored(int);	//선인장을 넘었는지 확인

int GetKeyDown()
{
	if(_kbhit()){
		return getch();
	}
	return 0;
}

int _kbhit()
{
	struct timeval va = { 0L, 0L };
	fd_set fds;

	FD_ZERO(&fds);
	FD_SET(0, &fds);

	return select(1, &fds, NULL, NULL, &va);
}

void DrawDinosaur(int dinosaurHead)
{
	move(dinosaurHead, 0);
	static bool legDraw = true;
    	
	printw("        &&&&&&& \n");
    	printw("       && &&&&&&\n");
    	printw("       &&&&&&&&&\n");
    	printw("&      &&&      \n");
    	printw("&&     &&&&&&&  \n");
    	printw("&&&   &&&&&     \n");
    	printw(" &&  &&&&&&&&&& \n");
    	printw(" &&&&&&&&&&&    \n");	
    	printw("  &&&&&&&&&&    \n");	
    	printw("    &&&&&&&&    \n");
    	printw("     &&&&&&     \n");

	if (legDraw) {
		printw("     &    &&&     \n");
		printw("     &&           ");
		legDraw = false;
	}else {
    		printw("     &&&  &       \n");	
		printw("          &&      ");
		legDraw = true;
	}	
}

void DrawCactus(int cactusHead, int cactusPos)
{
	move(cactusHead, cactusPos);
	printw("$$$$");
	move(cactusHead + 1, cactusPos);
	printw(" $$ ");
	move(cactusHead + 2, cactusPos);
	printw(" $$ ");
	move(cactusHead + 3, cactusPos);
	printw(" $$ ");
	move(cactusHead + 4, cactusPos);
	printw(" $$ ");
}

void DrawScore(int score,int level, int scoreX, int scoreY)
{
	move(scoreX, scoreY);
	printw("S C O R E : %d\n", score);
	printw("L E V E L : %d", level);
}

int is_crashed(int dinosaurHead, int cactusPos, int cactusHead)
{
	if(cactusPos <= 11 && cactusHead <= dinosaurHead + 13)
	{
		return true;
	}
	else
		return false;
}

int is_scored(int cactusPos)
{
	if(cactusPos <= 5)
		return true;
	else
		return false;
}

int main(int argc, char* argv[], char* env[])
{
	initscr();

	int winWidth= 0, winHeight = 0;
	int dinosaurHead = 0;
	int cactusHead = 0, cactusPos = 0;
	int scoreY= 0, scoreX = 0;	//점수판의 y,x 좌표
	bool isJumping = false;
	bool isBottom = true;
	int getKey = 0;
	int crashed = 0;	//선인장과 충돌했는지 확인
	int score = 100;	//점수
	int level = 0;		//난이도

	getmaxyx(stdscr, winHeight, winWidth);

	dinosaurHead = winHeight - DINO_HEIGHT;
	cactusHead = winHeight - CACTUS_HEIGHT;/* Y */
	cactusPos = winWidth - 50;/* X */

	while(true){

		level = score / 1000;	//1000점당 난이도가 1씩 증가

		if(is_crashed(dinosaurHead, cactusPos, cactusHead))	//선인장과 충돌하면 while문 종료
		{	
			crashed = 1;
			break;
		}

		getKey = GetKeyDown();

		if((getKey == 32) && isBottom){
			isJumping = true;
			isBottom = false;
		}else if(getKey == 10){
			break;
		}

		if(isJumping){
			dinosaurHead -= GRAVITY;
		}else{
			dinosaurHead += GRAVITY;
		}

		if(winHeight <= (dinosaurHead + DINO_HEIGHT)){
			dinosaurHead = winHeight - DINO_HEIGHT;
			isBottom = true;
		}

		if(dinosaurHead <= 0){
			isJumping = false;
		}

		cactusPos = cactusPos - CACTUS_SPEED - level;

		if(cactusPos <= 0){
			cactusPos = winWidth - 5; 
			score += 100;
		}

		clear();
		//getKey = GetKeyDown();
		//move(0,0);
		//printw("input : %d", getKey);
		DrawDinosaur(dinosaurHead);
		DrawCactus(cactusHead, cactusPos);
		DrawScore(score, level, scoreX, scoreY);
		usleep(100000);
		refresh();
	}	
	
	endwin();

	if(crashed == 1)	//선인장과 충돌해서 게임이 끝난 경우 결과창
	{
		printf("=======================================\n");
		printf("   G   A   M   E       O   V   E   R\n");
		printf("\n");
		printf("   S   C   O   R   E   :   %d\n", score);
		printf("\n");
		printf("   L   E   V   E   L   :   %d\n", level);	
		printf("=======================================\n");
	}

	else				//enter를 눌러서 종료한 경우 결과창
	{
		printf("=======================================\n");
		printf("   S   C   O   R   E   :   %d\n", score);
		printf("\n");
		printf("   L   E   V   E   L   :   %d\n", level);	
		printf("=======================================\n");
	}
	return 0;
}



