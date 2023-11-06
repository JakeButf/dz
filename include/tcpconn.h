#ifndef TCPCONN_H
#define TCPCONN_H

#include "pch.h"

#include <iostream>
#include <vector>
#include <string>

class TcpConn {
private:
    SOCKET socket_fd;  // The socket file descriptor for the connection
    std::string host;  // The hostname or IP to connect to
    int port;          // The port number to connect to

public:
    // Constructor to initialize the connection with a host and port
    TcpConn(const std::string& host, int port) : host(host), port(port), socket_fd(INVALID_SOCKET) {
        // Initialize Winsock
        WSADATA wsaData;
        int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
        if (result != 0) {
            throw std::runtime_error("WSAStartup failed with error: " + std::to_string(result));
        }
    }

    // Destructor to clean up the connection and Winsock
    ~TcpConn() {
        Close();
        WSACleanup();
    }

    // Method to establish a connection to the server
    void Connect() {
        Close();  // Ensure any existing connection is closed first

        struct addrinfo hints, * res;
        ZeroMemory(&hints, sizeof(hints)); // Zero out the structure
        hints.ai_family = AF_UNSPEC;       // Don't specify which IP version to use yet
        hints.ai_socktype = SOCK_STREAM;   // Specify a stream socket (TCP)
        hints.ai_protocol = IPPROTO_TCP;   // Specify the TCP protocol

        // Resolve the server address and port
        if (getaddrinfo(host.c_str(), std::to_string(port).c_str(), &hints, &res) != 0) {
            throw std::runtime_error("getaddrinfo failed");
        }

        // Create a SOCKET for connecting to the server
        socket_fd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
        if (socket_fd == INVALID_SOCKET) {
            freeaddrinfo(res); // Free the resources allocated by getaddrinfo
            throw std::runtime_error("Error at socket(): " + std::to_string(WSAGetLastError()));
        }

        // Connect to the server
        int result = connect(socket_fd, res->ai_addr, (int)res->ai_addrlen);
        freeaddrinfo(res); // Free the resources allocated by getaddrinfo

        if (result == SOCKET_ERROR) {
            closesocket(socket_fd); // If connection fails, close the socket
            socket_fd = INVALID_SOCKET;
            throw std::runtime_error("Unable to connect to server!");
        }
    }

    // Method to close the connection
    void Close() {
        if (socket_fd != INVALID_SOCKET) {
            closesocket(socket_fd); // Close the socket if it is valid
            socket_fd = INVALID_SOCKET;
        }
    }

    // Method to read data from the connection
    void Read(std::vector<char>& buffer, uint32_t nobytes, uint32_t& bytesRead) {
        bytesRead = 0;

        if (socket_fd == INVALID_SOCKET) {
            throw std::runtime_error("Not connected.");
        }

        buffer.resize(nobytes);
        // Receive data from the server
        int result = recv(socket_fd, buffer.data(), nobytes, 0);
        if (result > 0) {
            bytesRead = static_cast<uint32_t>(result);
        }
        else if (result == 0) {
            throw std::runtime_error("Connection closed by peer.");
        }
        else {
            throw std::runtime_error("recv failed: " + std::to_string(WSAGetLastError()));
        }
    }

    // Method to send data to the connection
    void Write(const std::vector<char>& buffer, int nobytes, uint32_t& bytesWritten) {
        bytesWritten = 0;

        if (socket_fd == INVALID_SOCKET) {
            throw std::runtime_error("Not connected.");
        }

        // Send data to the server
        int result = send(socket_fd, buffer.data(), nobytes, 0);
        if (result == SOCKET_ERROR) {
            throw std::runtime_error("send failed: " + std::to_string(WSAGetLastError()));
        }
        bytesWritten = static_cast<uint32_t>(result);
    }
};
#endif
