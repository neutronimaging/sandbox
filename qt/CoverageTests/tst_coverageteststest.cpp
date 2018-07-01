#include <QString>
#include <QtTest>

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
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(CoverageTestsTest)

#include "tst_coverageteststest.moc"
