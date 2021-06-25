#include <QtTest>

// add necessary includes here
#include <iostream>


class strfmt : public QObject
{
    Q_OBJECT

public:
    strfmt();
    ~strfmt();

private slots:
    void test_case1();

};

strfmt::strfmt()
{

}

strfmt::~strfmt()
{

}

void strfmt::test_case1()
{

}

QTEST_APPLESS_MAIN(strfmt)

#include "tst_strfmt.moc"
