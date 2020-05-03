#include <QtTest>
#include <iostream>
#include <armadillo.h>
// add necessary includes here

using namespace std;
using namespace arma;


class ArmadilloTests : public QObject
{
    Q_OBJECT

public:
    ArmadilloTests();
    ~ArmadilloTests();

private slots:
    void test_case1();
    void test_case2();

};

ArmadilloTests::ArmadilloTests()
{

}

ArmadilloTests::~ArmadilloTests()
{

}

void ArmadilloTests::test_case1()
{
  mat A = randu<mat>(4,5);
  mat B = randu<mat>(4,5);

  cout << A*B.t() << endl;

}

void ArmadilloTests::test_case2()
{
    int polyOrder = 2;
    int windowLength = 5;
    int deriv = 0;
    double delta = 1.0;
    int pos=2;

    mat A(polyOrder+1,windowLength) ;
    float x=-pos;
    for (int i=0; i<windowLength; ++i, ++x)
    {
        for (int order = 0 ; order<=polyOrder; ++order)
        {
            A(order,i)=std::pow(x,order);
        }
    }

    vec y(polyOrder+1);

    y.fill(0.0);
    y(deriv)=1.0 / std::pow(delta,deriv);

    vec c=solve(A,y);

}

QTEST_APPLESS_MAIN(ArmadilloTests)

#include "tst_armadillotests.moc"
