// reader.cpp
#include <iostream>
#include <fcntl.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <unistd.h>

const char* SHM_NAME = "/shared_memory";
const char* SEM_NAME = "/semaphore";

struct SharedData {
    char message[256];
};

int main() {
    int shm_fd = shm_open(SHM_NAME, O_RDWR, 0666);
    SharedData* shared_data = (SharedData*)mmap(0, sizeof(SharedData), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    sem_t* sem = sem_open(SEM_NAME, 0);

    sem_wait(sem);  // Wait for semaphore
    std::cout << "Message from writer: " << shared_data->message << std::endl;
    sem_post(sem);  // Signal semaphore

    munmap(shared_data, sizeof(SharedData));
    close(shm_fd);
    sem_close(sem);

    return 0;
}