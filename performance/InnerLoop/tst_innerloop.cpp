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
    void test_original();
    void test_tuned();
    void test_thread();
    void test_async();
private:
    int N;

};

InnerLoop::InnerLoop() :
    N(1e6)
{

}

InnerLoop::~InnerLoop()
{

}

void InnerLoop::test_original()
{
    Loops test(N);


    QBENCHMARK {
        test.original();
    }

}

void InnerLoop::test_tuned()
{
    Loops test(N);

    QBENCHMARK {
        test.tuned();
    }
}

void InnerLoop::test_thread()
{
    Loops test(N);

    QBENCHMARK {
        test.threaded();
    }
}

void InnerLoop::test_async()
{
    Loops test(N);

    QBENCHMARK {
        test.async();
    }
}
QTEST_APPLESS_MAIN(InnerLoop)

#include "tst_innerloop.moc"
