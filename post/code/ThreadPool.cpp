// main.cpp
#include <iostream>
#include <vector>
#include "ThreadPool.h"

int main() {
    // 创建线程池，包含4个线程
    ThreadPool pool(4);

    // 添加任务到线程池
    std::vector<std::future<int>> results;
    for(int i = 0; i < 8; ++i) {
        results.emplace_back(
            pool.enqueue([i] {
                std::cout << "Task " << i << " is being processed by thread " << std::this_thread::get_id() << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
                return i*i;
            })
        );
    }

    // 获取任务结果
    for(auto && result: results)
        std::cout << "Result: " << result.get() << std::endl;

    return 0;
}
