#ifndef AMOEBAVIEW_H
#define AMOEBAVIEW_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include "amoebamodel.h"
#include <QLineEdit>
#include <QFont>
#include <QMessageBox>
#include <QInputDialog>
#include <QFileDialog>

class AmobaWidget : public QWidget
{
    Q_OBJECT

public:
    AmobaWidget(QWidget *parent = nullptr);
    ~AmobaWidget();
private:
    AmoebaModel* model;
    QHBoxLayout* buttonContainer;
    QVBoxLayout* mainLayout;
    QGridLayout* boardLayout;
    QHBoxLayout* menuContainer;
    QPushButton* saveGame;
    QPushButton* loadGame;
    QHBoxLayout* sizeContainer;
    QMessageBox* victory;
    QPushButton* small;
    QPushButton* medium;
    QPushButton* large;
    void drawBoard();

private slots:
    void placeIcon();
    void newRound(int i, int j, int player);
    void newGameSmall();
    void newGameMedium();
    void newGameLarge();
    void endGame(int player);
    void save();
    void load();
};
#endif // AMOEBAVIEW_H
