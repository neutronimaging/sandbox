#include <QtTest>
#include <algorithm>
#include <execution>
#include <vector>
// add necessary includes here

struct Sum
{
    Sum(): sum{0} { }
    void operator()(float n) { sum += n; }
    float sum;
};

class STLalg : public QObject
{
    Q_OBJECT

public:
    STLalg();
    ~STLalg();

private slots:
    void test_for_each();

};

STLalg::STLalg()
{

}

STLalg::~STLalg()
{

}

void STLalg::test_for_each()
{
    std::vector<float> data;
    data.resize(100);
    float x=0.0f;
    for (auto &d: data) {
        d=x++;
    }
    std::for_each(std::execution::par,data.begin(),data.end(),Sum());
}

QTEST_APPLESS_MAIN(STLalg)

#include "tst_stlalg.moc"
