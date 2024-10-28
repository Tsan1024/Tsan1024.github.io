// writer.cpp
#include <iostream>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstring>

int main() {
    const char *fifo_path = "/tmp/my_fifo";
    
    // 创建命名管道（如果已经存在则不会重新创建）mkfifo create fifo
    // if (mkfifo(fifo_path, 0666) == -1) {
    //     perror("mkfifo");
    //     return 1;
    // }

    // 打开命名管道
    int fd = open(fifo_path, O_WRONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    // 写入消息到管道
    const char *message = "Hello from writer!";
    if (write(fd, message, strlen(message) + 1) == -1) {
        perror("write");
        close(fd);
        return 1;
    }

    // 关闭管道
    close(fd);

    return 0;
}
