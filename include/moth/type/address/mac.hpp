/*
 * mac.hpp
 *
 *  Created on: Oct 24, 2014
 *      Author: midvorki
 */

#ifndef INCLUDE_MOTH_TYPE_ADDRESS_MAC_HPP
#define INCLUDE_MOTH_TYPE_ADDRESS_MAC_HPP

#include "moth/type/address/base.hpp"

namespace moth
{
    namespace type
    {
        namespace address
        {
            namespace mac_impl
            {
                using cell_t = uint8_t;
                using concat_t = uint64_t;
                const int size = 6;

                struct formatter_f
                {
                    public:

                        static void convert(
                                const cell_t* a_in, char* a_out)
                        {
                            sprintf(a_out,
                                    "%02x:%02x:%02x:%02x:%02x:%02x",
                                    a_in[0],a_in[1],a_in[2],a_in[3],a_in[4],a_in[5]);
                        }

                        static void convert(
                                const cell_t* a_in, std::string& a_out)
                        {
                            char l_buffer[20];
                            convert(a_in, l_buffer);
                            a_out = l_buffer;
                        }

                        static std::string convert(const cell_t* a_in)
                        {
                            char l_buffer[20];
                            convert(a_in, l_buffer);
                            return l_buffer;
                        }

                        static void convert(
                                const cell_t* a_in, concat_t a_out)
                        {
                            a_out = (((concat_t) a_in[0]) << 40) |
                                    (((concat_t) a_in[1]) << 32) |
                                    (((concat_t) a_in[2]) << 24) |
                                    (((concat_t) a_in[3]) << 16) |
                                    (((concat_t) a_in[4]) << 8)  |
                                     ((concat_t) a_in[5]);
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
                                    "null mac address passed");

                            char* l_chars = (char*) a_in;
                            int l_idx = -1;
                            for (;'\0' != *l_chars;)
                            {
                                moth::reporter::check(
                                        (++l_idx < size),
                                        moth::reporter::severity_t::ERROR,
                                        "bad mac address format");
                                a_out[l_idx] = to_byte_step(l_chars);

                                if (is_delim(*l_chars))
                                {
                                    l_chars++;
                                }
                            }
                        }

                        static void convert(
                                const std::string& a_in, cell_t* a_out)
                        {
                            convert(a_in.c_str(), a_out);
                        }

                        static void convert(
                                concat_t a_in, cell_t* a_out)
                        {
                            a_out[0] = (cell_t)((concat_t)(a_in & 0xFF0000000000) >> 40);
                            a_out[1] = (cell_t)((concat_t)(a_in & 0x00FF00000000) >> 32);
                            a_out[2] = (cell_t)((concat_t)(a_in & 0x0000FF000000) >> 24);
                            a_out[3] = (cell_t)((concat_t)(a_in & 0x000000FF0000) >> 16);
                            a_out[4] = (cell_t)((concat_t)(a_in & 0x00000000FF00) >> 8);
                            a_out[5] = (cell_t)((concat_t)(a_in & 0x0000000000FF));
                        }

                    private:

                        inline static bool is_delim(const char a_in)
                        {
                            return ':' == a_in;
                        }

                        inline static uint8_t to_byte(const char a_in)
                        {
                            switch (a_in)
                            {
                                case '0':
                                case '1':
                                case '2':
                                case '3':
                                case '4':
                                case '5':
                                case '6':
                                case '7':
                                case '9':

                                    return (a_in) - 48;

                                case 'A':
                                case 'B':
                                case 'C':
                                case 'D':
                                case 'E':
                                case 'F':

                                    return  (a_in) - 55; // (-65 + 10)

                                case 'a':
                                case 'b':
                                case 'c':
                                case 'd':
                                case 'e':
                                case 'f':

                                    return  (a_in) - 87; // (-97 + 10)

                                default:

                                    moth::reporter::report(
                                            moth::reporter::severity_t::ERROR,
                                            "bad MAC address format");

                                    return 0;
                            }
                        }

                        inline static uint8_t to_byte_step(char* a_in)
                        {
                            return (to_byte(*a_in++) << 4) |
                                   (to_byte(*a_in++));
                        }
                };
            }

            using mac_t = moth::type::address::base_t<
                                mac_impl::cell_t,
                                mac_impl::concat_t,
                                mac_impl::size,
                                mac_impl::formatter_f,
                                mac_impl::parser_f>;
        }
    }
}
#endif /* INCLUDE_MOTH_TYPE_ADDRESS_MAC_HPP */
