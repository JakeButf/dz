#ifndef TCPGECKO_H
#define TCPGECKO_H

#include "tcpconn.h"
#include <cstdint>
#include <string>
#include <mutex>

class TCPGecko {
public:
    TCPGecko(const std::string& ip, int port);
    ~TCPGecko();
    static std::mutex peekmem_mutex;
    static std::condition_variable peekmem_cv;
    static bool isPeekPending;

    bool Connect();
    void Disconnect();

    uint32_t peekmem(uint32_t address);
    uint32_t peekmem8(uint32_t address);

    uint8_t get8Bit(uint32_t value, int index);
    uint16_t get16Bit(uint32_t value, bool last);

    const uint32_t CodeHandlerStart = 0x01133000;
    const uint32_t CodeHandlerEnd = 0x01134300;
    const uint32_t CodeHandlerEnabled = 0x10014CFC;

private:
    TcpConn tcpConn;
    bool connected;
};

#endif