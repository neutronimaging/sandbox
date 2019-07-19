#include <QtTest>

// add necessary includes here

class STLalg : public QObject
{
    Q_OBJECT

public:
    STLalg();
    ~STLalg();

private slots:
    void test_case1();

};

STLalg::STLalg()
{

}

STLalg::~STLalg()
{

}

void STLalg::test_case1()
{

}

QTEST_APPLESS_MAIN(STLalg)

#include "tst_stlalg.moc"
