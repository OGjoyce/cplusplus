#include <iostream>
#include <cstring>
#include <sstream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>

const int PORT = 8080;
const int BUFFER_SIZE = 1024;

void handleClient(int clientSocket) {
    char buffer[BUFFER_SIZE];
    memset(buffer, 0, sizeof(buffer));

    // Read the incoming data from the client
    int bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);

    if (bytesRead < 0) {
        std::cerr << "Error reading from client" << std::endl;
        return;
    }

    // Parse the HTTP request
    std::istringstream request(buffer);
    std::string requestType, path, httpVersion;
    request >> requestType >> path >> httpVersion;

    // Send a simple response back to the client
    std::string response = "HTTP/1.1 200 OK\r\nContent-Length: 12\r\n\r\nHello, World!";
    send(clientSocket, response.c_str(), response.length(), 0);

    // Close the client socket
    close(clientSocket);
}

int main() {
    // Create a socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (serverSocket < 0) {
        std::cerr << "Error creating socket" << std::endl;
        return 1;
    }

    // Bind the socket to a specific address and port
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(PORT);

    if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
        std::cerr << "Error binding socket" << std::endl;
        return 1;
    }

    // Listen for incoming connections
    if (listen(serverSocket, 10) < 0) {
        std::cerr << "Error listening for connections" << std::endl;
        return 1;
    }

    std::cout << "Server listening on port " << PORT << "..." << std::endl;

    while (true) {
        // Accept a connection from a client
        sockaddr_in clientAddress;
        socklen_t clientAddressLength = sizeof(clientAddress);
        int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &clientAddressLength);

        if (clientSocket < 0) {
            std::cerr << "Error accepting client connection" << std::endl;
            continue;
        }

        // Handle the client request
        handleClient(clientSocket);
    }

    // Close the server socket
    close(serverSocket);

    return 0;
}
