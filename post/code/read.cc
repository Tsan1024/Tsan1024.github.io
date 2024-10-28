// reader.cpp
#include <iostream>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    const char *fifo_path = "/tmp/my_fifo";
    
    // 创建命名管道（如果已经存在则不会重新创建）
    if (mkfifo(fifo_path, 0666) == -1) {
        perror("mkfifo");
        return 1;
    }

    // 打开命名管道
    int fd = open(fifo_path, O_RDONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    // 从管道读取消息
    char buffer[128];
    if (read(fd, buffer, sizeof(buffer)) == -1) {
        perror("read");
        close(fd);
        return 1;
    }

    // 输出读取的消息
    std::cout << "Reader received: " << buffer << std::endl;

    // 关闭管道
    close(fd);

    return 0;
}
