#ifndef MOTH_INCLUDE_TYPE_ADDRESS_IPV4_HPP
#define MOTH_INCLUDE_TYPE_ADDRESS_IPV4_HPP

#include "moth/type/address/base.hpp"

namespace moth
{
    namespace type
    {
        namespace address
        {
            namespace ipv4_impl
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
                            // TODO:xxx.xxx.xxx.xxx
                            a_out[0] = 0;
                            a_out[1] = 0;
                            a_out[2] = 0;
                            a_out[3] = 0;

                            moth::reporter::check(
                                    (nullptr != a_in),
                                    moth::reporter::severity_t::ERROR,
                                    "null ipv4 address passed");
                            int l_begin = 0;
                            int l_end = -1;
                            for (int l_idx = 0; '\0' != a_in[l_idx]; ++l_idx)
                            {
                                char l_char = a_in[l_idx];
                                //if (isdigit())
                            }
                        }

                        static void convert(
                                const std::string& a_in, cell_t* a_out)
                        {
                            // TODO:
                        }

                        static void convert(
                                concat_t a_in, cell_t* a_out)
                        {
                            a_out[2] = (cell_t)((concat_t)(a_in & 0xFF000000) >> 24);
                            a_out[3] = (cell_t)((concat_t)(a_in & 0x00FF0000) >> 16);
                            a_out[4] = (cell_t)((concat_t)(a_in & 0x0000FF00) >> 8);
                            a_out[5] = (cell_t)((concat_t)(a_in & 0x000000FF));
                        }
                };
            }

            using ipv4_t = moth::type::address::base_t<
                                ipv4_impl::cell_t,
                                ipv4_impl::concat_t,
                                ipv4_impl::size,
                                ipv4_impl::formatter_f,
                                ipv4_impl::parser_f>;
        }
    }
}
#endif
