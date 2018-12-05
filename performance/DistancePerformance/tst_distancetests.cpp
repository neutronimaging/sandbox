#include <QtTest>
#include <QDebug>
// add necessary includes here
#include "position.h"

class DistanceTests : public QObject
{
    Q_OBJECT

public:
    DistanceTests();
    ~DistanceTests();

private slots:
    void test_case_orig();
    void test_case_sse();
    void test_values();

private:
    Position posA[10000];
    Position posB[10000];

};

DistanceTests::DistanceTests()
{
    for (int i=0; i<10000; ++i) {
        for (int j=0; j<3; ++j)
        {
            posA[i].pos.v[j]=std::rand()%1000;
            posB[i].pos.v[j]=std::rand()%1000;
        }

    }
}

DistanceTests::~DistanceTests()
{

}

void DistanceTests::test_case_orig()
{
    Position a(1.0f,2.0f,3.0f);
    Position b(5.0f,4.0f,3.0f);
    QBENCHMARK
    {
        for (int i=0; i<10000; ++i) {

            float d=dist(posA[i],posB[i]);
        }
    }
}

void DistanceTests::test_case_sse()
{
    Position a(1.0f,2.0f,3.0f);
    Position b(5.0f,4.0f,3.0f);
    QBENCHMARK
    {
        for (int i=0; i<10000; ++i) {

            float d=distSSE(posA[i],posA[i]);
        }
    }

}

void DistanceTests::test_values()
{
    Position a(1.0f,2.0f,3.0f);
    Position b(5.0f,4.0f,3.0f);
    float d=dist(a,b);
//    qDebug() <<d;
    float dsse=dist(a,b);
//    qDebug() <<dsse;
    QCOMPARE(d,dsse);
}

QTEST_APPLESS_MAIN(DistanceTests)

#include "tst_distancetests.moc"
