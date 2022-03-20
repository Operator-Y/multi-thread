/*
 * 文件为 互斥量/原子变量的使用
 * std::mutex mtx 互斥量可用于进程间临街区代码的互斥访问
 *                1.但由于mtx.lock()和mtx.unlock()之间代码可能出现异常
 *                互斥量mtx上锁后，没有解锁，造成死锁现象，从而引进类模版
 * lock_guard<std::mutex> lock(mtx) 功能类似于
 *                class A
 *                {
 *                  A(std::mutex& mtx) {mtx.lock();}
 *                  ~A() {mtx.unlock();}
 *                }
 *                构造函数中上锁，析构函数中解锁
 *                RAII(Resource Acquisition Is Initialization)
 *                资源获取即初始化
 * unique_lock<std::mutex> lock(mtx) 相比于lock_guard有更多的类方法，
 *                可以进行unlock()等操作
 * atomic :原子变量，可以不用加锁，对该类型变量的操作都为原子操作
 *         实现方式1: 类模板内部上锁，解锁
 *         实现方式2: cpu内部加锁解锁
 * std::scoped_lock 等操作
 * */
#include <thread>
#include <mutex>
#include <iostream>

int global_value = 0;
std::mutex mtx1;
std::mutex mtx2;
std::atomic<int> global_value_at = 0; //对该变量的操作不需要上锁
void task1()
{
    for (int i = 0; i < 1000000; i++)
    {
        std::lock_guard<std::mutex> lock1(mtx1);
        std::lock_guard<std::mutex> lock2(mtx2);
        global_value++;
        global_value--;
        //1. call_function() throw
        //2. if (判断)  return
        //3. 多把锁的竞争 造成死锁 解决 std::lock(mtx1, mtx2);
        //以上三种情况的解决办法使用类似于智能指针的类模板
        //lock_gruad()
    }
}
void task2()
{
    for (int i = 0; i < 1000000; i++)
    {
        mtx1.lock();
        mtx2.lock();
        global_value++;
        global_value--;
        mtx1.unlock();
        mtx2.unlock();
    }
}
int main(int argc, char** argv)
{
    std::thread t1(task1);
    std::thread t2(task2);
    t1.join();
    t2.join();
    std::cout << "current value is :" << global_value << std::endl;
    return 0;
}

