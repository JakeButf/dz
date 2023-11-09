#include "../include/tcpgecko.h"
#include "../include/geckoutils.h"
#include <iostream>
#include <stdexcept>
#include <vector>

constexpr char POKE_COMMAND = 0x01;
constexpr char PEEK_COMMAND = 0x02;
std::mutex TCPGecko::peekmem_mutex;
std::condition_variable TCPGecko::peekmem_cv;
bool TCPGecko::isPeekPending;

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
/*
* METHOD (uint32_t) PEEKMEM
* 
* This method exists to receive and store the value of an address on the Wii U.
* 
* We are adding and subtracting from the buffer in order to ignore the Command Byte*
* from TCP Gecko's response. Storing just the value of the address.
* 
* *I am not actually sure that this is the command byte, see Read() in tcpconn.h
*/
uint32_t TCPGecko::peekmem(uint32_t address)
{
    address &= 0xFFFFFFFC; //align address

    if (!tcpConn.ValidAddress(address))
        return -1; //invalid address

    uint32_t value = 0;
    uint8_t buffer[sizeof(uint32_t) + 1];
    size_t bufferSize = sizeof(buffer) - 1;

    if (tcpConn.Read(address, sizeof(uint32_t), buffer + 1))
    {
        memcpy(&value, buffer + 1, sizeof(value));
        value = ByteSwap::Swap(value);
    }
    else {
        std::cerr << "Failed to read at address" << std::hex << address << std::endl;
        return -2; //fail to read
    }
    address = NULL;
    return value;
}

uint32_t TCPGecko::peekmem8(uint32_t address)
{
    uint32_t a_address = address & 0xFFFFFFFC; //align address
    uint32_t value = TCPGecko::peekmem(a_address);
    
    int byteOffset = address & 0x03;
    uint8_t desiredByte;

    switch (byteOffset)
    {
        case 0:
            desiredByte = (value >> 24) & 0xFF;
            break;
        case 1:
            desiredByte = (value >> 16) & 0xFF;
            break;
        case 2:
            desiredByte = (value >> 8) & 0xFF;
            break;
        case 3:
            desiredByte = value & 0xFF;
            break;
    }
    return desiredByte;
}

uint8_t TCPGecko::get8Bit(uint32_t value, int index)
{
    if (index < 0 || index > 3)
        return 0;
    return (value >> (8 * index)) & 0xFF;
}
uint16_t TCPGecko::get16Bit(uint32_t value, bool last)
{
    if (last)
        return static_cast<uint16_t>(value & 0xFFFF);
    else 
        return static_cast<uint16_t>((value >> 16) & 0xFFFF);
}