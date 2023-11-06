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