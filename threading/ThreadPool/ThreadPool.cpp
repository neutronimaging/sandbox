#include <iostream>
#include <sstream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <functional>

#include <logging/logger.h>

std::mutex print_mutex;

void Print(std::string str, std::mutex &m)
{
    std::unique_lock<std::mutex> lock(m);
    std::cout<<str;
}

class ThreadPool 
{
    kipl::logging::Logger logger;
public:
    ThreadPool(size_t numThreads) : 
        logger("ThreadPool"),
        stop(false) {
        std::ostringstream msg_global;
        msg_global<<"Starting thread pool with "<<numThreads<<" threads";
        logger.verbose(msg_global.str());

        for (size_t i = 0; i < numThreads; ++i)
        {
            threads.emplace_back(
                [this,i] {
                    std::ostringstream msg;

                    for (;;) 
                    {
                        std::function<void()> task;

                        {
                            std::unique_lock<std::mutex> lock(this->queue_mutex);
                            this->condition.wait(lock,
                                                 [this] { return this->stop || !this->tasks.empty(); });
                            if (this->stop && this->tasks.empty())
                                return;
                            task = std::move(this->tasks.front());
                            this->tasks.pop();
                        }

                        msg.str("");
                        msg<<"Thread "<<i<<" starts new task";
                        logger.verbose(msg.str());
                        
                        task();
                    }
                }
            );
        }
    }

    template<class F>
    void enqueue(F &&f) {
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            tasks.emplace(std::forward<F>(f));
        }
        condition.notify_one();
    }


    ~ThreadPool() {
        logger.verbose("Tearing down the thread pool");
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            stop = true;
        }
        condition.notify_all();
        for (std::thread &thread : threads)
            thread.join();
    }

private:
    std::vector<std::thread> threads;
    std::queue<std::function<void()>> tasks;

    std::mutex queue_mutex;

    std::condition_variable condition;
    bool stop;
};

// Example usage:
int main(int argc, char *argv[]) 
{
    kipl::logging::Logger::set_loglevel();
    size_t N=0;
    if (argc<2)
        N=std::thread::hardware_concurrency();
    else 
        N=std::stol(argv[1]);

    ThreadPool pool(N);

    std::ostringstream msg;
    for (int i = 0; i < 200; ++i) {
        int b = i*2;
        pool.enqueue([i,b] {
            float sum=0.0f;

            for (size_t cnt=0; cnt<100000000; ++cnt)
                sum+=sqrt(static_cast<float>(cnt));
        });
    }
}
