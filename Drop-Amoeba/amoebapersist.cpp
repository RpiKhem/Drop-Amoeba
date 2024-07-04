#include "amoebapersist.h"

AmoebaPersist::AmoebaPersist(QObject *parent) : QObject(parent){}

void AmoebaPersist::save(int n, int m, int nextPlayer, QVector<QVector<int> > board, QString name){
    QFile f(name + ".save");
    if (!f.open( QIODevice::WriteOnly | QIODevice::Text )) {
        return;
    }
    QTextStream stream(&f);
    stream << n << "\n";
    stream << m << "\n";
    stream << nextPlayer << "\n";
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            stream << board[i][j];
            if(j != m - 1) {
                stream << " ";
            }
        }
        if(i != n - 1) {
            stream << "\n";
        }
    }
    f.close();
}

bool AmoebaPersist::load(int &n, int &m, int &nextPlayer, QVector<QVector<int> > &board, QString name){
    QFile f(name);
    if (!f.open(QIODevice::ReadOnly)) {
        return false;
    }
    QVector<QString> lines;
    QTextStream inStream(&f);
    while(!inStream.atEnd()) {
        QString l = inStream.readLine();
        lines.append(l);
    }
    n = lines[0].toInt();
    m = lines[1].toInt();
    nextPlayer = lines[2].toInt();
    QVector<int> tmpSV;
    QVector<QVector<int>> tmpBV;
    lines.remove(0);
    lines.remove(0);
    lines.remove(0);
    for(int i = 0; i < lines.size(); i++) {
        for(QString q : lines[i].split(" ")) {
            tmpSV.append(q.toInt());
        }
        tmpBV.append(tmpSV);
        tmpSV.clear();
    }
    board = tmpBV;
    return true;
}

