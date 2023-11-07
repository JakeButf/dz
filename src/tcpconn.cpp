#include "../include/tcpconn.h"

std::vector<AddressRange> TcpConn::ValidAreas = {
    AddressRange(AddressType::Ex, 0x01000000, 0x01800000),
    AddressRange(AddressType::Ex, 0x0e300000, 0x10000000),
    AddressRange(AddressType::Rw, 0x10000000, 0x50000000),
    AddressRange(AddressType::Ro, 0xe0000000, 0xe4000000),
    AddressRange(AddressType::Ro, 0xe8000000, 0xea000000),
    AddressRange(AddressType::Ro, 0xf4000000, 0xf6000000),
    AddressRange(AddressType::Ro, 0xf6000000, 0xf6800000),
    AddressRange(AddressType::Ro, 0xf8000000, 0xfb000000),
    AddressRange(AddressType::Ro, 0xfb000000, 0xfb800000),
    AddressRange(AddressType::Rw, 0xfffe0000, 0xffffffff)
};