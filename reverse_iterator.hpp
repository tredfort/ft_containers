#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft {
    template<class Iterator>
    class reverse_iterator {
    public:
        typedef Iterator iterator_type;
        typedef typename ft::iterator_traits<iterator_type>::iterator_category iterator_category;
        typedef typename ft::iterator_traits<iterator_type>::value_type value_type;
        typedef typename ft::iterator_traits<iterator_type>::difference_type difference_type;
        typedef typename ft::iterator_traits<iterator_type>::pointer pointer;
        typedef typename ft::iterator_traits<iterator_type>::reference reference;

    private:
        iterator_type _base;

    public:
        reverse_iterator() { }

        reverse_iterator(const Iterator& other) :_base(other.base()) { }

        reverse_iterator(const reverse_iterator& other) :_base(other.base()) { }

        template<typename U>
        reverse_iterator(const reverse_iterator<U>& other) :_base(other.base()) { }

        virtual ~reverse_iterator() { }

        iterator_type base() const { return _base; }

        reference operator*() const
        {
            iterator_type it(_base);
            --it;
            return *it;
        }

        pointer operator->() const { return &(operator*()); }

        reverse_iterator operator+(difference_type n) const { return reverse_iterator(_base-n); }

        reverse_iterator operator-(difference_type n) const { return reverse_iterator(_base+n); }

        reverse_iterator& operator++()
        {
            _base--;
            return *this;
        }

        reverse_iterator& operator--()
        {
            _base++;
            return *this;
        }

        reverse_iterator operator++(int)
        {
            reverse_iterator temp(*this);
            _base--;
            return temp;
        }

        reverse_iterator operator--(int)
        {
            reverse_iterator temp(*this);
            _base++;
            return temp;
        }

        reverse_iterator& operator+=(difference_type n)
        {
            _base -= n;
            return *this;
        }

        reverse_iterator& operator-=(difference_type n)
        {
            _base += n;
            return *this;
        }

        reference operator[](difference_type n) const { return (this->base()[-n-1]); }

        template <class U>
        bool operator==(const reverse_iterator<U>& other) const { return _base == other.base(); };

        template <class U>
        bool operator!=(const reverse_iterator<U>& other) const { return _base != other.base(); };

        template <class U>
        bool operator<(const reverse_iterator<U>& other) const { return _base >  other.base(); };

        template <class U>
        bool operator<=(const reverse_iterator<U>& other) const { return _base >= other.base(); };

        template <class U>
        bool operator>(const reverse_iterator<U>& other) const { return _base <  other.base(); };

        template <class U>
        bool operator>=(const reverse_iterator<U>& other) const { return _base <= other.base(); };

        template <class U>
        difference_type operator-(const reverse_iterator<U>& other) { return other.base() - _base; };

        friend reverse_iterator operator+(difference_type n, const reverse_iterator& other) { return other + n; };
    };
}

#endif
