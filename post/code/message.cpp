#include<stdio.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/msg.h>

#define KEY 0x9999

typedef struct{
    long msgType;
    char data[80];
}Msg;

// Msg可以随意定义但需要含有一个消息类型type，而且还必须是结构体的第一个成员。而结构体中的其他成员都被认为是要发送的消息体数据。

int main(void){
    pid_t pid;
    int msgid;
    int i = 0;
    int ret;
    Msg msg;

    pid = fork();
    if(pid == 0){ 
        msgid = msgget(KEY, IPC_CREAT | 0666);
        if(msgid == -1){
            perror("");
            return -1; 
        }   
        while(1){
            msg.msgType = 1;
            sprintf(msg.data, "Hello I am sender %d", i);
            msgsnd(msgid, &msg, sizeof(Msg) - sizeof(long), 0);
            i++;
            sleep(1);
        }
    }else if(pid > 0){
        msgid = msgget(KEY, IPC_CREAT | 0666);
        if(msgid == -1){
            perror("");
            return -1;
        }
        while(1){
            ret = msgrcv(msgid, &msg, sizeof(Msg) - sizeof(long), 1, 0);
            if(ret < 0){
                perror("");
                return -1;
            }
            printf("Father RCV :%s\n", msg.data);
        }


    }else{
        perror("");
        return -1;
    }   

    return 0;
}