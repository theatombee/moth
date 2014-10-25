/*
 * ipv6.hpp
 *
 *  Created on: Oct 24, 2014
 *      Author: midvorki
 */

#ifndef INCLUDE_MOTH_TYPE_ADDRESS_IPV6_HPP
#define INCLUDE_MOTH_TYPE_ADDRESS_IPV6_HPP


#include "moth/type/address/base.hpp"

namespace moth
{
    namespace type
    {
        namespace address
        {
            namespace ipv6_impl
            {
                using cell_t = uint8_t;
                using concat_t = uint32_t;
                const int size = 4;

                struct formatter_f
                {
                    public:

                        static void convert(
                                const cell_t* a_in, char* a_out)
                        {
                            sprintf(a_out,
                                    "%d.%d.%d.%d",
                                    a_in[0],a_in[1],a_in[2],a_in[3]);
                        }

                        static void convert(
                                const cell_t* a_in, std::string& a_out)
                        {
                            char l_buffer[16];
                            convert(a_in, l_buffer);
                            a_out = l_buffer;
                        }

                        static std::string convert(const cell_t* a_in)
                        {
                            char l_buffer[16];
                            convert(a_in, l_buffer);
                            return l_buffer;
                        }

                        static void convert(
                                const cell_t* a_in, concat_t a_out)
                        {
                            a_out = (((concat_t) a_in[0]) << 24) |
                                    (((concat_t) a_in[1]) << 16) |
                                    (((concat_t) a_in[2]) << 8)  |
                                     ((concat_t) a_in[3]);
                        }
                };

                struct parser_f
                {
                    public:

                        static void convert(
                                const char* a_in, cell_t* a_out)
                        {
                            moth::reporter::check(
                                    (nullptr != a_in),
                                    moth::reporter::severity_t::ERROR,
                                    "null ipv6 address passed");

                            in_addr_t l_addr;

                            moth::reporter::check(
                                    -1 < (l_addr = inet_network(a_in)),
                                    moth::reporter::severity_t::ERROR,
                                    "null ipv6 address passed");


                            convert((concat_t) l_addr, a_out);
                        }

                        static void convert(
                                const std::string& a_in, cell_t* a_out)
                        {
                            convert(a_in.c_str(), a_out);
                        }

                        static void convert(
                                concat_t a_in, cell_t* a_out)
                        {
                            a_out[0] = (cell_t)((concat_t)(a_in & 0xFF000000) >> 24);
                            a_out[1] = (cell_t)((concat_t)(a_in & 0x00FF0000) >> 16);
                            a_out[2] = (cell_t)((concat_t)(a_in & 0x0000FF00) >> 8);
                            a_out[3] = (cell_t)((concat_t)(a_in & 0x000000FF));
                        }
                };
            }

            using ipv6_t = moth::type::address::base_t<
                                ipv6_impl::cell_t,
                                ipv6_impl::concat_t,
                                ipv6_impl::size,
                                ipv6_impl::formatter_f,
                                ipv6_impl::parser_f>;
        }
    }
}



#endif /* INCLUDE_MOTH_TYPE_ADDRESS_IPV6_HPP_ */
