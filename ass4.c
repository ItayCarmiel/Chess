/*******
 * Itay Carmiel
 * 208464198
 * 01
 * ass04
 *******/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>

typedef struct {
    char srcCol, destCol,piece,isClear,promotion;
    int isWhite, isCapture, isPromotion, isCheck,isOwnCheck, isMate, comIsLegal, moveIsLegal,movementIsLeagal;
    int roadIsClear,roadToCheck,isHit,change,destRow,srcRow;
} Move;

//declartion of PGN fuctions
int isNegative(int a, int b);
int makeMove(char board[][SIZE], char pgn[], int isWhiteTurn);
void changeBoard (Move* m,char board[][SIZE], char pgn[],int isWhiteTurn);
void moveIsLegal (Move* m,char board[][SIZE], char pgn[],int isWhiteTurn);
void commandIsLegal (Move* m,char board[][SIZE], char pgn[],int isWhiteTurn);
void isWhite (Move* m,char board[][SIZE], char pgn[],int isWhiteTurn);
void whatPiece (Move* m,char board[][SIZE], char pgn[],int isWhiteTurn);
void findRowDest (Move* m,char board[][SIZE], char pgn[],int isWhiteTurn);
void findColDest (Move* m,char board[][SIZE], char pgn[],int isWhiteTurn);
void isHit(Move* m,char board[][SIZE], char pgn[],int isWhiteTurn);
void isClear (Move* m,char board[][SIZE], char pgn[],int isWhiteTurn);
void movementIsLegal (Move* m,char board[][SIZE], char pgn[],int isWhiteTurn);
void promotion (Move* m,char board[][SIZE], char pgn[],int isWhiteTurn);
void isPromotion (Move* m,char board[][SIZE], char pgn[],int isWhiteTurn);
int kingRow (char board[][SIZE],int isWhiteTurn);
int kingCo (char board[][SIZE],int isWhiteTurn);
void isChess(Move* m,char board[][SIZE], char pgn[],int isWhiteTurn);
void roadIsClear (Move* m,char board[][SIZE],char piece);
void isOwnChess (Move* m,char board[][SIZE],int isWhiteTurn);
void roadToCheck (Move* m,char board[][SIZE],char piece,int a,char b,int c,char d);
char toLower(char a);
int isUpper(char a);
int overLimit(int a, int b);

/**********************************************************
 * Function Name: toLower
 * Input: char a
 * Output: cahr a
 * Function Operation: the function convert capital letter to lower
 *********************************************************/
char toLower(char a) {
    if (a>=65 && a<=90)
        a+=32;
    return a;
}
/**********************************************************
 * Function Name: isUpper
 * Input: char a
 * Output: 0 or 1
 * Function Operation: the function check if the char is capital
 *********************************************************/
int isUpper(char a) {
    //if (a>=97 && a<=122)
    //    a-=32;
    // return a;
    if (a>=65 && a<=90) {
        return 1;
    }
    return 0;
}
/**********************************************************
 * Function Name: islow
 * Input: char a
 * Output: 1 or 0
 * Function Operation: the function check if the char is not capital
 *********************************************************/
int islow(char a) {
    if (a>=97 && a<=122)
        return 1;
    return 0;
}
/**********************************************************
 * Function Name: isNegative
 * Input: int a, int b
 * Output: 0 or 1
 * Function Operation: the function return 1 if the sum is negative, else return 0
 *********************************************************/
int isNegative(int a, int b) {
    if (a-b>=0){
        return 0;
    }
    return 1;
}
/**********************************************************
 * Function Name: overLimit
 * Input: int a, int b
 * Output: 0 or 1
 * Function Operation: the function return 1 if the sum is over SIZE, else return 0
 *********************************************************/
int overLimit(int a, int b) {
    if ((a+b)<=SIZE){
        return 0;
    }
    return 1;
}
/**********************************************************
 * Function Name: printColumns
 * Input: none
 * Output: none
 * Function Operation: the function print a row of letters from A to a+size
 *********************************************************/
void printColumns() {
    char column = toupper('a');
    printf("* |");
    for (int i = 0; i < SIZE; i++) {
        if (i) {
            printf(" ");
        }
        printf("%c", column);
        column++;
    }
    printf("| *\n");
}
/**********************************************************
 * Function Name: printSpacers
 * Input: none
 * Output: none
 * Function Operation: the function print row of '-'
 *********************************************************/
void printSpacers() {
    printf("* -");
    for (int i = 0; i < SIZE; i++) {
        printf("--");
    }
    printf(" *\n");
}
/**********************************************************
 * Function Name: createBoard
 * Input: char board[][],char fen[]
 * Output: none
 * Function Operation: the funtion convert 'fen' to 2D array
 *********************************************************/
void createBoard(char board[][SIZE], char fen[]) {
    int sFen=0, row=0, column=0, numJump;
    while (fen[sFen] != 0) {
        // end of a row
        if (fen[sFen] == '/') {
            row++;
            column=0;
        }
            // alpha case
        else if (isalpha(fen[sFen])) {
            board[row][column] = fen[sFen];
            column++;
        }
            // digit case
        else if (isdigit(fen[sFen])) {
            numJump = (fen[sFen] - 48);
            for (int s = 0; s < numJump; s++) {
                board[row][column] = ' ';
                column++;
            }
        }
        sFen++;
    }
}
/**********************************************************
 * Function Name: printBoard
 * Input: char board[][]
 * Output: none
 * Function Operation: the function print the board
 * like the function 'printBoardFromFEN'
 *********************************************************/
void printBoard(char board[][SIZE]){
    int rowIdx;
    printColumns();
    printSpacers();
    rowIdx = SIZE;
    for (int i=0; i<SIZE; i++){
        printf("%d ", rowIdx);
        for (int j=0; j<SIZE; j++){
            printf("|%c",board[i][j]);
        }
        printf("| %d\n", rowIdx--);
    }
    printSpacers();
    printColumns();
}
/**********************************************************
 * Function Name: whatPiece
 * Input: char board[][], char pgn[],int isWhiteTurn
 * Output: char piece
 * Function Operation: the function sent the letter of the moving piece
 *********************************************************/
void whatPiece (Move* m,char board[][SIZE], char pgn[],int isWhiteTurn){
    char piece;
    piece = pgn [0];
    //case it's R/N/B/Q/K
    if (isUpper(piece)){
        if (isWhiteTurn)
            m->piece =  piece;
        else
            m->piece = (toLower(piece));
    }
        //case it's pawn
    else {
        piece = 'P';
        if (isWhiteTurn)
            m->piece =  piece;
        else
            m->piece = (toLower(piece));
    }
}
/**********************************************************
 * Function Name: findRowDest
 * Input: char board[][], char pgn[],int isWhiteTurn
 * Output: int number
 * Function Operation: the function sent the future row of the piece in the array
 * if it's not have one, the punction return SIZE+1
 *********************************************************/
void findRowDest (Move* m,char board[][SIZE], char pgn[],int isWhiteTurn){
    int destR=-1,pg=0;
    while (pgn[pg] != 0){
        //check if it's number
        if (pgn[pg]>47 && pgn[pg]<58)
            destR = (pgn[pg] - 48);
        pg++;
    }
    int num = SIZE-destR;
    m->destRow = num;
}
/**********************************************************
* Function Name: findColDest
* Input: char board[][], char pgn[],int isWhiteTurn
* Output: char column
* Function Operation: the function sent the future column of the piece in the array
* if it's not have one, the punction return '0'
*********************************************************/
void findColDest (Move* m,char board[][SIZE], char pgn[],int isWhiteTurn){
    int pgc=0;
    char destC='0';
    while (pgn[pgc] != 0) {
        if (pgn[pgc] > 96 && pgn[pgc] < 107)
            destC = pgn[pgc];
        pgc++;
    }
    m->destCol = destC;
}
/**********************************************************
 * Function Name: isHit
 * Input: char board[][], char pgn[],int isWhiteTurn
 * Output: 1 or 0
 * Function Operation: the function send 1 if there is 'x' in the pgn
 * if not - send 0;
 *********************************************************/
void isHit(Move* m,char board[][SIZE], char pgn[],int isWhiteTurn){
    int pgc=0;
    m->isHit =0;
    while (pgn[pgc] != 0) {
        if (pgn[pgc] == 'x')
            m->isHit =1;
        pgc++;
    }
}
/**********************************************************
 * Function Name: isClear
 * Input: char board[][], char pgn[],int isWhiteTurn
 * Output: '0' or char
 * Function Operation: the function send '0' if the destiny point is clear
 * if not - send the char of the piece
 *********************************************************/
void isClear (Move* m,char board[][SIZE], char pgn[],int isWhiteTurn){
    int desR,desCo;
    char desC;
    desR = m->destRow;
    desC = m->destCol;
    desCo = (desC-97);
    if (board[desR][desCo] == ' ')
        m->isClear = '0';
    else
        m->isClear = board[desR][desCo];
}
/**********************************************************
 * Function Name: isWhite
 * Input: char board[][], char pgn[],int isWhiteTurn
 * Output: 1 or 0
 * Function Operation: the function send 1 if isWhiteTurn is true
 * if not - send 0
 *********************************************************/
void isWhite (Move* m,char board[][SIZE], char pgn[],int isWhiteTurn) {
    int x = m->srcRow;
    char y = m->srcCol;
    //convert char to int
    int con = (y-97);
    //check if white
    m->isWhite = 0;
    if ((isUpper(board[x][con])) && (isWhiteTurn))
        m->isWhite = 1;
        //check if black
    else if ((islower(board[x][con])) && (isWhiteTurn == 0))
        m->isWhite = 1;
}
/**********************************************************
 * Function Name: isPromotion
 * Input: char board[][], char pgn[],int isWhiteTurn
 * Output: 1 or 0
 * Function Operation: the function send 1 if there is a promotion and decleration
 * if not (decleration xor in reality) - send 0
 *********************************************************/
void isPromotion (Move* m,char board[][SIZE], char pgn[],int isWhiteTurn){
    int pgc=0,des,check=0;
    char piece;
    while (pgn[pgc]!=0){
        if (pgn[pgc]=='=')
            check=1;
        pgc++;
    }
    m->isPromotion =0;
    if (check==0)
        m->isPromotion = 1;
    piece = m->piece;
    des = m->destRow;
    if ((piece == 'P') && (des == 0)){
        if (check)
            m->isPromotion = 1;
    }
    if ((piece == 'p') && (des == (SIZE-1))){
        if (check)
            m->isPromotion = 1;
    }
}
/**********************************************************
 * Function Name: promotion
 * Input: char board[][], char pgn[],int isWhiteTurn
 * Output: '0', or char
 * Function Operation: the function return '0' if there is no promotion
 * and if there is it return the char of the promotion's piece
 *********************************************************/
void promotion (Move* m,char board[][SIZE], char pgn[],int isWhiteTurn){
    int pgc=0;
    char pie='0';
    while (pgn[pgc]!=0){
        if (pgn[pgc]=='=')
            pie = pgn[pgc+1];
        pgc++;
    }
    if (isWhiteTurn)
        m->promotion = pie;
    else {
        pie = tolower(pie);
        m->promotion = pie;
    }
}
void roadToCheck (Move* m,char board[][SIZE],char piece,int a,char b,int c,char d){
    int disC;
    char baseCo = b;
    char desCo = d;
    int baseR = a;
    int desR = c;
    if (baseCo>=desCo)
        disC = (baseCo - desCo);
    if (baseCo<desCo)
        disC = (desCo - baseCo);
    m->roadToCheck = 0;
    switch (piece){
        case 'N':
        case 'n':
        case 'K':
        case 'k':
        case 'P':
        case 'p': {
            m->roadToCheck = 0;
            break;
        }
        case 'R':
        case 'r':{
            //row clear
            if (baseR>desR){
                for (int i=desR+1; i<baseR; i++){
                    if(board[i][desCo]!=' ')
                        m->roadToCheck = 1;
                }
            }
            if (baseR<desR){
                for (int i=baseR+1; i<desR; i++){
                    if(board[i][desCo]!=' ')
                        m->roadToCheck = 1;
                }
            }
            //column clear
            if (baseCo>desCo){
                for (int i=desCo+1; i<baseCo; i++){
                    if(board[desR][i]!=' ')
                        m->roadToCheck = 1;
                }
            }
            if (baseCo<desCo){
                for (int i=baseCo+1; i<desCo; i++){
                    if(board[desR][i]!=' ')
                        m->roadToCheck = 1;
                }
            }
            break;
        }
        case 'B':
        case 'b': {
            //right & up
            if ((desR > baseR) && (desCo > baseCo)) {
                for (int i = 1; i < disC; i++) {
                    if (board[baseR + i][baseCo + i] != ' ')
                        m->roadToCheck = 1;
                }
            }
                //left & down
            else if ((desR < baseR) && (desCo < baseCo)) {
                for (int i = 1; i < disC; i++) {
                    if (board[baseR - i][baseCo - i] != ' ')
                        m->roadToCheck = 1;
                }
            }
                //right & down
            else if ((desR < baseR) && (desCo > baseCo)) {
                for (int i = 1; i < disC; i++) {
                    if (board[baseR - i][baseCo + i] != ' ')
                        m->roadToCheck = 1;
                }
            }
                //left & up
            else if ((desR > baseR) && (desCo < baseCo)) {
                for (int i = 1; i < disC; i++) {
                    if (board[baseR + i][baseCo - i] != ' ')
                        m->roadToCheck = 1;
                }
            }
            break;
        }
        case 'Q':
        case 'q': {
            //row clear
            if ((baseR == desR) || (baseCo == desCo)) {
                if (baseR >= desR) {
                    for (int i = desR+1; i < baseR; i++) {
                        if (board[i][desCo] != ' ')
                            m->roadToCheck = 1;
                    }
                }
                if (baseR < desR) {
                    for (int i = baseR+1; i < desR; i++) {
                        if (board[i][desCo] != ' ')
                            m->roadToCheck = 1;
                    }
                }
                //column clear
                if (baseCo >= desCo) {
                    for (int i = desCo+1; i < baseCo; i++) {
                        if (board[desR][i] != ' ')
                            m->roadToCheck = 1;
                    }
                }
                if (baseCo < desCo) {
                    for (int i = baseCo+1; i < desCo; i++) {
                        if (board[desR][i] != ' ')
                            m->roadToCheck = 1;
                    }
                }
            }
                //horizon case
            else {
                //right & up
                if ((desR > baseR) && (desCo > baseCo)) {
                    for (int i = 1; i < disC; i++) {
                        if (board[baseR + i][baseCo + i] != ' ')
                            m->roadToCheck = 1;
                    }
                }
                    //left & down
                else if ((desR < baseR) && (desCo < baseCo)) {
                    for (int i = 1; i < disC; i++) {
                        if (board[baseR - i][baseCo - i] != ' ')
                            m->roadToCheck = 1;
                    }
                }
                    //right & down
                else if ((desR < baseR) && (desCo > baseCo)) {
                    for (int i = 1; i < disC; i++) {
                        if (board[baseR - i][baseCo + i] != ' ')
                            m->roadToCheck = 1;
                    }
                }
                    //left & up
                else if ((desR > baseR) && (desCo < baseCo)) {
                    for (int i = 1; i < disC; i++) {
                        if (board[baseR + i][baseCo - i] != ' ')
                            m->roadToCheck = 1;
                    }
                }
            }
            break;
        }
    }
}
/**********************************************************
 * Function Name: roadIsClear
 * Input: char [][], char, int, int, int, int
 * Output: int number
 * Function Operation: the function return 1 if the road clear from [dr][dc]
 * until [kr][kc], and 0 if no
 *********************************************************/
void roadIsClear (Move* m,char board[][SIZE],char piece){
    int disC;
    char baseC = m->srcCol;
    char desC = m->destCol;
    int baseR = m->srcRow;
    int desR = m->destRow;
    int baseCo = (baseC-97);
    int desCo = (desC-97);
    if (baseCo>=desCo)
        disC = (baseCo - desCo);
    if (baseCo<desCo)
        disC = (desCo - baseCo);
    m->roadIsClear = 1;
    switch (piece){
        case 'N':
        case 'n':
        case 'K':
        case 'k':
        case 'P':
        case 'p': {
            m->roadIsClear = 1;
            break;
        }
        case 'R':
        case 'r':{
            //row clear
            if (baseR>desR){
                for (int i=desR+1; i<baseR; i++){
                    if(board[i][desCo]!=' ')
                        m->roadIsClear = 0;
                }
            }
            if (baseR<desR){
                for (int i=baseR+1; i<desR; i++){
                    if(board[i][desCo]!=' ')
                        m->roadIsClear = 0;
                }
            }
            //column clear
            if (baseCo>desCo){
                for (int i=desCo+1; i<baseCo; i++){
                    if(board[desR][i]!=' ')
                        m->roadIsClear = 0;
                }
            }
            if (baseCo<desCo){
                for (int i=baseCo+1; i<desCo; i++){
                    if(board[desR][i]!=' ')
                        m->roadIsClear = 0;
                }
            }
            break;
        }
        case 'B':
        case 'b': {
            //right & up
            if ((desR > baseR) && (desCo > baseCo)) {
                for (int i = 1; i < disC; i++) {
                    if (board[baseR + i][baseCo + i] != ' ')
                        m->roadIsClear = 0;
                }
            }
                //left & down
            else if ((desR < baseR) && (desCo < baseCo)) {
                for (int i = 1; i < disC; i++) {
                    if (board[baseR - i][baseCo - i] != ' ')
                        m->roadIsClear = 0;
                }
            }
                //right & down
            else if ((desR < baseR) && (desCo > baseCo)) {
                for (int i = 1; i < disC; i++) {
                    if (board[baseR - i][baseCo + i] != ' ')
                        m->roadIsClear = 0;
                }
            }
                //left & up
            else if ((desR > baseR) && (desCo < baseCo)) {
                for (int i = 1; i < disC; i++) {
                    if (board[baseR + i][baseCo - i] != ' ')
                        m->roadIsClear = 0;
                }
            }
            break;
        }
        case 'Q':
        case 'q': {
            //row clear
            if ((baseR == desR) || (baseCo == desCo)) {
                if (baseR >= desR) {
                    for (int i = desR+1; i < baseR; i++) {
                        if (board[i][desCo] != ' ')
                            m->roadIsClear = 0;
                    }
                }
                if (baseR < desR) {
                    for (int i = baseR+1; i < desR; i++) {
                        if (board[i][desCo] != ' ')
                            m->roadIsClear = 0;
                    }
                }
                //column clear
                if (baseCo >= desCo) {
                    for (int i = desCo+1; i < baseCo; i++) {
                        if (board[desR][i] != ' ')
                            m->roadIsClear = 0;
                    }
                }
                if (baseCo < desCo) {
                    for (int i = baseCo+1; i < desCo; i++) {
                        if (board[desR][i] != ' ')
                            m->roadIsClear = 0;
                    }
                }
            }
                //horizon case
            else {
                //right & up
                if ((desR > baseR) && (desCo > baseCo)) {
                    for (int i = 1; i < disC; i++) {
                        if (board[baseR + i][baseCo + i] != ' ')
                            m->roadIsClear = 0;
                    }
                }
                    //left & down
                else if ((desR < baseR) && (desCo < baseCo)) {
                    for (int i = 1; i < disC; i++) {
                        if (board[baseR - i][baseCo - i] != ' ')
                            m->roadIsClear = 0;
                    }
                }
                    //right & down
                else if ((desR < baseR) && (desCo > baseCo)) {
                    for (int i = 1; i < disC; i++) {
                        if (board[baseR - i][baseCo + i] != ' ')
                            m->roadIsClear = 0;
                    }
                }
                    //left & up
                else if ((desR > baseR) && (desCo < baseCo)) {
                    for (int i = 1; i < disC; i++) {
                        if (board[baseR + i][baseCo - i] != ' ')
                            m->roadIsClear = 0;
                    }
                }
            }
            break;
        }
    }
}
/**********************************************************
 * Function Name: kingRow
 * Input: char board[][], int isWhiteTurn
 * Output: int number
 * Function Operation: the function sent the current row of the king
 * according to 'isWhiteTurn'
 *********************************************************/
int kingRow (char board[][SIZE],int isWhiteTurn) {
    if (isWhiteTurn) {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (board[i][j] == 'k')
                    return i;
            }
        }
    }
    if (isWhiteTurn == 0) {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (board[i][j] == 'K')
                    return i;
            }
        }
    }
}
/**********************************************************
 * Function Name: kingCo
 * Input: char board[][], int isWhiteTurn
 * Output: int number
 * Function Operation: the function sent the current column of the king
 * according to 'isWhiteTurn'
 *********************************************************/
int kingCo (char board[][SIZE],int isWhiteTurn) {
    if (isWhiteTurn) {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (board[i][j] == 'k')
                    return j;
            }
        }
    }
    if (isWhiteTurn == 0) {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (board[i][j] == 'K')
                    return j;
            }
        }
    }
}
/**********************************************************
 * Function Name: isChess
 * Input: char board[][], char pgn[],int isWhiteTurn
 * Output: 1 or 0
 * Function Operation: the function return 1 if there is a chess and decleration or non
 * if only one is true, return 0
 *********************************************************/
void isChess(Move* m,char board[][SIZE], char pgn[],int isWhiteTurn){
    int kingR,kingC,isChe=0,isCheDec=0,pgc=0,max;
    kingR = kingRow(board, isWhiteTurn);
    kingC = kingCo(board, isWhiteTurn);
    if (kingC >= kingR)
        max = kingC;
    if (kingR > kingC)
        max = kingR;
    while (pgn[pgc]!= 0){
        if ((pgn[pgc] == '+') || (pgn[pgc] == '#'))
            isCheDec = 1;
        pgc++;
    }
    if (isWhiteTurn) {
        for (int i = 0; i < SIZE; i++) {
            //rook case
            if (board[kingR][i] == 'R') {
                roadToCheck(m,board, 'R', kingR, kingC, kingR, i);
                if (m->roadToCheck == 0)
                    isChe = 1;
            }
            if (board[i][kingC] == 'R') {
                roadToCheck(m,board, 'R', kingR, kingC, i, kingC);
                if (m->roadToCheck == 0)
                    isChe = 1;
            }
            //queen case
            if (board[kingR][i] == 'Q') {
                roadToCheck(m,board, 'Q', kingR, kingC, kingR, i);
                if (m->roadToCheck == 0)
                    isChe = 1;
            }
            if (board[i][kingC] == 'Q') {
                roadToCheck(m,board, 'Q', kingR, kingC, i, kingC);
                if (m->roadToCheck == 0)
                    isChe = 1;
            }
        }
        //knight case
        int a = isNegative(kingR,1);
        int b = isNegative(kingR,2);
        if ((board[kingR + 1][kingC + 2] == 'N') || (board[kingR + 1][kingC - 2] == 'N')
            || ((board[kingR - 1][kingC + 2] == 'N')&&(a!=1))|| ((board[kingR - 1][kingC - 2] == 'N')&&(a!=1))
            || (board[kingR + 2][kingC + 1] == 'N') || (board[kingR + 2][kingC - 1] == 'N')
            || ((board[kingR - 2][kingC + 1] == 'N') &&(b!=1))|| ((board[kingR - 2][kingC - 1] == 'N')&&(b!=1))) {
            isChe = 1;
        }
        //pawn case
        int nega = isNegative(kingR,1);
        if ((board[kingR - 1][kingC - 1] == 'P' && nega!=1) || (board[kingR - 1][kingC + 1] == 'P' && nega!=1))
            isChe = 1;
        //bishop and queen case
        int neg1,neg2,over1,over2;
        for (int i = 1; i <= max; i++) {
            neg1 = isNegative(kingR,i);
            neg2 = isNegative(kingC,i);
            over1 = overLimit(kingR,i);
            over2 = overLimit(kingC,i);
            if (board[kingR + i][kingC + i] == 'B'&& over1!=1 && over2!=1) {
                roadToCheck(m,board, 'B', kingR, kingC, kingR + i, kingC + i);
                if (m->roadToCheck == 0)
                    isChe = 1;
            }
            if (board[kingR + i][kingC + i] == 'Q'&& over1!=1 && over2!=1) {
                roadToCheck(m,board, 'Q', kingR, kingC, kingR + i, kingC + i);
                if (m->roadToCheck == 0)
                    isChe = 1;
            }
            if (board[kingR - i][kingC - i] == 'B' && neg1 !=1 && neg2!=1) {
                roadToCheck(m,board, 'B', kingR, kingC, kingR - i, kingC - i);
                if (m->roadToCheck == 0)
                    isChe = 1;
            }
            if (board[kingR - i][kingC - i] == 'Q'&& neg1 !=1 && neg2!=1) {
                roadToCheck(m,board, 'Q', kingR, kingC, kingR - i, kingC - i);
                if (m->roadToCheck == 0)
                    isChe = 1;
            }
            if (board[kingR + i][kingC - i] == 'B'&& over1 !=1 && neg2!=1) {
                roadToCheck(m,board, 'B', kingR, kingC, kingR + i, kingC - i);
                if (m->roadToCheck == 0)
                    isChe = 1;
            }
            if (board[kingR + i][kingC - i] == 'Q' && over1 !=1 && neg2!=1) {
                roadToCheck(m,board, 'Q', kingR, kingC, kingR + i, kingC - i);
                if (m->roadToCheck == 0)
                    isChe = 1;
            }
            if (board[kingR - i][kingC + i] == 'B'&& neg1 !=1 && over2!=1) {
                roadToCheck(m,board, 'B', kingR, kingC, kingR - i, kingC + i);
                if (m->roadToCheck == 0)
                    isChe = 1;
            }
            if (board[kingR - i][kingC + i] == 'Q'&& neg1 !=1 && over2!=1) {
                roadToCheck(m,board, 'Q', kingR, kingC, kingR - i, kingC + i);
                if (m->roadToCheck == 0)
                    isChe = 1;
            }
        }
    }
    if (isWhiteTurn == 0){
        for (int i = 0; i < SIZE; i++) {
            //rook case
            if (board[kingR][i] == 'r') {
                roadToCheck(m,board, 'r', kingR, kingC, kingR, i);
                if (m->roadToCheck == 0)
                    isChe = 1;
            }
            if (board[i][kingC] == 'r') {
                roadToCheck(m,board, 'r', kingR, kingC, i, kingC);
                if (m->roadToCheck == 0)
                    isChe = 1;
            }
            //queen case
            if (board[kingR][i] == 'q') {
                roadToCheck(m,board, 'q', kingR, kingC, kingR, i);
                if (m->roadToCheck == 0)
                    isChe = 1;
            }
            if (board[i][kingC] == 'q') {
                roadToCheck(m,board, 'q', kingR, kingC, i, kingC);
                if (m->roadToCheck == 0)
                    isChe = 1;
            }
        }
        //knight case
        int a=isNegative(kingR,1);
        int b = isNegative(kingR,2);

        if ((board[kingR + 1][kingC + 2] == 'n') || (board[kingR + 1][kingC - 2] == 'n')
            || ((board[kingR - 1][kingC + 2] == 'n')&&(a!=1))|| ((board[kingR - 1][kingC - 2] == 'n')&&(a!=1))
            || (board[kingR + 2][kingC + 1] == 'n') || (board[kingR + 2][kingC - 1] == 'n')
            || ((board[kingR - 2][kingC + 1] == 'n')&&(b!=1)) || ((board[kingR - 2][kingC - 1] == 'n')&&(b!=1))) {
            isChe = 1;
        }
        //pawn case
        if ((board[kingC + 1][kingR + 1] == 'p') || (board[kingR + 1][kingC + 1] == 'P'))
            isChe = 1;
        //bishop and queen case
        int neg1,neg2,over1,over2;
        for (int i = 1; i <= max; i++) {
            neg1 = isNegative(kingR,i);
            neg2 = isNegative(kingC,i);
            over1 = overLimit(kingR,i);
            over2 = overLimit(kingC,i);
            if (board[kingR + i][kingC + i] == 'b'&& over1!=1 && over2!=1) {
                roadToCheck(m,board, 'b', kingR, kingC, kingR + i, kingC + i);
                if (m->roadToCheck == 0)
                    isChe = 1;
            }
            if (board[kingR + i][kingC + i] == 'q'&& over1!=1 && over2!=1) {
                roadToCheck(m,board, 'q', kingR, kingC, kingR + i, kingC + i);
                if (m->roadToCheck == 0)
                    isChe = 1;
            }
            if (board[kingR - i][kingC - i] == 'b' && neg1 !=1 && neg2!=1) {
                roadToCheck(m,board, 'b', kingR, kingC, kingR - i, kingC - i);
                if (m->roadToCheck == 0)
                    isChe = 1;
            }
            if (board[kingR - i][kingC - i] == 'q'&& neg1 !=1 && neg2!=1) {
                roadToCheck(m,board, 'q', kingR, kingC, kingR - i, kingC - i);
                if (m->roadToCheck == 0)
                    isChe = 1;
            }
            if (board[kingR + i][kingC - i] == 'b'&& over1!=1 && neg2!=1) {
                roadToCheck(m,board, 'b', kingR, kingC, kingR + i, kingC - i);
                if (m->roadToCheck == 0)
                    isChe = 1;
            }
            if (board[kingR + i][kingC - i] == 'q'&& over1!=1 && neg2!=1) {
                roadToCheck(m,board, 'q', kingR, kingC, kingR + i, kingC - i);
                if (m->roadToCheck == 0)
                    isChe = 1;
            }
            if (board[kingR - i][kingC + i] == 'b'&& neg1 !=1 && over2!=1) {
                roadToCheck(m,board, 'b', kingR, kingC, kingR - i, kingC + i);
                if (m->roadToCheck == 0)
                    isChe = 1;
            }
            if (board[kingR - i][kingC + i] == 'q'&& neg1 !=1 && over2!=1) {
                roadToCheck(m,board, 'q', kingR, kingC, kingR - i, kingC + i);
                if (m->roadToCheck == 0)
                    isChe = 1;
            }
        }
    }
    if (isChe && isCheDec)
        m->isCheck = 1;
    else if ((isChe == 0) && (isCheDec == 0))
        m->isCheck = 1;
    else
        m->isCheck = 0;
}
/***********************************************
* Function Name: isOwnChess
* Input: char board[][],int isWhiteTurn
* Output: 1 or 0
* Function Operation: the function return 1 if there is an own chess
* if not, return 0
*********************************************************/
void isOwnChess (Move* m,char board[][SIZE],int isWhiteTurn){
    int neg;
    int kingR,kingC,isChe=0,pgc=0,max;
    //find own king location
    if (isWhiteTurn == 1) {
        kingR = kingRow(board, isWhiteTurn-1);
        kingC = kingCo(board, isWhiteTurn-1);
    }
    else {
        kingR = kingRow(board, isWhiteTurn+1);
        kingC = kingCo(board, isWhiteTurn+1);
    }
    if (kingC >= kingR)
        max = kingC;
    if (kingR > kingC)
        max = kingR;
    if (isWhiteTurn) {
        for (int i = 0; i < SIZE; i++) {
            //rook case
            if (board[kingR][i] == 'r') {
                roadToCheck(m,board, 'r', kingR, kingC, kingR, i);
                if (m->roadToCheck == 0)
                    isChe = 1;
            }
            if (board[i][kingC] == 'r') {
                roadToCheck(m,board, 'r', kingR, kingC, i, kingC);
                if (m->roadToCheck == 0)
                    isChe = 1;
            }
            //queen case
            if (board[kingR][i] == 'q') {
                roadToCheck(m,board, 'q', kingR, kingC, kingR, i);
                if (m->roadToCheck == 0)
                    isChe = 1;
            }
            if (board[i][kingC] == 'q') {
                roadToCheck(m,board, 'q', kingR, kingC, i, kingC);
                if (m->roadToCheck == 0)
                    isChe = 1;
            }
        }
        //knight case
        int a1 = isNegative(kingR,1);
        int b1 = isNegative(kingR,2);
        if ((board[kingR + 1][kingC + 2] == 'n') || (board[kingR + 1][kingC - 2] == 'n')
            || ((board[kingR - 1][kingC + 2] == 'n') && (a1!=1))|| ((board[kingR - 1][kingC - 2] == 'n')&& (a1!=1))
            || (board[kingR + 2][kingC + 1] == 'n') || (board[kingR + 2][kingC - 1] == 'n')
            || ((board[kingR - 2][kingC + 1] == 'n')&&(b1!=1)) || ((board[kingR - 2][kingC - 1] == 'n')&&(b1!=1))) {
            isChe = 1;
        }
        //pawn case
        int nega = isNegative(kingR,1);
        if (((board[kingC - 1][kingR - 1] == 'p') &&nega !=1) || (board[kingR - 1][kingC + 1] == 'p')&& nega !=1)
            isChe = 1;
        //bishop and queen case
        int neg1,neg2,over1,over2;
        for (int i = 1; i <= max; i++) {
            neg1 = isNegative(kingR,i);
            neg2 = isNegative(kingC,i);
            over1 = overLimit(kingR,i);
            over2 = overLimit(kingC,i);
            if (board[kingR + i][kingC + i] == 'b'&& over1!=1 && over2!=1) {
                roadToCheck(m,board, 'b', kingR, kingC, kingR + i, kingC + i);
                if (m->roadToCheck == 0)
                    isChe = 1;
            }
            if (board[kingR + i][kingC + i] == 'q'&& over1!=1 && over2!=1) {
                roadToCheck(m,board, 'q', kingR, kingC, kingR + i, kingC + i);
                if (m->roadToCheck == 0)
                    isChe = 1;
            }
            if (board[kingR - i][kingC - i] == 'b'&& neg1!=1 && neg2!=1) {
                roadToCheck(m,board, 'b', kingR, kingC, kingR - i, kingC - i);
                if (m->roadToCheck == 0)
                    isChe = 1;
            }
            if (board[kingR - i][kingC - i] == 'q'&& neg1!=1 && neg2!=1) {
                roadToCheck(m,board, 'q', kingR, kingC, kingR - i, kingC - i);
                if (m->roadToCheck == 0)
                    isChe = 1;
            }
            if (board[kingR + i][kingC - i] == 'b'&& over1!=1 && neg2!=1) {
                roadToCheck(m,board, 'b', kingR, kingC, kingR + i, kingC - i);
                if (m->roadToCheck == 0)
                    isChe = 1;
            }
            if (board[kingR + i][kingC - i] == 'q'&& over1!=1 && neg2!=1) {
                roadToCheck(m,board, 'q', kingR, kingC, kingR + i, kingC - i);
                if (m->roadToCheck == 0)
                    isChe = 1;
            }
            if (board[kingR - i][kingC + i] == 'b'&& neg1!=1 && over2!=1) {
                roadToCheck(m,board, 'b', kingR, kingC, kingR - i, kingC + i);
                if (m->roadToCheck == 0)
                    isChe = 1;
            }
            if (board[kingR - i][kingC + i] == 'q'&& neg1!=1 && over2!=1) {
                roadToCheck(m,board, 'q', kingR, kingC, kingR - i, kingC + i);
                if (m->roadToCheck == 0)
                    isChe = 1;
            }
        }
    }
    if (isWhiteTurn == 0){
        for (int i = 0; i < SIZE; i++) {
            //rook case
            if (board[kingR][i] == 'R') {
                roadToCheck(m,board, 'R', kingR, kingC, kingR, i);
                if (m->roadToCheck == 0)
                    isChe = 1;
            }
            if (board[i][kingC] == 'R') {
                roadToCheck(m,board, 'R', kingR, kingC, i, kingC);
                if (m->roadToCheck == 0)
                    isChe = 1;
            }
            //queen case
            if (board[kingR][i] == 'Q') {
                roadToCheck(m,board, 'Q', kingR, kingC, kingR, i);
                if (m->roadToCheck == 0)
                    isChe = 1;
            }
            if (board[i][kingC] == 'Q') {
                roadToCheck(m,board, 'Q', kingR, kingC, i, kingC);
                if (m->roadToCheck == 0)
                    isChe = 1;
            }
        }
        //knight case
        int a = isNegative(kingR,1);
        int b = isNegative(kingR,2);
        if ((board[kingR + 1][kingC + 2] == 'N') || (board[kingR + 1][kingC - 2] == 'N')
            || ((board[kingR - 1][kingC + 2] == 'N')&&(a!=1)) || ((board[kingR - 1][kingC - 2] == 'N')&&(a!=1))
            || (board[kingR + 2][kingC + 1] == 'N') || (board[kingR + 2][kingC - 1] == 'N')
            || ((board[kingR - 2][kingC + 1] == 'N')&&(b!=1)) || ((board[kingR - 2][kingC - 1] == 'N')&&(b!=1))) {
            isChe = 1;
        }
        //pawn case
        if ((board[kingR + 1][kingC - 1] == 'P') || (board[kingR + 1][kingC + 1] == 'P'))
            isChe = 1;
        //bishop and queen case
        int neg1,neg2,over1,over2;
        for (int i = 1; i <= max; i++) {
            neg1 = isNegative(kingR,i);
            neg2 = isNegative(kingC,i);
            over1 = overLimit(kingR,i);
            over2 = overLimit(kingC,i);
            if (board[kingR + i][kingC + i] == 'B'&& over1!=1 && over2!=1) {
                roadToCheck(m,board, 'B', kingR, kingC, kingR + i, kingC + i);
                if (m->roadToCheck == 0)
                    isChe = 1;
            }
            if (board[kingR + i][kingC + i] == 'Q'&& over1!=1 && over2!=1) {
                roadToCheck(m,board, 'Q', kingR, kingC, kingR + i, kingC + i);
                if (m->roadToCheck == 0)
                    isChe = 1;
            }
            if (board[kingR - i][kingC - i] == 'B'&& neg1!=1 && neg2!=1) {
                roadToCheck(m,board, 'B', kingR, kingC, kingR - i, kingC - i);
                if (m->roadToCheck == 0)
                    isChe = 1;
            }
            if (board[kingR - i][kingC - i] == 'Q'&& neg1!=1 && neg2!=1) {
                roadToCheck(m,board, 'Q', kingR, kingC, kingR - i, kingC - i);
                if (m->roadToCheck == 0)
                    isChe = 1;
            }
            if (board[kingR + i][kingC - i] == 'B'&& over1!=1 && neg2!=1) {
                roadToCheck(m,board, 'B', kingR, kingC, kingR + i, kingC - i);
                if (m->roadToCheck == 0)
                    isChe = 1;
            }
            if (board[kingR + i][kingC - i] == 'Q'&& over1!=1 && neg2!=1) {
                roadToCheck(m,board, 'Q', kingR, kingC, kingR + i, kingC - i);
                if (m->roadToCheck == 0)
                    isChe = 1;
            }
            if (board[kingR - i][kingC + i] == 'B'&& neg1!=1 && over2!=1) {
                roadToCheck(m,board, 'B', kingR, kingC, kingR - i, kingC + i);
                if (m->roadToCheck == 0)
                    isChe = 1;
            }
            if (board[kingR - i][kingC + i] == 'Q'&& neg1!=1 && over2!=1) {
                roadToCheck(m,board, 'Q', kingR, kingC, kingR - i, kingC + i);
                if (m->roadToCheck == 0)
                    isChe = 1;
            }
        }
    }
    m->isOwnCheck = isChe;
}
/**********************************************************
 * Function Name: commandIsLegal
 * Input: char board[][], char pgn[],int isWhiteTurn
 * Output: 1 or 0
 * Function Operation: the function return 1 if the command is legal, 0 if not
 *********************************************************/
void commandIsLegal (Move* m,char board[][SIZE], char pgn[],int isWhiteTurn){
    m->comIsLegal = 0;
    isWhite(m,board, pgn,isWhiteTurn);
    if (m->isWhite){
        findRowDest(m,board, pgn,isWhiteTurn);
        if (m->destRow != (SIZE+1)){
            findColDest(m,board, pgn,isWhiteTurn);
            if(m->destCol != '0') {
                isPromotion(m,board, pgn, isWhiteTurn);
                if (m->isPromotion == 1)
                    m->comIsLegal =1;
            }
        }
    }
}
/**********************************************************
 * Function Name: movementIsLegal
 * Input: char board[][], char pgn[],int isWhiteTurn
 * Output: 1 or 0
 * Function Operation: the function return 1 if the move is legal, 0 if not
 *********************************************************/
void movementIsLegal (Move* m,char board[][SIZE], char pgn[],int isWhiteTurn) {
    int baseR,desR,disR,disC;
    char baseC,desC,piece;
    baseR = m->srcRow;
    baseC = m->srcCol;
    desR = m->destRow;
    desC = m->destCol;
    piece = m->piece;
    disR = (baseR - desR);
    disR = abs(disR);
    if (baseC>=desC)
        disC = (baseC - desC);
    if (baseC<desC)
        disC = (desC - baseC);
    m->movementIsLeagal = 0;
    switch (piece){
        case 'P':{
            if (desC == baseC) {
                //classic move
                if ((desR < baseR) && (disR == 1))
                    m->movementIsLeagal = 1;
                //opening move
                if (baseR == (SIZE-2)) {
                    if ((desR < baseR) && (disR == 2)) {
                        if (board[baseR-1][desC-97]== ' ')
                            m->movementIsLeagal = 1;
                    }
                }
            }
                //hiting case
            else {
                isHit(m,board, pgn,isWhiteTurn);
                if (m->isHit){
                    if ((desR < baseR)&&(disC==1))
                        m->movementIsLeagal = 1;
                }
            }
            break;
        }
        case 'p':{
            if (desC == baseC) {
                //classic move
                if ((desR > baseR) && (disR == 1))
                    m->movementIsLeagal = 1;
                //opening move
                if (baseR == 1) {
                    if ((desR > baseR) && (disR == 2)){
                        if (board[baseR+1][desC-97]== ' ')
                            m->movementIsLeagal = 1;
                    }
                }
            }
                //hiting case
            else {
                isHit(m,board, pgn,isWhiteTurn);
                if (m->isHit){
                    if ((desR > baseR)&&(disC==1))
                        m->movementIsLeagal = 1;
                }
            }
            break;
        }
        case 'R':
        case 'r':{
            //straight line
            if ((disC == 0) || (disR == 0))
                m->movementIsLeagal = 1;
            break;
        }
        case 'N':
        case 'n':{
            if ((disC == 1) && (disR == 2))
                m->movementIsLeagal = 1;
            if ((disC == 2) && (disR == 1))
                m->movementIsLeagal = 1;
            break;
        }
        case 'B':
        case 'b':{
            // horizon line
            if (disC == disR)
                m->movementIsLeagal = 1;
            break;
        }
        case 'Q':
        case 'q':{
            //straight line
            if ((disR==0) || (disC==0))
                m->movementIsLeagal = 1;
            // horizon line
            if (disC == disR)
                m->movementIsLeagal = 1;
            break;
        }
        case 'K':
        case 'k':{
            if ((disC<2)&&(disR<2))
                m->movementIsLeagal = 1;
            break;
        }
    }
}
/**********************************************************
 * Function Name: moveIsLegal
 * Input: char board[][], char pgn[],int isWhiteTurn
 * Output: 1 or 0
 * Function Operation: the function return 1 if the move is legal physically, 0 if not
 *********************************************************/
void moveIsLegal (Move* m,char board[][SIZE], char pgn[],int isWhiteTurn){
    int baseR,desR,disC;
    char baseC,desC,piece;
    baseR = m->srcRow;
    baseC = m->srcCol;
    desR = m->destRow;
    desC = m->destCol;
    piece = m->piece;
    //convert char to int
    int baseCo = (baseC-97);
    int desCo = (desC-97);
    movementIsLegal(m,board, pgn,isWhiteTurn);
    int check1 = m->movementIsLeagal;
    roadIsClear(m,board, piece);
    int check2 = m->roadIsClear;
    isClear(m,board, pgn,isWhiteTurn);
    char check3 = m->isClear;
    int check = (check1 && check2);
    m->moveIsLegal = 0;
    if (check == 0)
        m->moveIsLegal = 0;
        // ch and che true
    else if ((check3 == '0'))
        m->moveIsLegal = 1;
        //block by same team
    else {
        if (isWhiteTurn) {
            //check if there is a 'hit' in the pgn
            isHit(m, board, pgn, isWhiteTurn);
            if ((m->isHit) && (islow(check3)))
                m->moveIsLegal = 1;
            else
                m->moveIsLegal = 0;
        }
        else if (isWhiteTurn == 0) {
            //check if there is a 'hit' in the pgn
            isHit(m, board, pgn, isWhiteTurn);
            if ((isUpper(check3)) && ((m->isHit)))
                m->moveIsLegal = 1;
            else
                m->moveIsLegal = 0;
        }
    }
}
/**********************************************************
 * Function Name: changeBoard
 * Input: char board[][], char pgn[],int isWhiteTurn
 * Output: 1 or 0
 * Function Operation: the function change the board according to pgn if possible,
 * and return 1. if not - send 0
 *********************************************************/
void changeBoard (Move* m,char board[][SIZE], char pgn[],int isWhiteTurn) {
    int baseR,desR,chessA,chessO;
    char baseC,desC,pro,temp;
    baseR = m->srcRow;
    baseC = m->srcCol;
    desR = m->destRow;
    desC = m->destCol;
    pro = m->promotion;
    //convert char to int
    int x = (baseC-97);
    int y = (desC-97);
    temp = board[desR][y];
    promotion(m,board, pgn,isWhiteTurn);
    if (m->isPromotion == 1 && m->promotion != '0') {
        board[desR][y] = m->promotion;
    }
    else board[desR][y] = board[baseR][x];
    board[baseR][x] = ' ';
    isChess(m,board, pgn, isWhiteTurn);
    chessA = m->isCheck;
    isOwnChess(m,board, isWhiteTurn);
    chessO = m->isOwnCheck;
    if ((chessA == 1) && (chessO == 0))
        m->change = 1;
        // arrange the board like before the move
    else {
        // promotion case
        if (m->isPromotion == 1 && m->promotion != '0'){
            if (isWhiteTurn)
                board[baseR][x] = 'P';
            else board [baseR][x] = 'p';
        }
        else board [baseR][x] = board[desR][y];
        board [desR][y] = temp;
        m->change = 0;
    }
}
/**********************************************************
 * Function Name: makeMove
 * Input: char board[][], char pgn[], int isWhiteTurn
 * Output: 1 - if the move is legal, 0 -if not
 * Function Operation: the function check if the move is legal,
 * if it is the function change the board array according to pgn,
 * if it's not, the function return 0
 *********************************************************/
int makeMove(char board[][SIZE], char pgn[], int isWhiteTurn) {
    Move m;
    int destR = -1, pieceR = -1, pg = 0;
    char piece, destC = '0', pieceC = '0';
    findRowDest(&m, board, pgn, isWhiteTurn);
    findColDest(&m, board, pgn, isWhiteTurn);
    while (pgn[pg] != 0) {
        //check if it's number
        if (pgn[pg] > 47 && pgn[pg] < 58) {
            if (destR != -1)
                pieceR = destR;
            destR = (pgn[pg] - 48);
        }
        if (pgn[pg] > 96 && pgn[pg] < 107) {
            if (destC != '0')
                pieceC = destC;
            destC = pgn[pg];
        }
        pg++;
    }
    if ((pieceR != -1) && (pieceC != '0')) {
        m.srcRow = (SIZE - pieceR);
        m.srcCol = pieceC;
        commandIsLegal(&m, board, pgn, isWhiteTurn);
        moveIsLegal(&m, board, pgn, isWhiteTurn);
        if (m.comIsLegal && m.moveIsLegal) {
            changeBoard(&m, board, pgn, isWhiteTurn);
            if (m.change)
                return 1;
        }
    }
    else if ((pieceR == -1) && (pieceC != '0')) {
        whatPiece(&m,board, pgn, isWhiteTurn);
        piece = m.piece;
        for (int i = 0; i < SIZE; i++) {
            if (board[i][pieceC-97] == piece) {
                m.srcRow = i;
                m.srcCol = pieceC;
                commandIsLegal(&m,board, pgn,isWhiteTurn);
                moveIsLegal(&m,board, pgn,isWhiteTurn);
                if (m.comIsLegal && m.moveIsLegal) {
                    changeBoard(&m,board, pgn, isWhiteTurn);
                    if (m.change)
                        return 1;
                }
            }
        }
    }
    else if ((pieceR != -1) && (pieceC == '0')) {
        whatPiece(&m,board, pgn, isWhiteTurn);
        piece = m.piece;
        for (int i = 0; i < SIZE; i++) {
            if (board[SIZE-pieceR][i] == piece) {
                m.srcRow = SIZE-pieceR;
                m.srcCol = (i+97);
                commandIsLegal(&m,board, pgn,isWhiteTurn);
                moveIsLegal(&m,board, pgn,isWhiteTurn);
                if (m.comIsLegal && m.moveIsLegal) {
                    changeBoard(&m,board, pgn, isWhiteTurn);
                    if (m.change)
                        return 1;
                }
            }
        }
    }
    else {
        whatPiece(&m,board, pgn, isWhiteTurn);
        piece = m.piece;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (board[i][j] == piece) {
                    m.srcRow = i;
                    m.srcCol = (j+97);
                    commandIsLegal(&m,board, pgn,isWhiteTurn);
                    moveIsLegal(&m,board, pgn,isWhiteTurn);
                    if (m.comIsLegal && m.moveIsLegal) {
                        changeBoard(&m,board, pgn, isWhiteTurn);
                        if (m.change)
                            return 1;
                    }
                }
            }
        }
    }
    return 0;
}
