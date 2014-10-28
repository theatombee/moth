#ifndef MOTH_INCLUDE_TYPE_ADDRESS_BASE_HPP
#define MOTH_INCLUDE_TYPE_ADDRESS_BASE_HPP
#include <stddef.h>
#include <cstddef>
#include <cstdlib>
#include <cstring>

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <cctype>

#include <arpa/inet.h>

#include "moth/reporter/reporter.hpp"
#include "moth/type/container/fixed_array.hpp"

namespace moth
{
    namespace type
    {
        namespace address
        {
            template<typename cell_type_tt,
                     typename concat_type_tt,
                     int size_tp,
                     typename formatter_tf,
                     typename parser_tf>
            struct base_t
            {
                public:

                    enum
                    {
                        SIZE = size_tp,
                        CELL_SIZE = sizeof(cell_type_tt),
                        NUM_OF_BYTES = (SIZE * CELL_SIZE),
                        CONCAT_SIZE = sizeof(concat_type_tt),
                        CONCAT_OFFSET = (NUM_OF_BYTES - CONCAT_SIZE),
                    };

                    using concat_t = concat_type_tt;
                    using cell_t = cell_type_tt;
                    using impl_t = moth::type::container::fixed_array_t<cell_t, SIZE>;

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

                    base_t(const impl_t& a_in_that)
                    {
                        set(a_in_that);
                    }

                    base_t(const concat_t& a_in)
                    {
                        set(a_in);
                    }

                    base_t(const base_t& a_in_that)
                    {
                        set(a_in_that);
                    }

                    base_t(const char* a_in)
                    {
                        set(a_in);
                    }

                    base_t(const std::string& a_in)
                    {
                        set(a_in);
                    }

                    ///////////////////////////////////////////////////////////////////
                    // MUTATORS
                    ///////////////////////////////////////////////////////////////////

                    inline base_t& set(const impl_t& a_in_that)
                    {
                        impl = a_in_that;
                        return *this;
                    }

                    inline base_t& set(concat_t a_in)
                    {
                        parser_tf::convert_from_concat(a_in,impl);
                        return *this;
                    }

                    inline base_t& set(const base_t& a_in)
                    {
                        set(a_in.impl);
                        return *this;
                    }

                    inline base_t& set(const std::string& a_in)
                    {
                        parser_tf::convert_from_str(a_in, impl);
                        return *this;
                    }

                    inline base_t& set(const char* a_in)
                    {
                        parser_tf::convert_from_char_str(a_in, impl);
                        return *this;
                    }

                    inline base_t& operator=(const impl_t& a_in_that)
                    {
                        return set(a_in_that);
                    }

                    inline base_t& operator=(concat_t const& a_in)
                    {
                        return set(a_in);
                    }

                    inline base_t& operator=(const base_t& a_in)
                    {
                        return set(a_in);
                    }

                    inline base_t& operator=(const std::string& a_in)
                    {
                        return set(a_in);
                    }

                    inline base_t& operator=(const char*& a_in)
                    {
                        return set(a_in);
                    }

                    ///////////////////////////////////////////////////////////////////
                    // ACCESSORS
                    ///////////////////////////////////////////////////////////////////

                    inline impl_t& get()
                    {
                        return impl;
                    }

                    inline const impl_t& get() const
                    {
                        return impl;
                    }

                    inline cell_t& get(int a_in)
                    {
                        return impl[a_in];
                    }

                    inline const cell_t get(int i) const
                    {
                        return impl[i];
                    }

                    inline cell_t& operator[](int i)
                    {
                        return get(i);
                    }

                    inline cell_t operator[](int i) const
                    {
                        return get(i);
                    }

                    ///////////////////////////////////////////////////////////////////
                    // CONVERTERS
                    ///////////////////////////////////////////////////////////////////

                    inline void to_concat_t(concat_t& a_out) const
                    {
                        formatter_tf::convert_to_concat(impl,a_out);
                    }

                    inline concat_t to_concat_t() const
                    {
                        concat_t l_ret;
                        to_concat_t(l_ret);
                        return l_ret;
                    }

                    inline operator concat_t () const
                    {
                        return to_concat_t();
                    }

                    inline void to_impl_t(impl_t& a_out) const
                    {
                        a_out = impl;
                    }

                    cell_t compare(const base_t& a_in_that) const
                    {
                        return impl.compare(a_in_that.impl);
                    }

                    std::size_t hash_value() const
                    {
                        return impl.hash_value();
                    }

                    inline void to_string(char* a_out) const
                    {
                        formatter_tf::convert_to_char_str(impl,a_out);
                    }

                    inline void to_string(std::string& a_out) const
                    {
                        formatter_tf::convert_to_str(impl,a_out);
                    }

                    inline std::string to_string() const
                    {
                        return formatter_tf::convert_to_str(impl);
                    }

                    ///////////////////////////////////////////////////////////////////
                    // STANDARD ITERATORS
                    ///////////////////////////////////////////////////////////////////

                    inline iterator begin()
                    {
                        return impl.begin();
                    }

                    inline iterator end()
                    {
                        return impl.end();
                    }

                    inline const_iterator begin() const
                    {
                        return (const_iterator) impl.begin();
                    }

                    inline const_iterator end() const
                    {
                        return (const_iterator) impl.end();
                    }

                    inline size_type size() const
                    {
                        return impl.size();
                    }

                    inline bool is_nil() const
                    {
                        return impl.is_nil();
                    }

                private:

                    impl_t impl;
            };
        }
    }
}

template<
    typename cell_type_tt,
    typename concat_type_tt,
    int size_tp,
    typename formatter_tf,
    typename parser_tf>
bool operator<(const moth::type::address::base_t<
                   cell_type_tt,
                   concat_type_tt,
                   size_tp,
                   formatter_tf,
                   parser_tf>& a_in_lhs,
               const moth::type::address::base_t<
                   cell_type_tt,
                   concat_type_tt,
                   size_tp,
                   formatter_tf,
                   parser_tf>& a_in_rhs)
{
    return 0 < a_in_lhs.compare(a_in_rhs);
}

template<
    typename cell_type_tt,
    typename concat_type_tt,
    int size_tp,
    typename formatter_tf,
    typename parser_tf>
bool operator>(const moth::type::address::base_t<
                    cell_type_tt,
                    concat_type_tt,
                    size_tp,
                    formatter_tf,
                    parser_tf>& a_in_lhs,
               const moth::type::address::base_t<
                    cell_type_tt,
                    concat_type_tt,
                    size_tp,
                    formatter_tf,
                    parser_tf>& a_in_rhs)
{
    return 0 > a_in_lhs.compare(a_in_rhs);
}

template<
    typename cell_type_tt,
    typename concat_type_tt,
    int size_tp,
    typename formatter_tf,
    typename parser_tf>
bool operator<=(const moth::type::address::base_t<
                    cell_type_tt,
                    concat_type_tt,
                    size_tp,
                    formatter_tf,
                    parser_tf>& a_in_lhs,
                const moth::type::address::base_t<
                    cell_type_tt,
                    concat_type_tt,
                    size_tp,
                    formatter_tf,
                    parser_tf>& a_in_rhs)
{
    return 0 <= a_in_lhs.compare(a_in_rhs);
}

template<
    typename cell_type_tt,
    typename concat_type_tt,
    int size_tp,
    typename formatter_tf,
    typename parser_tf>
bool operator>=(const moth::type::address::base_t<
                    cell_type_tt,
                    concat_type_tt,
                    size_tp,
                    formatter_tf,
                    parser_tf>& a_in_lhs,
                const moth::type::address::base_t<
                    cell_type_tt,
                    concat_type_tt,
                    size_tp,
                    formatter_tf,
                    parser_tf>& a_in_rhs)
{
    return 0 >= a_in_lhs.compare(a_in_rhs);
}

template<
    typename cell_type_tt,
    typename concat_type_tt,
    int size_tp,
    typename formatter_tf,
    typename parser_tf>
bool operator==(const moth::type::address::base_t<
                        cell_type_tt,
                        concat_type_tt,
                        size_tp,
                        formatter_tf,
                        parser_tf>& a_in_lhs,
                const moth::type::address::base_t<
                        cell_type_tt,
                        concat_type_tt,
                        size_tp,
                        formatter_tf,
                        parser_tf>& a_in_rhs)
{
    return 0 == a_in_lhs.compare(a_in_rhs);
}

namespace boost
{
    template<
        typename cell_type_tt,
        typename concat_type_tt,
        int size_tp,
        typename formatter_tf,
        typename parser_tf>
    inline std::size_t hash_value(const moth::type::address::base_t<
                                            cell_type_tt,
                                            concat_type_tt,
                                            size_tp,
                                            formatter_tf,
                                            parser_tf>& a_in)
    {
        return a_in.hash_value();
    }
}

#endif // MOTH_INCLUDE_TYPE_ADDRESS_ADRESS_HPP
