#include <iostream>
#include <conio.h>
#include <ctime>
#include <windows.h>
using namespace std;
#define H 20
#define W 15
int Speed = 200;
int lineCleared = 0;
char board[H][W] = {} ;

void UpdateSpeed(){
    Speed = Speed - (lineCleared * 3);
    if(Speed<75) Speed = 75;
}

class Piece {
public:
    char shape[4][4];
    int x, y;
    Piece() : x(4), y(0) { memset(shape, ' ', sizeof(shape)); }
    virtual void rotate() = 0;
    virtual char symbol() = 0;
    virtual ~Piece() {}
protected:
    void rotateClockwise() {
        char temp[4][4];
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                temp[j][3-i] = shape[i][j];
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                if (temp[i][j] != ' ') {
                    int tx=x+j, ty=y+i;
                    if (tx<1||tx>=W-1||ty>=H-1||board[ty][tx]!=' ') return;
                }
        memcpy(shape, temp, sizeof(shape));
    }
};

class IPiece : public Piece {
public:
    IPiece() {
        char s[4][4] = {
            {' ','I',' ',' '},{' ','I',' ',' '},
            {' ','I',' ',' '},{' ','I',' ',' '}
        };
        memcpy(shape, s, sizeof(s));
    }
    char symbol() override { return 'I'; }
    void rotate() override {
        char temp[4][4];
        bool isVertical = (shape[0][1] == 'I');
        if (isVertical) {
            char s[4][4] = {{' ',' ',' ',' '},{'I','I','I','I'},{' ',' ',' ',' '},{' ',' ',' ',' '}};
            memcpy(temp, s, sizeof(s));
        } else {
            char s[4][4] = {{' ','I',' ',' '},{' ','I',' ',' '},{' ','I',' ',' '},{' ','I',' ',' '}};
            memcpy(temp, s, sizeof(s));
        }
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                if (temp[i][j] != ' ') {
                    int tx=x+j, ty=y+i;
                    if (tx<1||tx>=W-1||ty>=H-1||board[ty][tx]!=' ') return;
                }
        memcpy(shape, temp, sizeof(temp));
    }
};
class OPiece : public Piece {
public:
    OPiece() {
        char s[4][4] = {{' ',' ',' ',' '},{' ','O','O',' '},{' ','O','O',' '},{' ',' ',' ',' '}};
        memcpy(shape, s, sizeof(s));
    }
    char symbol() override { return 'O'; }
    void rotate() override {}
};
class TPiece : public Piece {
public:
    TPiece() {
        char s[4][4] = {{' ',' ',' ',' '},{' ','T',' ',' '},{'T','T','T',' '},{' ',' ',' ',' '}};
        memcpy(shape, s, sizeof(s));
    }
    char symbol() override { return 'T'; }
    void rotate() override { rotateClockwise(); }
};
class SPiece : public Piece {
public:
    SPiece() {
        char s[4][4] = {{' ',' ',' ',' '},{' ','S','S',' '},{'S','S',' ',' '},{' ',' ',' ',' '}};
        memcpy(shape, s, sizeof(s));
    }
    char symbol() override { return 'S'; }
    void rotate() override { rotateClockwise(); }
};
class ZPiece : public Piece {
public:
    ZPiece() {
        char s[4][4] = {{' ',' ',' ',' '},{'Z','Z',' ',' '},{' ','Z','Z',' '},{' ',' ',' ',' '}};
        memcpy(shape, s, sizeof(s));
    }
    char symbol() override { return 'Z'; }
    void rotate() override { rotateClockwise(); }
};
class JPiece : public Piece {
public:
    JPiece() {
        char s[4][4] = {{' ',' ',' ',' '},{'J',' ',' ',' '},{'J','J','J',' '},{' ',' ',' ',' '}};
        memcpy(shape, s, sizeof(s));
    }
    char symbol() override { return 'J'; }
    void rotate() override { rotateClockwise(); }
};
class LPiece : public Piece {
public:
    LPiece() {
        char s[4][4] = {{' ',' ',' ',' '},{' ',' ','L',' '},{'L','L','L',' '},{' ',' ',' ',' '}};
        memcpy(shape, s, sizeof(s));
    }
    char symbol() override { return 'L'; }
    void rotate() override { rotateClockwise(); }
};

Piece* createRandomPiece() {
    switch (rand() % 7) {
        case 0: return new IPiece();
        case 1: return new OPiece();
        case 2: return new TPiece();
        case 3: return new SPiece();
        case 4: return new ZPiece();
        case 5: return new JPiece();
        default: return new LPiece();
    }
}

void gotoxy(int x, int y) {
    COORD c = {(SHORT)x, (SHORT)y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void boardDelBlock(Piece* p){
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (p->shape[i][j] != ' ' && p->y+i < H)
                board[p->y+i][p->x+j] = ' ';
}

void block2Board(Piece* p){
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (p->shape[i][j] != ' ')
                board[p->y+i][p->x+j] = p->shape[i][j];
}

void initBoard(){
    for (int i = 0 ; i < H ; i++)
        for (int j = 0 ; j < W ; j++)
            if ((i==H-1)||(j==0)||(j==W-1)) board[i][j]='#';
            else board[i][j]=' ';
}
void draw(){
    gotoxy(0,0);
    for (int i = 0 ; i < H ; i++, cout<<endl)
        for (int j = 0 ; j < W ; j++){
            if(board[i][j]==' ')       cout<<"  ";
            else if(board[i][j]=='#')  cout<<(char)178<<(char)178;
            else                       cout<<(char)219<<(char)219;
        }
}

bool canMove(Piece* p, int dx, int dy){
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (p->shape[i][j] != ' '){
                int tx=p->x+j+dx, ty=p->y+i+dy;
                if (tx<1||tx>=W-1||ty>=H-1) return false;
                if (board[ty][tx] != ' ')   return false;
            }
    return true;
}


void removeLine() {
    int clearedThisTurn = 0;
    for (int i = H-2; i > 0; i--) {
        int j;
        for (j = 1; j < W-1; j++)
            if (board[i][j] == ' ') break;
        if (j == W-1) {
            clearedThisTurn++;
            for (int ii = i; ii > 0; ii--)
                for (int col = 1; col < W-1; col++)
                    board[ii][col] = board[ii-1][col];
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

int main(){
    srand(time(0));
    system("cls");
    initBoard();

    
    Piece* current = createRandomPiece();

    while (1){
        boardDelBlock(current);
        if (kbhit()){
            char c = getch();
       
            if (c=='a' && canMove(current,-1,0)) current->x--;
            if (c=='d' && canMove(current, 1,0)) current->x++;
            if (c=='x' && canMove(current, 0,1)) current->y++;
           
            if (c=='w'){ boardDelBlock(current); current->rotate(); }
            if (c=='q') break;
        }
        if (canMove(current,0,1)) current->y++;
        else {
            block2Board(current);
            removeLine();
         
            delete current;
            current = createRandomPiece();
        }
        block2Board(current);
        draw();
        Sleep(Speed);
    }

    delete current;
    return 0;
}