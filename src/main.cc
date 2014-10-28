#include <cstdint>
#include <iostream>
#include "moth/reporter/reporter.hpp"
#include "moth/type/address/base.hpp"
#include "moth/type/address/ipv4.hpp"
#include "moth/type/address/ipv6.hpp"
#include "moth/type/address/mac.hpp"
#include "moth/type/container/fixed_array.hpp"

/*
  template<typename cell_type_tt,
                     typename concat_type_tt,
                     int size_tp,
                     char delim_tp,
                     typename stringifier_tf,
                     typename parser_tf>
 */


using ipv4_t = moth::type::address::ipv4_t;

int main()
{
    {
        ipv4_t ip_address("192.168.1.1");
        size_t l_count(0);
        for (ipv4_t::iterator l_it = ip_address.begin(); l_it != ip_address.end(); l_it++)
        {
            std::cout << "[" << (l_count++) << "]=" << (int)*l_it << std::endl;
        }
    }
    //in_addr_t address = inet_addr(l_string_ip_address.c_str());

}
