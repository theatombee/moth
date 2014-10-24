#ifndef MOTH_INCLUDE_TYPE_ADDRESS_BASE_HPP
#define MOTH_INCLUDE_TYPE_ADDRESS_BASE_HPP
#include <stddef.h>
#include <cstddef>
#include <cstdlib>
#include <cstring>

#include "moth/reporter/reporter.hpp"

namespace moth
{
    namespace type
    {
        namespace address
        {
            template<typename T, typename N, int S>
            struct base_t
            {
                public:

                    enum
                    {
                        SIZE = S,
                        CELL_SIZE = sizeof(T),
                        NUM_OF_BYTES = (SIZE * CELL_SIZE),
                        CONCAT_SIZE = sizeof(N),
                        CONCAT_OFFSET = (NUM_OF_BYTES - CONCAT_SIZE),
                    };

                    using concat_t = N;
                    using cell_t = T;
                    using impl_t = cell_t[SIZE];

                    using value_type = cell_t;
                    using reference = cell_t &;
                    using const_reference = cell_t const &;
                    using iterator = cell_t *;
                    using const_iterator = cell_t const *;
                    using size_type = size_t;
                    using difference_type = std::ptrdiff_t;

                    ///////////////////////////////////////////////////////////////////
                    // CONSTRUCTORS
                    ///////////////////////////////////////////////////////////////////

                    base_t(const impl_t &a_in_that)
                    {
                        set(a_in_that);
                    }

                    base_t(const concat_t& a_in)
                    {
                        set(a_in);
                    }

                    base_t(const base_t &a_in_that)
                    {
                        set(a_in_that);
                    }

                    ///////////////////////////////////////////////////////////////////
                    // MUTATORS
                    ///////////////////////////////////////////////////////////////////

                    inline base_t &set(const impl_t &a_in_that)
                    {
                        memcpy(impl, a_in_that, NUM_OF_BYTES);
                        return *this;
                    }

                    inline base_t &set(concat_t const &a_in)
                    {
                        uint8_t* l_bytes = (uint8_t*) &a_in;
                        memcpy(impl, l_bytes + CONCAT_OFFSET, NUM_OF_BYTES);
                        return *this;
                    }

                    inline base_t &set(const base_t &a_in)
                    {
                        set(a_in.impl);
                        return *this;
                    }

                    inline base_t operator=(const impl_t &a_in_that)
                    {
                        return set(a_in_that);
                    }

                    inline base_t operator=(concat_t const &a_in)
                    {
                        return set(a_in);
                    }

                    inline base_t operator=(const base_t &a_in)
                    {
                        return set(a_in);
                    }

                    ///////////////////////////////////////////////////////////////////
                    // ACCESSORS
                    ///////////////////////////////////////////////////////////////////

                    inline impl_t &get()
                    {
                        return impl;
                    }

                    inline const impl_t &get() const
                    {
                        return impl;
                    }

                    inline cell_t &get(int a_in)
                    {
                        moth::reporter::check(
                                check_range(a_in),
                                moth::reporter::severity_t::ERROR,
                                "index out of range");

                        return impl[a_in];
                    }

                    inline const cell_t get(int i) const
                    {
                        return impl[i];
                    }

                    inline cell_t &operator()(int i)
                    {
                        return get(i);
                    }

                    inline cell_t operator()(int i) const
                    {
                        return get(i);
                    }

                    ///////////////////////////////////////////////////////////////////
                    // CONVERTERS
                    ///////////////////////////////////////////////////////////////////

                    inline void to_concat_t(concat_t &a_out) const
                    {
                        uint8_t* l_bytes = (uint8_t*) &a_out;
                        memset(l_bytes, 0, CONCAT_OFFSET);
                        memcpy(l_bytes + CONCAT_OFFSET, impl, NUM_OF_BYTES);
                    }

                    inline concat_t to_concat_t() const
                    {
                        concat_t l_ret;
                        to_concat_t(l_ret);
                        return l_ret;
                    }

                    inline void to_impl_t(impl_t &a_out) const
                    {
                        memcpy(a_out, impl, NUM_OF_BYTES);
                    }

                    cell_t compare(const base_t &a_in_that) const
                    {
                        cell_t l_diff = 0;
                        for (int i = 0; i < SIZE && !(l_diff = impl[i] - a_in_that.impl[i]); i++);
                        return l_diff;
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

                    ///////////////////////////////////////////////////////////////////
                    // STANDARD ITERATORS
                    ///////////////////////////////////////////////////////////////////

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

                private:

                    impl_t impl;
            };
        }
    }
}

template<typename T, typename N, int S>
bool operator<(const moth::type::address::base_t<T,N,S>& a_in_lhs,
                  const moth::type::address::base_t<T,N,S>& a_in_rhs)
{
    return 0 < a_in_lhs.compare(a_in_rhs);
}

template<typename T, typename N, int S>
bool operator>(const moth::type::address::base_t<T,N,S>& a_in_lhs,
                  const moth::type::address::base_t<T,N,S>& a_in_rhs)
{
    return 0 > a_in_lhs.compare(a_in_rhs);
}

template<typename T, typename N, int S>
bool operator<=(const moth::type::address::base_t<T,N,S>& a_in_lhs,
                  const moth::type::address::base_t<T,N,S>& a_in_rhs)
{
    return 0 <= a_in_lhs.compare(a_in_rhs);
}

template<typename T, typename N, int S>
bool operator>=(const moth::type::address::base_t<T,N,S>& a_in_lhs,
                  const moth::type::address::base_t<T,N,S>& a_in_rhs)
{
    return 0 >= a_in_lhs.compare(a_in_rhs);
}

template<typename T, typename N, int S>
bool operator==(const moth::type::address::base_t<T,N,S>& a_in_lhs,
                  const moth::type::address::base_t<T,N,S>& a_in_rhs)
{
    return 0 == a_in_lhs.compare(a_in_rhs);
}

namespace boost
{
    template<typename T, typename N, int S>
    inline std::size_t hash_value(const moth::type::address::base_t<T,N,S>& a_in)
    {
        return a_in.hash_value();
    }
}

#endif // MOTH_INCLUDE_TYPE_ADDRESS_ADRESS_HPP
