#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "utility.hpp"
#include <memory>
#include <iostream>
#include "vector_iterator.hpp"
#include "reverse_iterator.hpp"

namespace ft {

    template<class T, class Alloc = std::allocator<T> >
    class vector {

    public:
        typedef T value_type;
        typedef Alloc allocator_type;
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;
        typedef typename allocator_type::difference_type difference_type;
        typedef typename allocator_type::size_type size_type;
        typedef ft::vector_iterator<pointer> iterator;
        typedef ft::vector_iterator<const_pointer> const_iterator;
        typedef ft::reverse_iterator<iterator> reverse_iterator;
        typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

    private:
        allocator_type _alloc;
        pointer _ptr;
        size_type _size;
        size_type _cap;

    public:
        explicit vector(const allocator_type& alloc = allocator_type()) :_alloc(alloc), _ptr(0), _size(0), _cap(0) { }

        explicit vector(size_type n, const value_type& value = value_type(),
                        const allocator_type& alloc = allocator_type())
                :_alloc(alloc), _ptr(0), _size(0), _cap(0) { assign(n, value); }

        template<class InputIterator>
        vector(InputIterator first,
                typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type last,
                const allocator_type& alloc = allocator_type())
                :_alloc(alloc), _ptr(0), _size(0), _cap(0) { assign(first, last); }

        vector(const vector& other) :_alloc(other._alloc), _ptr(0), _size(0), _cap(0) { assign(other.begin(), other.end()); }

        ~vector()
        {
            clear();
            _alloc.deallocate(_ptr, _cap);
        }

        vector& operator=(const vector& other)
        {
            if (this == &other)
                return *this;
            clear();
            insert(begin(), other.begin(), other.end());
            return *this;
        }

        iterator begin() { return iterator(_ptr); }

        const_iterator begin() const { return const_iterator(_ptr); }

        iterator end() { return iterator(_ptr + _size); }

        const_iterator end() const { return const_iterator(_ptr + _size); }

        reverse_iterator rbegin() { return reverse_iterator(_ptr + _size); }

        const_reverse_iterator rbegin() const { return const_reverse_iterator(_ptr + _size); }

        reverse_iterator rend() { return reverse_iterator(_ptr); }

        const_reverse_iterator rend() const { return const_reverse_iterator(_ptr); }

        size_type size() const { return _size; }

        size_type max_size() const { return _alloc.max_size(); }

        void resize(size_type n, value_type value = value_type())
        {
            if (_size > n) {
                for (; _size > n; --_size)
                    _alloc.destroy(_ptr + _size - 1);
            }
            else {
                if (!_cap || n > 2 * _cap)
                    reserve(n);
                else if (n > _cap)
                    reserve(_cap * 2);
                for (; _size < n; ++_size)
                    _alloc.construct(_ptr + _size, value);
            }
        }

        size_type capacity() const { return _cap; }

        bool empty() const { return _size == 0; }

        void reserve(size_type n)
        {
            if (n > _cap) {
                check_max_size(n);
                pointer new_ptr;
                size_type new_cap = n;
                size_type new_size = 0;
                try {
                    new_ptr = _alloc.allocate(new_cap);
                    for (; new_size < _size; ++new_size)
                        _alloc.construct(new_ptr + new_size, *(_ptr + new_size));
                    for (size_type i = 0; i < _size; ++i)
                        _alloc.destroy(_ptr + i);
                    replacement(new_ptr, new_size, new_cap);
                } catch (...) {
                    clear(new_ptr, new_size, new_cap);
                }
            }
        }

        reference operator[](size_type n) { return *(_ptr + n); }

        const_reference operator[](size_type n) const { return *(_ptr + n); }

        reference at(size_type n)
        {
            check_range(n);
            return *(_ptr + n);
        }

        const_reference at(size_type n) const
        {
        	check_range(n);
        	return *(_ptr + n);
        }

        reference front() { return *_ptr; }

        const_reference front() const { return *_ptr; }

        reference back() { return *(_ptr + _size - 1); }

        const_reference back() const { return *(_ptr + _size - 1); }

        template<class InputIterator>
        void assign(
                InputIterator first,
                typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type last)
        {
            clear();
            reserve(ft::distance(first, last));
            insert(begin(), first, last);
        }

        void assign(size_type n, const value_type& value)
        {
            clear();
            reserve(n);
            insert(begin(), n, value);
        }

        void push_back(const value_type& value)
        {
            if (_size == _cap)
                resize(_size + 1, value);
            else
                _alloc.construct(_ptr + _size++, value);
        }

        void pop_back()
        {
            --_size;
            _alloc.destroy(_ptr + _size);
        }

        iterator insert(iterator position, const value_type& value)
        {
        	size_type pos = ft::distance(begin(), position);
            insert(position, 1, value);
            return iterator(_ptr + pos);
        }

        //TODO: вместо вызова оператора =, создавать объекты через конструктор копирования
        void insert(iterator position, size_type n, const value_type& value)
        {
            size_type pos = ft::distance(begin(), position);
            size_type new_size = 0;
            size_type new_cap;
            pointer new_ptr;

            if (_size + n > _cap) {
                new_cap = !_cap ? n : _cap * 2 < n + _size ? _size + n : _cap * 2;
                check_max_size(new_cap);
                try {
                    new_ptr = _alloc.allocate(new_cap);
                    for (; new_size < n; ++new_size)
                        _alloc.construct(new_ptr + pos + new_size, value);
                    move(new_ptr, _ptr, pos, new_size);
                    move(new_ptr + pos + n, _ptr + pos, ft::distance(position, end()), new_size);
                    replacement(new_ptr, new_size, new_cap);
                } catch (...) {
                    clear(new_ptr + pos, new_size, new_cap);
                    throw;
                }
            } else {
                move_reverse(_ptr + _size - 1 + n, _ptr + _size - 1, ft::distance(position, end()));
                for (size_type i = 0; i < n; ++i, ++_size)
                    _alloc.construct(_ptr + pos + i, value);
            }
        }

        //TODO: вместо вызова оператора =, создавать объекты через конструктор копирования
        template<class InputIterator>
        void insert(
                iterator position,
                InputIterator first,
                typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type last) {
            size_type n = ft::distance(first, last);
            size_type pos = ft::distance(begin(), position);
            size_type new_size(0);
            size_type new_cap(0);
            pointer new_ptr(0);

            if (_size + n > _cap) {
                new_cap = _cap == 0 ? n : _cap * 2 < _size + n ? _size + n : _cap * 2;
                check_max_size(new_cap);
                try {
                    new_ptr = _alloc.allocate(new_cap);
                    for (; new_size < n; ++new_size, ++first)
                        _alloc.construct(new_ptr + pos + new_size, *first);
                    move(new_ptr, _ptr, pos, new_size);
                    move(new_ptr + pos + n, _ptr + pos, end() - position, new_size);
                    replacement(new_ptr, new_size, new_cap);
                } catch (...) {
                    clear(new_ptr, new_size, new_cap);
                    throw;
                }
            } else {
                move_reverse(_ptr + _size - 1 + n, _ptr + _size - 1, end() - position);
                for (size_type i = 0; i < n; ++i, ++_size, ++first)
                    _alloc.construct(_ptr + pos + i, *first);
            }
        }

        iterator erase(iterator position) { return erase(position, position + 1); }

        iterator erase(iterator first, iterator last)
        {
            size_type n = ft::distance(first, last);
            for (size_type i = 0; i < n; ++i) {
                _alloc.destroy(first.base() + i);
            }
            for (size_type i = 0, remains = ft::distance(last, end()); i < remains; ++i) {
                *(first.base() + i) = *(last.base() + i);
            }
            _size -= n;
            return first;
        }

        void swap(vector& other)
        {
            std::swap(_alloc, other._alloc);
            std::swap(_ptr, other._ptr);
            std::swap(_size, other._size);
            std::swap(_cap, other._cap);
        }

        void clear()
        {
            for (; _size > 0; --_size)
                _alloc.destroy(_ptr + _size - 1);
        }

        allocator_type get_allocator() const { return _alloc; }

        pointer data() { return _ptr; }

    private:
        void check_max_size(size_type n)
        {
            if (n > max_size())
                throw std::length_error("vector");
        }

        void check_range(size_type n) const
        {
            if (n > size())
                throw std::out_of_range("vector");
        }

        void replacement(pointer new_ptr, size_type new_size, size_type new_cap)
        {
            _alloc.deallocate(_ptr, _cap);
            _size = new_size;
            _cap = new_cap;
            _ptr = new_ptr;
        }

        void clear(pointer new_ptr, size_type new_size, size_type new_cap)
        {
            for (; new_size > 0; --new_size)
                _alloc.destroy(new_ptr + new_size - 1);
            _alloc.deallocate(new_ptr, new_cap);
        }

        void move(pointer dst, pointer src, size_type n, size_type& new_size)
        {
            for (size_type i = 0; i < n; ++i, ++new_size)
                *(dst + i) = *(src + i);
        }

        void move_reverse(pointer dst, pointer src, size_type n)
        {
            for (size_type i = 0; i < n; ++i)
                *(dst - i) = *(src - i);
        }
    };

    template<class T, class Alloc>
    bool operator==(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
    {
        if (lhs.size() != rhs.size())
            return false;

        typename vector<T, Alloc>::const_iterator it1 = lhs.begin();
        typename vector<T, Alloc>::const_iterator it2 = rhs.begin();

        for (; it1 != lhs.end(); ++it1, ++it2)
            if (*it1 != *it2)
                return false;
        return true;
    }

    template<class T, class Alloc>
    bool operator!=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) { return !(lhs == rhs); }

    template<class T, class Alloc>
    bool operator<(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
    {
        typename vector<T, Alloc>::const_iterator it1 = lhs.begin();
        typename vector<T, Alloc>::const_iterator it2 = rhs.begin();

        for (; it1 != lhs.end(); ++it1, ++it2) {
            if (it2 == rhs.end() || *it2 < *it1)
                return false;
            else if (*it1 < *it2)
                return true;
        }
        return it2 != rhs.end();
    }

    template<class T, class Alloc>
    bool operator<=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) { return !(rhs < lhs); }

    template<class T, class Alloc>
    bool operator>(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) { return rhs < lhs; }

    template<class T, class Alloc>
    bool operator>=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) { return !(lhs < rhs); }

    template<class T, class Alloc>
    void swap(vector<T, Alloc>& x, vector<T, Alloc>& y) { x.swap(y); }
}

#endif
