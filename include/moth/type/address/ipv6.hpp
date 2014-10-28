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
                using concat_t = moth::type::container::fixed_array_t<uint8_t,16>;
                const int size = 16;

                // TODO:::::::

                struct formatter_f
                {
                    public:

                        static void convert_to_char_str(
                                const cell_t* a_in, char* a_out)
                        {
                            moth::reporter::check(
                                    (0 != inet_ntop(
                                            AF_INET6,
                                            a_in,
                                            a_out,
                                            INET6_ADDRSTRLEN)),
                                    moth::reporter::severity_t::ERROR,
                                    "null ipv6 address passed");
                        }

                        static void convert_to_str(
                                const cell_t* a_in, std::string& a_out)
                        {
                            char l_buffer[16];
                            convert_to_char_str(a_in, l_buffer);
                            a_out = l_buffer;
                        }

                        static std::string convert_to_str(const cell_t* a_in)
                        {
                            char l_buffer[16];
                            convert_to_char_str(a_in, l_buffer);
                            return l_buffer;
                        }

                        static void convert_to_concat(
                                const cell_t* a_in, concat_t& a_out)
                        {
                            memcpy(a_out, a_in, size);
                        }
                };

                struct parser_f
                {
                    public:

                        static void convert_from_char_str(
                                const char* a_in, cell_t* a_out)
                        {
                            moth::reporter::check(
                                    (nullptr !=  a_in) &&
                                    (0 < (inet_pton(
                                            AF_INET6,
                                            a_in,
                                            (in6_addr*) a_out))),
                                    moth::reporter::severity_t::ERROR,
                                    "invalid ipv6 address passed");

                        }

                        static void convert_from_str(
                                const std::string& a_in, cell_t* a_out)
                        {
                            convert_from_char_str(a_in.c_str(), a_out);
                        }

                        static void convert_from_concat(
                                const concat_t& a_in, cell_t* a_out)
                        {
                            memcpy((void*)a_in.get(), (void*)a_out, size);
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
