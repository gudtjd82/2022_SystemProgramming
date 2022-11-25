#if defined(_WIN32) || defined(_WIN64)
	#include <WinSock2.h>
	#include <Windows.h>
	#include <conio.h>
#endif

	#include <unistd.h>
	#include <netinet/in.h>
	#include <sys/socket.h>
	#include <sys/shm.h>
	#include <sys/ipc.h>
	#include <sys/stat.h>
	#include <arpa/inet.h>

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <ncurses.h>
	#include <sys/types.h>
	#include <fcntl.h>

#define MAP_INIT_X 0
#define MAP_INIT_Y 0
#define MAP_WIDTH 60
#define MAP_HEIGHT 20
#define MAX_BODY_LEN 50
#define GAME_SPEEN 200000
#define MAX_PLAYER 1

typedef struct snake_info{

	int snake_pos_x[MAX_BODY_LEN];
	int snake_pos_y[MAX_BODY_LEN];
	int snake_len;
	int direction;

}SNAKE;

void DrawMap();
void DrawSnake();
void Move(SNAKE*);
int _kbhit();
void gotoxy(int, int, char*);
void SetColor();
void StructConstructor(SNAKE*);

void gotoxy(int y, int x, char* msg)
{
	move(y, x);
	printw("%s", msg);
}

int _kbhit()
{
	struct timeval tv = {0L, 0L}; //0으로 set
	fd_set fds;

	FD_ZERO(&fds);
	FD_SET(0, &fds); //file discriptor set

	return select(1, &fds, NULL, NULL, &tv);
}

void DrawMap()
{
    attron(COLOR_PAIR(1));

    int idx = 0;

    //x값을 증가시키며 space를 그림 (가로)
    for(; idx < MAP_WIDTH; idx++){
        gotoxy(MAP_INIT_Y, MAP_INIT_X+ idx, " ");   
    }

    //
    for(idx = MAP_INIT_Y +1; idx < MAP_INIT_Y + MAP_HEIGHT - 1; idx++){ //1~18
        gotoxy(idx, MAP_INIT_X, " ");   //고정된 x = 0에서 y값만 증가시키며 space를 그림(왼쪽 끝 세로)
        gotoxy(idx, MAP_INIT_X + MAP_WIDTH -1, " ");    //고정된 x에서 y값만 증가시키며 space를 그림(오른쪽 끝 세로)
    }

    for(idx = 0; idx < MAP_WIDTH; idx++){
        gotoxy(MAP_INIT_Y + MAP_HEIGHT -1, MAP_INIT_X + idx, " ");
    }
}

void SetColor(){
    start_color();

    init_pair(1, COLOR_BLUE, COLOR_BLUE);
}

int main(int argc, char* argv[])
{

    initscr();

    SetColor();

    DrawMap();

    getch();

    endwin();
	return 0;

}
