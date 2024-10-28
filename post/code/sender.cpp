// sender.cpp
#include <iostream>
#include <mqueue.h>
#include <cstring>
#include <cstdlib>
#include <unistd.h>

int main() {
    const char* queue_name = "/my_message_queue";
    mqd_t mq;
    struct mq_attr attr;
    const char* message = "Hello from sender!";
    unsigned int priority = 1;

    // 设置消息队列属性
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = 256;
    attr.mq_curmsgs = 0;

    // 创建或打开消息队列
    mq = mq_open(queue_name, O_CREAT | O_WRONLY, 0644, &attr);
    if (mq == (mqd_t) -1) {
        perror("mq_open");
        exit(1);
    }

    // 发送消息到消息队列
    if (mq_send(mq, message, strlen(message) + 1, priority) == -1) {
        perror("mq_send");
        exit(1);
    }

    std::cout << "Message sent: " << message << std::endl;

    // 关闭消息队列
    mq_close(mq);

    return 0;
}
