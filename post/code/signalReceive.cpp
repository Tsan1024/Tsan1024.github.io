#include <iostream>
#include <csignal>
#include <unistd.h>

// 信号处理程序
void handle_sigusr1(int sig) {
    std::cout << "Received SIGUSR1 signal. " << sig << std::endl;
}

int main() {
    // 设置信号处理程序
    if (signal(SIGUSR1, handle_sigusr1) == SIG_ERR) {
        perror("Error setting signal handler");
        return 1;
    }

    // 使进程保持运行，以等待信号
    while (true) {
        std::cout << "Waiting for signal..." << std::endl;
        sleep(5);
    }

    return 0;
}
