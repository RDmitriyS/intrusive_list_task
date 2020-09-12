#pragma once

#include <type_traits>
#include <iterator>

namespace intrusive
{
    struct default_tag;

    template <typename Tag = default_tag>
    struct list_element
    {
        void unlink();
    };

    template <typename T, typename Tag = default_tag>
    struct list
    {
        struct iterator : public std::iterator<std::input_iterator_tag, int> {

            list_element<Tag> *it;

            explicit iterator(list_element<Tag> *it) : it(it) {}

            iterator() = default;

            iterator(const iterator &mit) : it(mit.it) {}

            iterator &operator++() {
                ++it;
                return *this;
            }

            iterator &operator--() {
                --it;
                return *this;
            }

            bool operator==(const iterator &rhs) const { return it == rhs.it; }

            bool operator!=(const iterator &rhs) const { return it != rhs.it; }

            Tag &operator*() { return *it; }
        };

        typedef const iterator const_iterator;

        iterator _begin;
        iterator _end;

        static_assert(std::is_convertible_v<T&, list_element<Tag>&>,
        "value type is not convertible to list_element");

        list() noexcept;
        list(list const&) = delete;
        list(list&&) noexcept;
        ~list();

        list& operator=(list const&) = delete;
        list& operator=(list&&) noexcept;

        void clear() noexcept;

        void push_back(T&) noexcept;
        void pop_back() noexcept;
        T& back() noexcept;
        T const& back() const noexcept;

        void push_front(T&) noexcept;
        void pop_front() noexcept;
        T& front() noexcept;
        T const& front() const noexcept;

        bool empty() const noexcept;

        iterator begin() noexcept;
        const_iterator begin() const noexcept;

        iterator end() noexcept;
        const_iterator end() const noexcept;

        iterator insert(const_iterator pos, T&) noexcept;
        iterator erase(const_iterator pos) noexcept;
        void splice(const_iterator pos, list&, const_iterator first, const_iterator last) noexcept;

    };

}
