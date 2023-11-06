#ifndef TCPGECKO_H
#define TCPGECKO_H

#include "tcpconn.h"
#include <cstdint>
#include <string>

class TCPGecko {
public:
    TCPGecko(const std::string& ip, int port);
    ~TCPGecko();

    bool Connect();
    void Disconnect();
    void poke(uint32_t address, uint32_t value);
    uint32_t peek(uint32_t address);

    const uint32_t CodeHandlerStart = 0x01133000;
    const uint32_t CodeHandlerEnd = 0x01134300;
    const uint32_t CodeHandlerEnabled = 0x10014CFC;
private:
    TcpConn tcpConn;
    bool connected;
    bool cancelDump;

    void sendCommand(const std::vector<uint8_t>& command);
    std::vector<uint8_t> receiveData(size_t size);
    std::vector<uint8_t> buildPokeCommand(uint32_t address, uint32_t value);
    std::vector<uint8_t> buildPeekCommand(uint32_t address);
};

#endif