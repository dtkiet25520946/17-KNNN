#include <iostream>
#include <conio.h>
#include <ctime>
#include <windows.h>
using namespace std;
#define H 20
#define W 15
int Speed = 200; // Toc do ban dau
int lineCleared = 0; // Hang da xoa
char board[H][W] = {} ;
char blocks[][4][4] = {
        {{' ','I',' ',' '},
         {' ','I',' ',' '},
         {' ','I',' ',' '},
         {' ','I',' ',' '}},
        {{' ','I',' ',' '},
         {' ','I',' ',' '},
         {' ','I',' ',' '},
         {' ','I',' ',' '}},
        {{' ',' ',' ',' '},
         {' ','O','O',' '},
         {' ','O','O',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {' ','O','O',' '},
         {' ','O','O',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {' ','O','O',' '},
         {' ','O','O',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {' ','O','O',' '},
         {' ','O','O',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {' ','O','O',' '},
         {' ','O','O',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {' ','O','O',' '},
         {' ','O','O',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {' ','O','O',' '},
         {' ','O','O',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {'I','I','I','I'},
         {' ',' ',' ',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {' ','O','O',' '},
         {' ','O','O',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {' ','T',' ',' '},
         {'T','T','T',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {' ','S','S',' '},
         {'S','S',' ',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {'Z','Z',' ',' '},
         {' ','Z','Z',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {'J',' ',' ',' '},
         {'J','J','J',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {' ',' ','L',' '},
         {'L','L','L',' '},
         {' ',' ',' ',' '}}
};

void UpdateSpeed(){
    Speed = Speed - (lineCleared * 3); // tang toc do roi
    if(Speed<75) Speed = 75; // gioi han
}

int x=4,y=0,b=1;
void gotoxy(int x, int y) {
<<<<<<< HEAD
    COORD c = {(SHORT)x, (SHORT)y};
=======
    COORD c = {x, y};
>>>>>>> nhunguyet-tuan2
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void boardDelBlock(){
    for (int i = 0 ; i < 4 ; i++)
        for (int j = 0 ; j < 4 ; j++)
            if (blocks[b][i][j] != ' ' && y+j < H)
                board[y+i][x+j] = ' ';
}
void block2Board(){
    for (int i = 0 ; i < 4 ; i++)
        for (int j = 0 ; j < 4 ; j++)
            if (blocks[b][i][j] != ' ' )
                board[y+i][x+j] = blocks[b][i][j];
}
void initBoard(){
    for (int i = 0 ; i < H ; i++)
        for (int j = 0 ; j < W ; j++)
            if ((i==H-1) || (j==0) || (j == W-1)) board[i][j] = '#';
            else board[i][j] = ' ';
}
void draw(){
    gotoxy(0,0);
    for (int i = 0 ; i < H ; i++, cout<<endl)
<<<<<<< HEAD
        for (int j = 0 ; j < W ; j++)
            cout<<board[i][j];
=======
        for (int j = 0 ; j < W ; j++){
            if(board[i][j]==' '){
                cout<<"  ";
            }
            else if(board[i][j]=='#'){
                cout<<(char)178<<(char)178;
            }
            else{
                cout<<(char)219<<(char)219;
            }
        }

>>>>>>> nhunguyet-tuan2
}
bool canMove(int dx, int dy){
    for (int i = 0 ; i < 4 ; i++)
        for (int j = 0 ; j < 4 ; j++)
            if (blocks[b][i][j] != ' '){
                int tx = x + j + dx;
                int ty = y + i + dy;
                if ( tx<1 || tx >= W-1 || ty >= H-1) return false;
                if ( board[ty][tx] != ' ') return false;
            }
    return true;
}

void rotateBlock()
{
    char temp[4][4];
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            temp[j][3 - i] = blocks[b][i][j];
        }
    }

    bool canRotate = true;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (temp[i][j] != ' ')
            {
                int tx = x + j;
                int ty = y + i;
                if (tx < 1 || tx >= W - 1 || ty >= H - 1 || board[ty][tx] != ' ')
                {
                    canRotate = false;
                    break;
                }
            }
        }
        if (!canRotate)
            break;
    }

    if (canRotate)
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                blocks[b][i][j] = temp[i][j];
            }
        }
    }
}

void removeLine() {
    int clearedThisTurn = 0;

    for (int i = H - 2; i > 0; i--) {
        int j;
        for (j = 1; j < W - 1; j++)
            if (board[i][j] == ' ') break;

        if (j == W - 1) {
            clearedThisTurn++;

            for (int ii = i; ii > 0; ii--)
                for (int col = 1; col < W - 1; col++)
                    board[ii][col] = board[ii - 1][col];

            i++;
        }
    }

    if (clearedThisTurn > 0) {
        lineCleared += clearedThisTurn;
        UpdateSpeed();
        draw();
        Sleep(200);
    }
}

int main()
{
    srand(time(0));
    b = rand() % 7;
    system("cls");
    initBoard();
    while (1){
        boardDelBlock();
        if (kbhit()){
            char c = getch();
            if (c=='a' && canMove(-1,0)) x--;
            if (c=='d' && canMove(1,0) ) x++;
            if (c=='x' && canMove(0,1))  y++;
            if (c == 'w') rotateBlock(); // Rotate block
            if (c=='q') break;
        }
        if (canMove(0,1)) y++;
        else {
            block2Board();
            removeLine();
            x = 5; y = 0; b = rand() % 7;
        }
        block2Board();
        draw();
        _sleep(200);
        Sleep(Speed);
    }
    return 0;
<<<<<<< HEAD
}
=======
}
>>>>>>> nhunguyet-tuan2
