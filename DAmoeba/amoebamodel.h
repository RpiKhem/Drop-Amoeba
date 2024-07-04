#ifndef AMOEBAMODEL_H
#define AMOEBAMODEL_H

#include <QVector>
#include <QObject>
#include <QtDebug>
#include "amoebapersist.h"

class AmoebaModel : public QObject
{
    Q_OBJECT
public:
    explicit AmoebaModel(QObject *parent = nullptr);
    void setN(int n){this->n = n;}
    void setM(int m){this->m = m;}
    int getN(){return this->n;}
    int getM(){return this->m;}
    int getNext(){return this->next;}
    QVector<QVector<int>> getBoard(){return this->board;}
    void createBoard();
    void putIcon(int x);
    int winCheck();
    void newGame();
    void save(QString name);
    void load(QString name);
private:
    QVector<QVector<int>> board;
    int n;
    int m;
    int next = 1;
    AmoebaPersist* s;
signals:
    void updateBoard(int i, int j, int player);
    void gameOver(int player);
};

#endif // AMOEBAMODEL_H
