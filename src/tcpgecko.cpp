#include "../include/tcpgecko.h"
#include "../include/geckoutils.h"
#include <iostream>
#include <stdexcept>
#include <vector>

constexpr char POKE_COMMAND = 0x01;
constexpr char PEEK_COMMAND = 0x02;

TCPGecko::TCPGecko(const std::string& ip, int port)
    : tcpConn(ip, port), connected(false), cancelDump(false) {
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

void TCPGecko::poke(uint32_t address, uint32_t value) {
    if (!connected) {
        throw std::runtime_error("Not connected to Gecko");
    }
    auto command = buildPokeCommand(address, value);
    sendCommand(command);
}

uint32_t TCPGecko::peek(uint32_t address) {
    if (!connected) {
        throw std::runtime_error("Not connected to Gecko");
    }
    auto command = buildPeekCommand(address);
    sendCommand(command);
    auto data = receiveData(sizeof(uint32_t));
    return ByteSwap::Swap(*reinterpret_cast<uint32_t*>(data.data()));
}

void TCPGecko::sendCommand(const std::vector<uint8_t>& command) {
    uint32_t bytesWritten = 0;
    tcpConn.Write(std::vector<char>(command.begin(), command.end()), command.size(), bytesWritten);
}

std::vector<uint8_t> TCPGecko::receiveData(size_t size) {
    std::vector<uint8_t> buffer(size);
    uint32_t bytesRead = 0;
    std::vector<char> charBuffer(buffer.begin(), buffer.end());
    tcpConn.Read(charBuffer, size, bytesRead);
    buffer = std::vector<uint8_t>(charBuffer.begin(), charBuffer.begin() + bytesRead);

    return buffer;
}

std::vector<uint8_t> TCPGecko::buildPokeCommand(uint32_t address, uint32_t value) {
    std::vector<uint8_t> command;
    command.push_back(POKE_COMMAND); // The poke command identifier

    // Convert address and value to big endian and split into bytes
    uint32_t bigEndianAddress = ByteSwap::Swap(address);
    uint32_t bigEndianValue = ByteSwap::Swap(value);

    // Add the address bytes to the command vector
    command.push_back(static_cast<uint8_t>((bigEndianAddress >> 24) & 0xFF));
    command.push_back(static_cast<uint8_t>((bigEndianAddress >> 16) & 0xFF));
    command.push_back(static_cast<uint8_t>((bigEndianAddress >> 8) & 0xFF));
    command.push_back(static_cast<uint8_t>(bigEndianAddress & 0xFF));

    // Add the value bytes to the command vector
    command.push_back(static_cast<uint8_t>((bigEndianValue >> 24) & 0xFF));
    command.push_back(static_cast<uint8_t>((bigEndianValue >> 16) & 0xFF));
    command.push_back(static_cast<uint8_t>((bigEndianValue >> 8) & 0xFF));
    command.push_back(static_cast<uint8_t>(bigEndianValue & 0xFF));

    return command;
}

std::vector<uint8_t> TCPGecko::buildPeekCommand(uint32_t address) {
    std::vector<uint8_t> command;
    command.push_back(PEEK_COMMAND); // The peek command identifier

    // Convert address to big endian and split into bytes
    uint32_t bigEndianAddress = ByteSwap::Swap(address);

    // Add the address bytes to the command vector
    command.push_back(static_cast<uint8_t>((bigEndianAddress >> 24) & 0xFF));
    command.push_back(static_cast<uint8_t>((bigEndianAddress >> 16) & 0xFF));
    command.push_back(static_cast<uint8_t>((bigEndianAddress >> 8) & 0xFF));
    command.push_back(static_cast<uint8_t>(bigEndianAddress & 0xFF));

    return command;
}
