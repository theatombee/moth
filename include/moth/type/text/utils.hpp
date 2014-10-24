#ifndef MOTH_INCLUDE_MOTH_TYPE_TEXT_UTILS_HPP
#define MOTH_INCLUDE_MOTH_TYPE_TEXT_UTILS_HPP
#include <cstdint>
#include <cstddef>
#include <stddef.h>
#include "moth/reporter/reporter.hpp"

namespace moth
{
    namespace type
    {
        namespace text
        {
            inline uint8_t char_to_byte(const char aIn)
            {
                switch (aIn)
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

                        return (aIn) - 48;

                    case 'A':
                    case 'B':
                    case 'C':
                    case 'D':
                    case 'E':
                    case 'F':

                        return  (aIn) - 55; // (-65 + 10)

                    case 'a':
                    case 'b':
                    case 'c':
                    case 'd':
                    case 'e':
                    case 'f':

                        return  (aIn) - 87; // (-97 + 10)

                    default:

                        moth::reporter::report(
                                moth::reporter::severity_t::ERROR,
                                "unexpected character encountered");

                        return 0;
                }
            }
        }
    }
}
#endif
