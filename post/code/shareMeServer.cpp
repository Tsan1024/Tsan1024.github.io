#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <cstring>

#define SHM_SIZE 1024

int main() {
    int shmid;
    char *shmaddr;

    // 创建共享内存段
    shmid = shmget(IPC_PRIVATE, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        return 1;
    }

    // 将共享内存段连接到当前进程的地址空间
    shmaddr = static_cast<char*>(shmat(shmid, nullptr, 0));
    if (shmaddr == (char*)-1) {
        perror("shmat");
        return 1;
    }

    // 写入数据到共享内存
    strncpy(shmaddr, "Hello from parent process", SHM_SIZE);

    // 分离共享内存，分离后当前进程则无法再修改该共享内存段
    shmdt(shmaddr);
    // strncpy(shmaddr, "Updated message", strlen("Updated message") + 1); 
    // 打印共享内存ID以便子进程使用
    std::cout << "Shared memory ID: " << shmid << std::endl;

    return 0;
}
