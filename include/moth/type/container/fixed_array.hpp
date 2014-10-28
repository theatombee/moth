/*
 * fixed_array.hpp
 *
 *  Created on: Oct 24, 2014
 *      Author: midvorki
 */

#ifndef INCLUDE_MOTH_TYPE_CONTAINER_FIXED_ARRAY_HPP_
#define INCLUDE_MOTH_TYPE_CONTAINER_FIXED_ARRAY_HPP_

#include <cstring>
#include "moth/reporter/reporter.hpp"

namespace moth
{
    namespace type
    {
        namespace container
        {
            template<typename type_tt, int size_tp>
            struct fixed_array_t
            {
                public:

                    using type_t = type_tt;
                    using value_type = type_t;
                    using reference = type_t &;
                    using const_reference = type_t const &;
                    using iterator = type_t *;
                    using const_iterator = type_t const *;
                    using size_type = size_t;
                    using difference_type = std::ptrdiff_t;

                    enum
                    {
                        SIZE = size_tp,
                        CELL_SIZE = sizeof(type_tt),
                        NUM_OF_BYTES = (SIZE * CELL_SIZE),
                    };

                    inline type_t& operator[](int a_in)
                    {
                        moth::reporter::check(
                                check_range(a_in),
                                moth::reporter::severity_t::ERROR,
                                "index out of range");

                        return impl[a_in];
                    }

                    inline const type_t& operator[](int a_in) const
                    {
                        return impl[a_in];
                    }

                    inline operator type_t* ()
                    {
                        return impl;
                    }

                    inline operator const type_t* () const
                    {
                        return impl;
                    }

                    inline fixed_array_t& set(const type_t* a_in)
                    {
                        std::memcpy(impl, a_in, NUM_OF_BYTES);
                        return *this;
                    }

                    inline fixed_array_t& operator=(const type_t* a_in)
                    {
                        return set(a_in);
                    }

                    inline fixed_array_t& set(const fixed_array_t& a_in)
                    {
                        return set(a_in);
                    }

                    inline fixed_array_t& operator=(const fixed_array_t& a_in)
                    {
                        return set(a_in);
                    }

                    void reset()
                    {
                        std::memset(impl, 0, NUM_OF_BYTES);
                    }

                    type_t compare(const fixed_array_t& a_in_that) const
                    {
                        return std::memcmp(impl, a_in_that.impl, SIZE);
                    }

                    std::size_t hash_value() const
                    {
                        std::size_t lSeed = 0;
                        for(const_iterator i=begin(); i != end(); ++i)
                        {
                            lSeed ^= static_cast<std::size_t>(*i) + 0x9e3779b9 + (lSeed << 6) + (lSeed >> 2);
                        }
                        return lSeed;
                    }

                    inline type_t* get()
                    {
                        return impl;
                    }

                    inline type_t const* get() const
                    {
                        return impl;
                    }

                    inline iterator begin()
                    {
                        return impl;
                    }

                    inline iterator end()
                    {
                        return (impl + SIZE);
                    }

                    inline const_iterator begin() const
                    {
                        return (const_iterator) impl;
                    }

                    inline const_iterator end() const
                    {
                        return (const_iterator) (impl + SIZE);
                    }

                    inline size_type size() const
                    {
                        return SIZE;
                    }

                    inline bool is_nil() const
                    {
                        bool l_ret = true;
                        for (int i=0;
                             i < SIZE && (l_ret = (0 == impl[i]));
                             i++);
                        return l_ret;
                    }

                protected:

                    inline static bool check_range(int a_in_index)
                    {
                        return -1 < a_in_index && a_in_index < SIZE;
                    }

                    type_t impl[SIZE];
            };
        }
    }
}

template<typename type_tt, int size_tp>
bool operator<(const moth::type::container::fixed_array_t<
                   type_tt,
                   size_tp>& a_in_lhs,
               const moth::type::container::fixed_array_t<
                   type_tt,
                   size_tp>& a_in_rhs)
{
    return 0 < a_in_lhs.compare(a_in_rhs);
}


template<typename type_tt, int size_tp>
bool operator>(const moth::type::container::fixed_array_t<
                    type_tt,
                    size_tp>& a_in_lhs,
               const moth::type::container::fixed_array_t<
                    type_tt,
                    size_tp>& a_in_rhs)
{
    return 0 > a_in_lhs.compare(a_in_rhs);
}

template<typename type_tt, int size_tp>
bool operator<=(const moth::type::container::fixed_array_t<
                    type_tt,
                    size_tp>& a_in_lhs,
                const moth::type::container::fixed_array_t<
                    type_tt,
                    size_tp>& a_in_rhs)
{
    return 0 <= a_in_lhs.compare(a_in_rhs);
}

template<typename type_tt, int size_tp>
bool operator>=(const moth::type::container::fixed_array_t<
                    type_tt,
                    size_tp>& a_in_lhs,
                const moth::type::container::fixed_array_t<
                    type_tt,
                    size_tp>& a_in_rhs)
{
    return 0 >= a_in_lhs.compare(a_in_rhs);
}

template<typename type_tt, int size_tp>
bool operator==(const moth::type::container::fixed_array_t<
                    type_tt,
                    size_tp>& a_in_lhs,
                const moth::type::container::fixed_array_t<
                    type_tt,
                    size_tp>& a_in_rhs)
{
    return 0 == a_in_lhs.compare(a_in_rhs);
}

namespace boost
{
    template<typename type_tt, int size_tp>
    inline std::size_t hash_value(
            const moth::type::container::fixed_array_t<
                        type_tt, size_tp>& a_in)
    {
        return a_in.hash_value();
    }
}

#endif /* INCLUDE_MOTH_TYPE_CONTAINER_FIXED_ARRAY_HPP_ */
