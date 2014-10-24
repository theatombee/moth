#ifndef MOTH_INCLUDE_TYPE_ADDRESS_ADRESS_HPP
#define MOTH_INCLUDE_TYPE_ADDRESS_ADRESS_HPP
#include <stddef.h>
#include <cstddef>
#include "moth/reporter/reporter.hpp"

namespace moth
{
    namespace type
    {
        namespace address
        {
            template<typename T, typename N, int S>
            struct address_t
            {
                public:

                    enum
                    {
                        SIZE = S, CELL_SIZE = sizeof(T), NUM_OF_BYTES = (SIZE * CELL_SIZE),
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

                    address_t(const impl_t &a_in_that)
                    {
                        set(a_in_that);
                    }

                    address_t(concat_t const *a_in)
                    {
                        set(a_in);
                    }

                    address_t(const address_t &a_in_that)
                    {
                        set(a_in_that);
                    }

                    ///////////////////////////////////////////////////////////////////
                    // MUTATORS
                    ///////////////////////////////////////////////////////////////////

                    inline address_t &set(const impl_t &a_in_that)
                    {
                        memcpy(impl, a_in_that, NUM_OF_BYTES);
                        return *this;
                    }

                    inline address_t &set(concat_t const &a_in)
                    {
                        memcpy(impl, &a_in, NUM_OF_BYTES);
                        return *this;
                    }

                    inline address_t &set(const address_t &a_in)
                    {
                        set(a_in.impl);
                        return *this;
                    }

                    inline address_t operator=(const impl_t &a_in_that)
                    {
                        return set(a_in_that);
                    }

                    inline address_t operator=(concat_t const &a_in)
                    {
                        return set(a_in);
                    }

                    inline address_t operator=(const address_t &a_in)
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
                        memcpy(&a_out, impl, NUM_OF_BYTES);
                    }

                    inline void to_impl_t(impl_t &a_out) const
                    {
                        memcpy(a_out, impl, NUM_OF_BYTES);
                    }

                    cell_t compare(const address_t &a_in_that) const
                    {
                        cell_t l_diff = 0;
                        for (int i = 0; i < SIZE && !(l_diff = impl[i] - a_in_that.impl[i]); i++);
                        return l_diff;
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

#endif // MOTH_INCLUDE_TYPE_ADDRESS_ADRESS_HPP
