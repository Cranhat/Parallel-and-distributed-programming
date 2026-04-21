#include "Client.hpp"
#include <iostream>
#include "Com_utils.hpp"

void Client::runClient() {
    initSockets();

    socket_t sock = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(54000);
    inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);

    connect(sock, (sockaddr*)&serverAddr, sizeof(serverAddr));

    while (true) {
        uint n;
        std::cout << "Podaj n: ";
        std::cin >> n;

        std::string msg = std::to_string(n);

        send(sock, msg.c_str(), msg.size(), 0);

        char buffer[1024]{};
        int bytes = recv(sock, buffer, sizeof(buffer) - 1, 0);

        if (bytes <= 0) {
            std::cout << "Server disconnected\n";
            break;
        }

        buffer[bytes] = '\0';

        std::cout << "Wynik: " << buffer << std::endl;
    }

    closeSocket(sock);
    cleanupSockets();
}