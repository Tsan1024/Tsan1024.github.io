#include <iostream>
#include <unistd.h>

int main() {
    int pipefd[2];
    pid_t pid;
    char buffer[20];

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { // 子进程
        std::cout << "child: " << pid << std::endl;
        close(pipefd[1]); // 关闭写端
        read(pipefd[0], buffer, sizeof(buffer));
        std::cout << "Child received: " << buffer << std::endl;
        close(pipefd[0]);
    } else { // 父进程
        std::cout << "father: " << pid << std::endl;
        close(pipefd[0]); // 关闭读端
        write(pipefd[1], "Hello, world!", 14);
        close(pipefd[1]);
        wait(NULL); // 等待子进程结束
    }

    return 0;
}
