#include <QString>
#include <QtTest>

#include <coveragedummies.h>
#include <QDebug>

class CoverageTestsTest : public QObject
{
    Q_OBJECT

public:
    CoverageTestsTest();

private Q_SLOTS:
    void testCase1();
};

CoverageTestsTest::CoverageTestsTest()
{
}

void CoverageTestsTest::testCase1()
{
    CoverageDummies a;

    QVERIFY(a.get()==0);
    a.set(12);
    QVERIFY(a.get()==12);
    QVERIFY(a.decade()==10);

    a.set(1);
    QVERIFY(a.decade()==0);
    a.set(24);
    QVERIFY(a.decade()==20);

    a.set(35);
    QVERIFY(a.decade()==30);

    a.set(305);
    QVERIFY(a.decade()==30);

    a.set(-20);
    QVERIFY(a.decade()==-1);


}

QTEST_APPLESS_MAIN(CoverageTestsTest)

#include "tst_coverageteststest.moc"
