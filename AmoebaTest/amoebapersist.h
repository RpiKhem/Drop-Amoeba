#ifndef AMOEBAPERSIST_H
#define AMOEBAPERSIST_H

#include <QObject>
#include <QFile>
#include <QTextStream>

class AmoebaPersist : public QObject
{
    Q_OBJECT
public:
    explicit AmoebaPersist(QObject *parent = nullptr);
    void save(int n, int m, int next, QVector<QVector<int>> board);
    bool load(int &n, int &m, int &next, QVector<QVector<int>> &board);
signals:


};

#endif // AMOEBAPERSIST_H
