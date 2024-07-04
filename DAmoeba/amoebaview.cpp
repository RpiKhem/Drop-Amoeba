#include "amoebaview.h"

AmobaWidget::AmobaWidget(QWidget *parent)
    : QWidget(parent)
{
    //init variables, layouts
    buttonContainer = new QHBoxLayout();
    mainLayout = new QVBoxLayout();
    boardLayout = new QGridLayout();
    menuContainer = new QHBoxLayout();
    sizeContainer = new QHBoxLayout();
    saveGame = new QPushButton("Save");
    loadGame = new QPushButton("Load");
    victory = new QMessageBox();

    //new game buttons connects
    small = new QPushButton("New: 8 x 5");
    connect(small, SIGNAL(clicked()), this, SLOT(newGameSmall()));
    medium = new QPushButton("New: 10 x 8");
    connect(medium, SIGNAL(clicked()), this, SLOT(newGameMedium()));
    large = new QPushButton("New: 12 x 7");
    connect(large, SIGNAL(clicked()), this, SLOT(newGameLarge()));

    //add to layout

    sizeContainer->addWidget(small);
    sizeContainer->addWidget(medium);
    sizeContainer->addWidget(large);

    menuContainer->addWidget(saveGame);
    menuContainer->addWidget(loadGame);

    mainLayout->addLayout(buttonContainer);
    mainLayout->addLayout(boardLayout);
    mainLayout->addLayout(sizeContainer);
    mainLayout->addLayout(menuContainer);

    setLayout(mainLayout);

    //setup and start a game with small board
    setWindowTitle("Drop amoeba game");
    model = new AmoebaModel();
    model->setN(8);
    model->setM(5);
    model->createBoard();
    drawBoard();
    connect(model, SIGNAL(updateBoard(int, int, int)), this, SLOT(newRound(int, int, int)));
    connect(model, SIGNAL(gameOver(int)), this, SLOT(endGame(int)));
    connect(saveGame, SIGNAL(clicked()), this, SLOT(save()));
    connect(loadGame, SIGNAL(clicked()), this, SLOT(load()));
}

AmobaWidget::~AmobaWidget()
{
}

void AmobaWidget::drawBoard(){
    //get size
    int n = model->getN();
    int m = model->getM();

    //clear board and buttons
    if (boardLayout->rowCount() != 0 || boardLayout->columnCount() != 0) {
        while ( QLayoutItem* item = boardLayout->takeAt( 0 ) ) {
                delete item->widget();
                delete item;
            }
    }
    if (buttonContainer->count() != 0) {
        while ( QLayoutItem* item = buttonContainer->takeAt( 0 ) ) {
                delete item->widget();
                delete item;
            }
    }

    //draw new
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if(i == 0){
                QPushButton* controlButton = new QPushButton("Drop");
                connect(controlButton, SIGNAL(clicked()), this, SLOT(placeIcon()));
                buttonContainer->addWidget(controlButton);
            }
            QLineEdit* field = new QLineEdit();
            if(model->getBoard()[i][j] == 1){
                field->setText("O");
            }
            else if (model->getBoard()[i][j] == 2){
                field->setText("X");
            }

            field->setReadOnly(true);
            field->setAlignment(Qt::AlignCenter);
            field->setFixedSize(40,40);
            boardLayout->addWidget(field, i, j);

        }
    }
}

void AmobaWidget::placeIcon(){
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    int col = buttonContainer->indexOf(btn);
    model->putIcon(col);
}

void AmobaWidget::newRound(int i, int j, int player){
    QLineEdit* field =qobject_cast<QLineEdit*> (boardLayout->itemAtPosition(i,j)->widget());
    if(player == 1){
        field->setText("O");
    }
    else{
        field->setText("X");
    }
}

void AmobaWidget::newGameSmall(){
    model->setM(5);
    model->setN(8);
    model->createBoard();
    drawBoard();
}

void AmobaWidget::newGameMedium(){
    model->setM(6);
    model->setN(10);
    model->createBoard();
    drawBoard();
}

void AmobaWidget::newGameLarge(){
    model->setM(7);
    model->setN(12);
    model->createBoard();
    drawBoard();
}

void AmobaWidget::endGame(int player){
    QString text;
    if(player == 1){
        text = "O won the game!";
    }
    else if(player == 2){
        text = "X won the game!";
    }
    else{
        text = "Game is draw!";
    }
    victory->setWindowTitle("Game result");
    victory->setText(text);
    int c = victory->exec();
    if (c){newGameSmall();}
}

void AmobaWidget::save(){
    QString saveName = QInputDialog::getText(this, tr("Save"), tr("Save file name"));
    model->save(saveName);
}

void AmobaWidget::load(){
    QString loadName = QFileDialog::getOpenFileName(
        this, "Load", ".", "Save files (*.save)");
    if (!loadName.isEmpty()){
        model->load(loadName);
        drawBoard();
    }

}
