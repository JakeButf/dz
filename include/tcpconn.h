#ifndef TCPCONN_H
#define TCPCONN_H

#include "pch.h"
#include "geckoutils.h"

#include <iostream>
#include <vector>
#include <string>

enum class AddressType {
    Ex, Rw, Ro, Unknown
};

struct AddressRange {
    AddressType type;
    uint32_t start;
    uint32_t end;

    AddressRange(AddressType type, uint32_t start, uint32_t end)
        : type(type), start(start), end(end) {}
};

class TcpConn {
private:
    SOCKET socket_fd;  // The socket file descriptor for the connection
    std::string host;  // The hostname or IP to connect to
    int port;          // The port number to connect to

    static constexpr bool AddressDebug = false;

public:
    const uint32_t packetsize = 0x400;
    const uint8_t cmd_poke08 = 0x01;
    const uint8_t cmd_poke16 = 0x02;
    const uint8_t cmd_pokemem = 0x03;
    const uint8_t cmd_readmem = 0x04;
    const uint8_t cmd_writekern = 0x0b;
    const uint8_t cmd_readkern = 0x0c;
    const uint8_t cmd_os_version = 0x9A;
    static std::vector<AddressRange> ValidAreas;

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
public:
    
    // Method to read data from the connection
    bool Read(uint32_t startAddress, uint32_t length, uint8_t* buffer)
    {
        if (socket_fd == INVALID_SOCKET) // Check for valid socket
            return false;

        // Calculate end address
        uint32_t endAddress = startAddress + length; // endAddress is exclusive

        // Send the cmd_readmem command byte first
        uint8_t cmd = cmd_readmem;
        if (send(socket_fd, (const char*)&cmd, sizeof(cmd), 0) != sizeof(cmd))
        {
            std::cerr << "Failed to send read command to Wii U." << std::endl;
            return false;
        }

        // Now send the start and end addresses as an 8-byte packet
        uint64_t addressRange = ((uint64_t)ByteSwap::Swap(endAddress) << 32) | ByteSwap::Swap(startAddress);

        if (send(socket_fd, (const char*)&addressRange, sizeof(addressRange), 0) != sizeof(addressRange))
        {
            std::cerr << "Failed to send address range to Wii U." << std::endl;
            return false;
        }

        // Now receive the data
        int totalBytesReceived = 0;
        while (totalBytesReceived < length) {
            int bytesReceived = recv(socket_fd, (char*)&buffer[totalBytesReceived], length - totalBytesReceived, 0);
            if (bytesReceived == SOCKET_ERROR)
            {
                std::cerr << "Failed to receive data." << std::endl;
                return false;
            }
            totalBytesReceived += bytesReceived;
        }
        return true;
    }

    bool ReadInChunks(uint32_t address, uint32_t totalLength, uint8_t* buffer)
    {
        while (totalLength > 0) {
            uint32_t chunkSize = totalLength > packetsize ? packetsize : totalLength;
            if (!Read(address, chunkSize, buffer)) {
                return false; // Failed to read memory
            }
            buffer += chunkSize;         // Move the buffer pointer forward
            address += chunkSize;        // Move to the next address chunk
            totalLength -= chunkSize;    // Decrease the remaining length
        }
        return true;
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

    

    static bool ValidAddress(uint32_t address) {
        return ValidAddressD(address, AddressDebug);
    }

    static bool ValidRange(uint32_t start, uint32_t end) {
        return ValidRangeD(start, end, AddressDebug);
    }

    static bool ValidAddressD(uint32_t address, bool debug) {
        return debug || RangeCheckId(address) >= 0;
    }

    static bool ValidRangeD(uint32_t start, uint32_t end, bool debug) {
        return debug || RangeCheckId(start) == RangeCheckId(end - 1);
    }

    static AddressType RangeCheck(uint32_t address) {
        int id = RangeCheckId(address);
        return id == -1 ? AddressType::Unknown : ValidAreas[id].type;
    }

    static int RangeCheckId(uint32_t address) {
        for (size_t i = 0; i < ValidAreas.size(); ++i) {
            const auto& range = ValidAreas[i];
            if (address >= range.start && address < range.end) {
                return static_cast<int>(i);
            }
        }

        return -1;
    }
};
#endif
