#include "amoebamodel.h"

AmoebaModel::AmoebaModel(QObject *parent) : QObject(parent){
    s = new AmoebaPersist();
}

void AmoebaModel::createBoard(){
    board.clear();
    for(int i = 0; i < n; i++){
        QVector<int> tempV;
        for(int j = 0; j < m; j++){
            tempV.append(0);
        }
        board.append(tempV);
        tempV.clear();
    }
}

void AmoebaModel::putIcon(int x){
    bool possible = false;
    int row;
    for(int i = n-1; i >= 0; i--){
        if(board[i][x] == 0){
            possible = true;
            board[i][x] = next;
            row = i;
            break;
        }
    }
    if(!possible){
        return;
    }
    emit(updateBoard(row, x, next));
    if(next == 1){
        next = 2;
    }
    else {
        next = 1;
    }
    int win = winCheck();
    if(win){
        emit(gameOver(win));
    }
}

int AmoebaModel::winCheck(){
    int HOcounter = 0;
    int HXcounter = 0;
    int VOcounter = 0;
    int VXcounter = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(j == 0){
                HOcounter++;
                HXcounter++;
            }
            else{

                if(board[i][j] != 0 && board[i][j] == board[i][j-1] && board[i][j] == 1){
                    HOcounter++;
                    if(HOcounter == 4){
                        return board[i][j];
                    }
                    HXcounter = 1;

                }
                else if(board[i][j] != 0 && board[i][j] == board[i][j-1] && board[i][j] == 2){
                    HXcounter++;
                    if(HXcounter == 4){
                        return board[i][j];
                    }
                    HOcounter = 1;
                }
                else{

                }
            }

        }
        HXcounter = 0;
        HOcounter = 0;
    }
    for(int j = 0; j < m; j++){
        for(int i = 0; i < n; i++){
            if(i == 0){
                VOcounter++;
                VXcounter++;
            }
            else{
                if(board[i][j] != 0 && board[i][j] == board[i-1][j] && board[i][j] == 1){
                    VOcounter++;
                    if(VOcounter == 4){
                        return board[i][j];
                    }
                    VXcounter = 1;
                }
                else if(board[i][j] != 0 && board[i][j] == board[i-1][j] && board[i][j] == 2){
                    VXcounter++;
                    if(VXcounter == 4){
                        return board[i][j];
                    }
                    VOcounter = 1;
                }
                else{
                }
            }
        }
        VXcounter = 0;
        VOcounter = 0;
    }
    for(int i = 0; i <= n-4; i++){
        for(int j = 0; j <= m-4; j++){
            if(board[i+1][j+1] == 1 && board[i+2][j+2] == 1 && board[i+3][j+3] == 1 && board[i][j] == 1){
                return board[i][j];
            }
            if(board[i+1][j+1] == 2 && board[i+2][j+2] == 2 && board[i+3][j+3] == 2 && board[i][j] == 2){
                return board[i][j];
            }
        }
    }
    for(int i = 0; i <= n-4; i++){
        for(int j = 3; j < m; j++){
            if(board[i+1][j-1] == 1 && board[i+2][j-2] == 1 && board[i+3][j-3] == 1 && board[i][j] == 1){
                return board[i][j];
            }
            if(board[i+1][j-1] == 2 && board[i+2][j-2] == 2 && board[i+3][j-3] == 2 && board[i][j] == 2){
                return board[i][j];
            }
        }
    }
    int flag = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(board[i][j] == 0){
                flag++;
            }
        }
    }
    if(flag == 0){
        return 3;
    }

            return 0;
}

void AmoebaModel::save(QString name){
    s->save(n,m,next,board, name);
}

void AmoebaModel::load(QString name){
    QVector<QVector<int>> tmp;
    s->load(n,m,next,tmp, name);
    createBoard();
    board = tmp;
}
