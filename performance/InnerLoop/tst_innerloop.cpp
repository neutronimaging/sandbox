#include <QtTest>

// add necessary includes here
#include "loops.h"

class InnerLoop : public QObject
{
    Q_OBJECT

public:
    InnerLoop();
    ~InnerLoop();

private slots:
    void test_case1();
    void test_case2();
    void test_case3();
private:
    int N;

};

InnerLoop::InnerLoop() :
    N(1e7)
{

}

InnerLoop::~InnerLoop()
{

}

void InnerLoop::test_case1()
{
    Loops test(N);


    QBENCHMARK {
        test.original();
    }

}

void InnerLoop::test_case2()
{
    Loops test(N);

    QBENCHMARK {
        test.tuned();
    }
}

void InnerLoop::test_case3()
{
    Loops test(N);

    QBENCHMARK {
        test.threaded();
    }
}

QTEST_APPLESS_MAIN(InnerLoop)

#include "tst_innerloop.moc"
