#include "../include/tcpgecko.h"
#include "../include/geckoutils.h"
#include <iostream>
#include <stdexcept>
#include <vector>

constexpr char POKE_COMMAND = 0x01;
constexpr char PEEK_COMMAND = 0x02;

TCPGecko::TCPGecko(const std::string& ip, int port)
    : tcpConn(ip, port), connected(false) {
}

TCPGecko::~TCPGecko() {
    Disconnect();
}

bool TCPGecko::Connect() {
    try {
        tcpConn.Connect();
        connected = true;
        return true;
    }
    catch (const std::exception& e) {
        std::cerr << "Connection failed: " << e.what() << std::endl;
        connected = false;
        return false;
    }
}

void TCPGecko::Disconnect() {
    if (connected) {
        tcpConn.Close();
        connected = false;
    }
}

uint32_t TCPGecko::peekmem(uint32_t address)
{
    address &= 0xFFFFFFFC; //align address

    if (!tcpConn.ValidAddress(address))
        return -1; //invalid address

    uint32_t value = 0;
    uint8_t buffer[sizeof(uint32_t)];

    if (tcpConn.Read(address, sizeof(uint32_t), buffer))
    {
        memcpy(&value, buffer, sizeof(value));
        value = ByteSwap::Swap(value);
    }
    else {
        std::cerr << "Failed to read at address" << std::hex << address << std::endl;
        return -2; //fail to read
    }
    return value;
}