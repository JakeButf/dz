#ifndef GECKOUTILS_H
#define GECKOUTILS_H

#include <cstdint>
#include <stdexcept>
#include <type_traits>

constexpr bool isLittleEndian() {
    union {
        uint32_t i;
        char c[4];
    } test_union = { 0x01020304 };

    return test_union.c[0] == 0x04;
}


// ByteSwap class with static functions for endianness conversion.
class ByteSwap {
public:
    // Swap bytes for uint16_t
    static uint16_t Swap(uint16_t input) {
        if (isLittleEndian()) {
            return (input >> 8) | (input << 8);
        }
        else {
            return input;
        }
    }

    // Swap bytes for uint32_t
    static uint32_t Swap(uint32_t input) {
        if (isLittleEndian()) {
            return ((input >> 24) & 0xff) |
                ((input << 8) & 0xff0000) |
                ((input >> 8) & 0xff00) |
                ((input << 24) & 0xff000000);
        }
        else {
            return input;
        }
    }

    // Swap bytes for uint64_t
    static uint64_t Swap(uint64_t input) {
        if (isLittleEndian()) {
            return ((input >> 56) & 0xff) |
                ((input << 40) & 0xff000000000000) |
                ((input << 24) & 0xff0000000000) |
                ((input << 8) & 0xff00000000) |
                ((input >> 8) & 0xff000000) |
                ((input >> 24) & 0xff0000) |
                ((input >> 40) & 0xff00) |
                ((input << 56) & 0xff00000000000000);
        }
        else {
            return input;
        }
    }
};

// Enumeration for TCP Gecko error codes.
enum class ETCPErrorCode {
    noTCPGeckoFound,
    FTDICommandSendError,
    FTDIReadDataError,
    TooManyRetries
};

// Enumeration for FTDI command codes.
enum class FTDICommand {
    CMD_ResultError,
    CMD_FatalError,
    CMD_OK
};

// Progress function type definition for the GeckoProgress.
typedef void (*GeckoProgress)(uint32_t address, uint32_t currentchunk, uint32_t allchunks,
    uint32_t transferred, uint32_t length, bool okay, bool dump);

// Custom exception class for TCP Gecko exceptions.
class ETCPGeckoException : public std::runtime_error {
private:
    ETCPErrorCode errorCode;

public:
    explicit ETCPGeckoException(ETCPErrorCode code)
        : std::runtime_error("TCP Gecko exception occurred"), errorCode(code) {}

    ETCPErrorCode getErrorCode() const {
        return errorCode;
    }
};



#endif
