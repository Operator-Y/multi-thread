#include <thread>
#include <iostream>

void func(int val)
{
    while(true)
    {
        std::cout<< "Hello World"<< std::endl;
        std::this_thread::sleep_for(std::chrono::microseconds(1000));
        std::this_thread.get_id();
    }
}

int main(int argc, char **agrv)
{
    int val = 0;
    //创建线程 thread_func 
    std::thread thread_func(func, val);
    thread_func.detach(); // 与主线程分离，注意传参内存释放
    thread_func.join();   // 主线程等待子线程运行结束
    thread_func.get_id(); // 获取线程id
    thread_func.hardware_concurrency() //获取线程最大并发数
    auto handle = thread_func.native_handle() // 获取线程的句柄
    //while(true)
    //{
    //    std::cout<<"Main"<<std::endl;
    //    std::this_thread::sleep_for(std::chrono::microseconds(1000));
    //}
    return 0;
}

