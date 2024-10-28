#include <iostream>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <unordered_map>

class EventHandler {
public:
    virtual void handle_event(int fd) = 0;
    virtual ~EventHandler() = default;
};

class ReadEventHandler : public EventHandler {
public:
    void handle_event(int fd) override {
        char buffer[1024];
        ssize_t n = read(fd, buffer, sizeof(buffer) - 1);
        if (n > 0) {
            buffer[n] = '\0';
            std::cout << "Received: " << buffer << std::endl;
        } else if (n == 0) {
            std::cout << "Client disconnected." << std::endl;
            close(fd);
        } else {
            perror("read");
        }
    }
};

class Reactor {
public:
    void register_handler(int fd, EventHandler* handler) {
        handlers[fd] = handler;
        if (fd > max_fd) {
            max_fd = fd;
        }
    }

    void remove_handler(int fd) {
        handlers.erase(fd);
    }

    void event_loop() {
        fd_set read_fds;
        while (true) {
            FD_ZERO(&read_fds);
            for (const auto& [fd, handler] : handlers) {
                FD_SET(fd, &read_fds);
            }

            int activity = select(max_fd + 1, &read_fds, nullptr, nullptr, nullptr);
            if (activity < 0) {
                perror("select");
                break;
            }

            for (int fd = 0; fd <= max_fd; ++fd) {
                if (FD_ISSET(fd, &read_fds)) {
                    if (handlers.find(fd) != handlers.end()) {
                        handlers[fd]->handle_event(fd);
                    }
                }
            }
        }
    }

private:
    std::unordered_map<int, EventHandler*> handlers;
    int max_fd = 0;
};

int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("socket");
        return 1;
    }

    struct sockaddr_in server_addr;
    std::memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("bind");
        close(server_fd);
        return 1;
    }

    if (listen(server_fd, 10) == -1) {
        perror("listen");
        close(server_fd);
        return 1;
    }

    Reactor reactor;
    ReadEventHandler read_handler;

    reactor.register_handler(server_fd, new ReadEventHandler);

    std::cout << "Server is listening on port 8080..." << std::endl;

    while (true) {
        struct sockaddr_in client_addr;
        socklen_t client_addr_len = sizeof(client_addr);
        int client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_addr_len);
        if (client_fd == -1) {
            if (errno == EWOULDBLOCK || errno == EAGAIN) {
                continue;
            } else {
                perror("accept");
                break;
            }
        }

        std::cout << "Client connected!" << std::endl;
        fcntl(client_fd, F_SETFL, O_NONBLOCK); // 设置非阻塞模式
        reactor.register_handler(client_fd, &read_handler);
    }

    close(server_fd);
    return 0;
}
