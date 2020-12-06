#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

#pragma comment (lib, "Ws2_32.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "9999"

DWORD WINAPI handleClient(LPVOID lpParam);
void function1(SOCKET ClientSocket, char* buf);
void function2(SOCKET ClientSocket);


struct MyData {
    SOCKET ClientSocket;
    int ClientNum;
};


int main(void)
{
    WSADATA wsaData;
    struct addrinfo* result = NULL;
    struct addrinfo hints;
    int iResult;
    SOCKET ListenSocket = INVALID_SOCKET;
    SOCKET ClientSocket = INVALID_SOCKET;


    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        return 1;
    }

    ZeroMemory(&hints, sizeof(hints)); 
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;


    iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);

    if (iResult != 0) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return 1;
    }

    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

    if (ListenSocket == INVALID_SOCKET) {
        printf("socket failed with error: %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }

    iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);

    if (iResult == SOCKET_ERROR) {
        printf("bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }
    freeaddrinfo(result);


    iResult = listen(ListenSocket, SOMAXCONN);
    if (iResult == SOCKET_ERROR) {
        printf("listen failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    printf("Server is listening.\n");
    
    while (1) {
       
        ClientSocket = accept(ListenSocket, NULL, NULL);
    
        if (ClientSocket == INVALID_SOCKET) {
            printf("accept failed with error: %d\n", WSAGetLastError());
            closesocket(ListenSocket);
            WSACleanup();
            return 1;
        }
        struct MyData* myData = (struct MyData*)malloc(sizeof(struct MyData*));
        myData->ClientSocket = ClientSocket;
        myData->ClientNum = DEFAULT_BUFLEN;

        HANDLE hThread = CreateThread(NULL, 0, handleClient, (LPVOID)myData, 0, NULL);
        if (hThread == NULL) {
            printf("create thread failed.\n");
            return 1;
        }

    }
    return 0;
}
DWORD WINAPI handleClient(LPVOID lpParam) {

    struct MyData* myData = (struct MyData*)lpParam;

    SOCKET ClientSocket = myData->ClientSocket;
    char value[10];
    snprintf(value, 10, "%d", myData->ClientNum);
    char command[DEFAULT_BUFLEN];
    int iResult;
  
   
    iResult = recv(ClientSocket, command, DEFAULT_BUFLEN, 0);   
    if(iResult < 0) {
        printf("recv failed with error: %d\n", WSAGetLastError());
        closesocket(ClientSocket);
        WSACleanup();
        return 1;
    }

    char sendbuf[DEFAULT_BUFLEN];
    sprintf_s(sendbuf, DEFAULT_BUFLEN, "Flag 1: %d points!", 4);
    iResult = send(ClientSocket, sendbuf, (int)strlen(sendbuf), 0);
    if (iResult == SOCKET_ERROR) {
        printf("send failed with error: %d\n", WSAGetLastError());
        closesocket(ClientSocket);
        WSACleanup();
        return 1;
    }

    while (1) {
        ZeroMemory(command, DEFAULT_BUFLEN);
        ZeroMemory(sendbuf, DEFAULT_BUFLEN);
        iResult = recv(ClientSocket, command, DEFAULT_BUFLEN, 0);

        if (iResult > 0) {
       
            if (strcmp(command, "bye") == 0) {
                break;
            }

            else if (command[2] == '.') {
                char buf[200];
                memset(buf, 0, 200);
                strncpy_s(buf, 200, command, 200);
                function1(ClientSocket, buf);
            }

            else if (strncmp(command, value, 3) == 0) {
                function2(ClientSocket);
            }
            
            
        }
        
        else {
            printf("recv failed with error: %d\n", WSAGetLastError());
            closesocket(ClientSocket);
            WSACleanup();
            return 1;
        }
    }

    sprintf_s(sendbuf,"Flag 5: 4 points!");
    iResult = send(ClientSocket, sendbuf, (int)strlen(sendbuf), 0);
    if (iResult == SOCKET_ERROR) {
        printf("send failed with error: %d\n", WSAGetLastError());
        closesocket(ClientSocket);
        WSACleanup();
        return 1;
    }

    //shotdown connection
    iResult = shutdown(ClientSocket, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        printf("shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(ClientSocket);
        WSACleanup();
        return 1;
    }
    closesocket(ClientSocket);
    return 0;

}
void function1(SOCKET ClientSocket, char* buf) {
    if (strlen(buf) >= 15) {
        char sendbuf[20] = "Flag 2: 3 points!";
        send(ClientSocket, sendbuf, (int)strlen(sendbuf), 0);
        if (isdigit(buf[5])) {
            char sendbuf2[20] = "Flag 3: 4 points!";
            send(ClientSocket, sendbuf2, (int)strlen(sendbuf2), 0);
        }
    }
}
void function2(SOCKET ClientSocket) {
    char sendbuf[20] = "Flag 4: 5 points!";
    send(ClientSocket, sendbuf, (int)strlen(sendbuf), 0);
}




