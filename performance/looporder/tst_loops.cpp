#include <QtTest>

// add necessary includes here

#include "looper.h"

class loops : public QObject
{
    Q_OBJECT

public:
    loops();
    ~loops();

private slots:
    void test_case1();

    void test_case2();

    void test_case3();

    void test_case4();

};

loops::loops()
{

}

loops::~loops()
{

}

void loops::test_case1()
{
    looper test;

    test.fillImageA(2048UL);

    QBENCHMARK {
        test.loopxyOp();
    }

}

void loops::test_case2()
{
    looper test;

    test.fillImageA(2048UL);

    QBENCHMARK {
        test.loopyxOp();
    }
}

void loops::test_case3()
{
    looper test;

    test.fillImageA(2048UL);

    QBENCHMARK {
        test.loopyxPtr();
    }
}

void loops::test_case4()
{
    looper test;

    test.fillImageA(2048UL);

    QBENCHMARK {
        test.loopyxPtr2();
    }
}
QTEST_APPLESS_MAIN(loops)

#include "tst_loops.moc"
