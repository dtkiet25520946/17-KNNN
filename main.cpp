
#include <iostream>
#include <conio.h>
#include <ctime>
#include <windows.h>
using namespace std;
#define H 20
#define W 15
int Speed = 600;// tăng mốc thời gian
int lineCleared = 0;
char board[H][W] = {} ;
char old_board[H][W] = {}; // Mảng lưu trạng thái cũ

void UpdateSpeed(){
    Speed = Speed - (lineCleared * 20);
    if(Speed<100) Speed = 100;
}

class Piece {
public:
    char shape[4][4];
    int x, y;
    int color;
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
        color = 12;
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
        color = 10;
        char s[4][4] = {{' ',' ',' ',' '},{' ','O','O',' '},{' ','O','O',' '},{' ',' ',' ',' '}};
        memcpy(shape, s, sizeof(s));
    }
    char symbol() override { return 'O'; }
    void rotate() override {}
};
class TPiece : public Piece {
public:
    TPiece() {
        color = 9;
        char s[4][4] = {{' ',' ',' ',' '},{' ','T',' ',' '},{'T','T','T',' '},{' ',' ',' ',' '}};
        memcpy(shape, s, sizeof(s));
    }
    char symbol() override { return 'T'; }
    void rotate() override { rotateClockwise(); }
};
class SPiece : public Piece {
public:
    SPiece() {
        color = 11;
        char s[4][4] = {{' ',' ',' ',' '},{' ','S','S',' '},{'S','S',' ',' '},{' ',' ',' ',' '}};
        memcpy(shape, s, sizeof(s));
    }
    char symbol() override { return 'S'; }
    void rotate() override { rotateClockwise(); }
};
class ZPiece : public Piece {
public:
    ZPiece() {
        color = 13;
        char s[4][4] = {{' ',' ',' ',' '},{'Z','Z',' ',' '},{' ','Z','Z',' '},{' ',' ',' ',' '}};
        memcpy(shape, s, sizeof(s));
    }
    char symbol() override { return 'Z'; }
    void rotate() override { rotateClockwise(); }
};
class JPiece : public Piece {
public:
    JPiece() {
        color = 14;
        char s[4][4] = {{' ',' ',' ',' '},{'J',' ',' ',' '},{'J','J','J',' '},{' ',' ',' ',' '}};
        memcpy(shape, s, sizeof(s));
    }
    char symbol() override { return 'J'; }
    void rotate() override { rotateClockwise(); }
};
class LPiece : public Piece {
public:
    LPiece() {
        color = 2;
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
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color);
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
    for (int i = 0 ; i < H ; i++, cout<<endl){
        for (int j = 0 ; j < W ; j++){
            if(board[i][j] != old_board[i][j]){
                // Chỉ vẽ lại khi ô có thay đổi
                gotoxy(j*2, i);
                if(board[i][j]==' ') {
                    setColor(7);
                    cout<<"  ";
                }
                else if(board[i][j]=='#') {
                     setColor(7);
                     cout<<(char)178<<(char)178;
                }
                else {
                    if (board[i][j]=='I') setColor(12);
                    else if (board[i][j]=='O') setColor(10);
                    else if (board[i][j]=='T') setColor(9);
                    else if (board[i][j]=='S') setColor(11);
                    else if (board[i][j]=='Z') setColor(13);
                    else if (board[i][j]=='J') setColor(14);
                    else if (board[i][j]=='L') setColor(2);
                    cout<<(char)219<<(char)219;
                }
            }
        }
    }
    setColor(7);
}

void drawScoreAndControls(int score){ // Thông tin bao gồm (Điểm và bảng điều khiển)
    // Điểm
    gotoxy(W * 2 + 3, 1); cout << "SCORE: " << (lineCleared * 100) << "   ";
    gotoxy(W * 2 + 3, 2); cout << "LINES: " << lineCleared << "   ";
    // Bảng điều khiển
    gotoxy(W * 2 + 3, 4); cout << "CONTROLS:";
    gotoxy(W * 2 + 3, 6); cout<<"A: Left    D: Right";
    gotoxy(W * 2 + 3, 7); cout<<"X: Down    W: Rotate";
    gotoxy(W * 2 + 3, 8); cout<<"    Q: Exit";
    // Chức năng
    gotoxy(W * 2 + 3, 9); cout<<"Space: Hard Drop";
    gotoxy(W * 2 + 3, 10);
    if(score<500) cout<<"[LOCKED - 500]";
    else cout<<"  -UNLOCKED-  ";
}

void drawNextPiece(Piece* next, int score) {
    gotoxy(W * 2 + 3, 11); cout << "--------------------";
    gotoxy(W * 2 + 3, 12); cout << "NEXT PIECE:";

    if (score >= 1000) {
        // Xóa dòng Locked nếu đủ điểm
        gotoxy(W * 2 + 3, 13); cout << "                         ";
        for (int i = 0; i < 4; i++) {
            gotoxy(W * 2 + 5, 13 + i);
            for (int j = 0; j < 4; j++) {
                if (next->shape[i][j] != ' ') cout << (char)219 << (char)219;
                else cout << "  ";
            }
        }
    } else {
        // Đủ điểm
        gotoxy(W * 2 + 3, 13); cout << "[LOCKED - NEED 1000 PTS]";
        for(int i = 1; i < 4; i++) {
            gotoxy(W * 2 + 5, 13 + i); cout << "                  ";
        }
    }
    gotoxy(W * 2 + 3, 17); cout << "--------------------";
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
        Sleep(10);
    }
}

void gameover(){
    system("cls");

    int startY = H/2 - 3;
    int startX = (W*2) / 4;

    gotoxy(startX, startY);     cout << "=============================";
    gotoxy(startX, startY + 2); cout << "*        GAME OVER          *";
    gotoxy(startX, startY + 4); cout << "=============================";

    gotoxy(startX, startY + 5); cout << "  Score: " << (lineCleared * 100);
    gotoxy(startX, startY + 6); cout << "  Lines Cleared: " << lineCleared;

    gotoxy(startX, startY + 8); cout << "Bam bat ky phim nao de thoat.";
    getch();
}

int main(){
    srand(time(0));
    system("cls");
    initBoard();

    Piece* current = createRandomPiece(); // Chọn piece
    Piece* next = createRandomPiece(); // Chọn piece kế tiếp (chỉ phục vụ tính năng)
    int fallTimer = 0; // Đếm thời gian rơi
    bool isSoftDrop = false;//trạng thái rơi(true = nhanh, false = bình thường)
    while (1){
        boardDelBlock(current);

        if (kbhit()){
            char c = getch();

            if (c=='a' && canMove(current,-1,0)) current->x--;
            if (c=='d' && canMove(current, 1,0)) current->x++;
            if (c=='x' && canMove(current, 0,1)){ isSoftDrop = true; }// trạng thái rơi chuyển thành rơi nhanh
            if (c=='w'){ boardDelBlock(current); current->rotate(); }
            if (c=='q'){ delete current; break; }
            if (c=='e'){ lineCleared++; UpdateSpeed();} // Tool
            // Hard drop
            if (c==' ' && lineCleared*100 >= 500){
                while(canMove(current, 0, 1)){current->y++;}
                fallTimer = 0;
                isSoftDrop = false; // chuyển về trạng thái bình thường cho gạch tiếp theo
            }
        }
        if (isSoftDrop) {
            fallTimer += 50; // Nếu đang bật chế độ rơi nhanh, cộng 50 để gạch tăng tốc dịch xuống
        } else { // rơi bình thường
        // Xử lý rơi tự động
        fallTimer += 10; // sau mỗi 10ms, cộng dồn
        }
        if (fallTimer >= Speed) { // Khi đủ frame, piece bắt đầu rơi
            if (canMove(current,0,1)) {
                current->y++;
            } else {
                // chạm đáy
                block2Board(current);
                removeLine();
                delete current;
                isSoftDrop = false;// chuyển sang trạng thái bình thường cho gạch tiếp theo
                // Next Piece
                if(lineCleared*100 >= 1000){
                    current = next;
                    next = createRandomPiece();
                }
                else{current = createRandomPiece();}
                // Thua game
                if (!canMove(current, 0, 0)) {
                    delete current;
                    gameover();
                    break;
                }
            }
            fallTimer = 0; // Reset bộ đếm rơi

        }
        block2Board(current);
        draw();
        drawScoreAndControls(lineCleared * 100);
        drawNextPiece(next, lineCleared*100);
        memcpy(old_board, board, sizeof(board));
        Sleep(10);
    }

    return 0;
}
