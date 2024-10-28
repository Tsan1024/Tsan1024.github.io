#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <cstring>

#define SHM_SIZE 1024

int main(int argc, char* argv[]) {
    int shmid;
    char *shmaddr;

    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <shared_memory_id>" << std::endl;
        return 1;
    }

    // 获取共享内存ID
    shmid = std::stoi(argv[1]);

    // 连接到共享内存
    shmaddr = static_cast<char*>(shmat(shmid, nullptr, 0));
    if (shmaddr == (char*)-1) {
        perror("shmat");
        return 1;
    }

    // 从共享内存中读取数据并打印
    std::cout << "Message from parent process: " << shmaddr << std::endl;

    // 更新共享内存
    strncpy(shmaddr, "Updated message", strlen("Updated message") + 1); 
    
    // 分离共享内存
    shmdt(shmaddr);

    return 0;
}
