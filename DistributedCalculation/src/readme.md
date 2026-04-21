g++ -std=c++20 Server.cpp Com_utils.cpp server_main.cpp -o s -lws2_32
g++ Client.cpp Com_utils.cpp client_main.cpp -o c -lws2_32   