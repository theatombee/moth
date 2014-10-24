#include <cstdint>
#include <iostream>
#include "moth/reporter/reporter.hpp"
#include "moth/type/address/base.hpp"

using ipv4_t = moth::type::address::base_t<uint8_t,uint32_t,4>;

int main()
{
    ipv4_t lIpAddr1((uint32_t)0x12233445);
    ipv4_t lIpAddr2((uint32_t)0x32233445);
    std::cout << std::hex << lIpAddr1.to_concat_t() << std::endl;
    std::cout << std::hex << lIpAddr2.to_concat_t() << std::endl;

    if (lIpAddr2 == lIpAddr2)
    {
        std::cout << "correct!" << std::endl;
    }
    else
    {
        std::cout << "wrong!" << std::endl;
    }
}
