#include "Com_utils.hpp"

void initSockets() {
#ifdef _WIN32
    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2), &wsa);
#endif
}

void cleanupSockets() {
#ifdef _WIN32
    WSACleanup();
#endif
}

void closeSocket(socket_t s) {
#ifdef _WIN32
    closesocket(s);
#else
    close(s);
#endif
}