#include <QtTest>
#include <QCoreApplication>
#include "amoebamodel.h"

// add necessary includes here

class test : public QObject
{
    Q_OBJECT

public:
    test();
    ~test();

private:
    AmoebaModel* m;

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_case1();
    void test_case2();
    void test_case3();
    void test_case4();
    void test_case5();
    void test_case6();
};

test::test()
{

}

test::~test()
{

}

void test::initTestCase(){
    m = new AmoebaModel();
    m->setN(8);
    m->setM(5);
}

void test::cleanupTestCase()
{

}

void test::test_case1(){
    initTestCase();
    m->createBoard();
    QCOMPARE(m->getNext(),1);
    QCOMPARE(m->getM(), 5);
    QCOMPARE(m->getN(), 8);
    QVector<QVector<int>> tmp;
    tmp = m->getBoard();
    qInfo()<<tmp;
    QCOMPARE(tmp[0][0],0);
    QCOMPARE(tmp[7][4],0);
}

void test::test_case2(){
    initTestCase();
    m->createBoard();
    m->putIcon(0);
    QVector<QVector<int>> tmp;
    tmp = m->getBoard();
    QCOMPARE(tmp[7][0],1);
    m->putIcon(2);
    tmp = m->getBoard();
    QCOMPARE(tmp[7][2],2);
}

void test::test_case3(){
    initTestCase();
    m->createBoard();
    m->putIcon(0);
    QVector<QVector<int>> tmp;
    m->putIcon(2);
    m->putIcon(0);
    m->putIcon(2);
    m->putIcon(0);
    m->putIcon(2);
    m->putIcon(0);
    QCOMPARE(m->winCheck(),1);
}

void test::test_case4(){
    initTestCase();
    m->createBoard();
    m->putIcon(0);
    QVector<QVector<int>> tmp;
    m->putIcon(2);
    m->putIcon(1);
    m->putIcon(2);
    m->putIcon(0);
    m->putIcon(2);
    m->putIcon(0);
    m->putIcon(2);
    QCOMPARE(m->winCheck(),2);
}

void test::test_case5(){
    initTestCase();
    m->createBoard();
    m->putIcon(0);
    QVector<QVector<int>> tmp;
    m->putIcon(2);
    m->putIcon(1);
    m->putIcon(2);
    QCOMPARE(m->winCheck(),0);
}

void test::test_case6(){
    initTestCase();
    m->createBoard();
    m->setM(3);
    m->setN(3);
    m->putIcon(0);
    m->putIcon(0);
    m->putIcon(0);
    m->putIcon(1);
    m->putIcon(1);
    m->putIcon(1);
    m->putIcon(2);
    m->putIcon(2);
    m->putIcon(2);
    QCOMPARE(m->winCheck(),3);
}

QTEST_MAIN(test)

#include "tst_test.moc"
