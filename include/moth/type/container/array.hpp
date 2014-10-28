/*
 * array.hpp
 *
 *  Created on: Oct 25, 2014
 *      Author: midvorki
 */

#ifndef INCLUDE_MOTH_TYPE_CONTAINER_ARRAY_HPP_
#define INCLUDE_MOTH_TYPE_CONTAINER_ARRAY_HPP_

#include <array>
namespace moth
{
    namespace type
    {
        namespace container
        {
            template<typename type_tt, int size_tp>
            using array_t = std::array<type_tt, size_tp>;
        }
    }
}


#endif /* INCLUDE_MOTH_TYPE_CONTAINER_ARRAY_HPP_ */
