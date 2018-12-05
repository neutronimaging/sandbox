#ifndef LOOPS_H
#define LOOPS_H


class Loops {

public:
    Loops(int N);
    ~Loops();

    void original();
    void tuned();
    void threaded();
    void async();
    void parallelSTL();

private:
 //   void orignalLoop(float *src, float * dest, float value, int N);

//    void tunedLoop(float *src, float * dest, float value, int N);

    void stlLoop(float *src, float * dest, float value, int N);

    void threadLoop(float *src, float * dest, float value, int N);

    void asyncLoop(float *src, float * dest, float value, int N);

    float * data;
    float * result;

    int nData;
};

#endif // LOOPS_H
