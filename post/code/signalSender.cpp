#include <iostream>
#include <csignal>
#include <unistd.h>

int main() {
    pid_t pid;
    std::cout << "Enter PID of the process to send SIGUSR1: ";
    std::cin >> pid;

    // 发送 SIGUSR1 信号
    if (kill(pid, SIGUSR1) == 0) {
        std::cout << "Signal sent successfully." << std::endl;
    } else {
        perror("Error sending signal");
    }

    return 0;
}
