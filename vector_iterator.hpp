#ifndef VECTOR_ITERATOR_HPP
#define VECTOR_ITERATOR_HPP

#include "utility.hpp"

namespace ft {
	template <typename Iterator>
	class vector_iterator {
	public:
        typedef Iterator iterator_type;
        typedef typename ft::random_access_iterator_tag iterator_category;
        typedef typename ft::iterator_traits<iterator_type>::value_type value_type;
        typedef typename ft::iterator_traits<iterator_type>::difference_type difference_type;
        typedef typename ft::iterator_traits<iterator_type>::pointer pointer;
        typedef typename ft::iterator_traits<iterator_type>::reference reference;

    private:
        pointer _ptr;

    public:
		vector_iterator(pointer ptr = 0) : _ptr(ptr) { }

		template<class U>
		vector_iterator(const vector_iterator<U>& other) : _ptr(other.base()) {}

		virtual ~vector_iterator() { }

        pointer base() const { return _ptr; }

		vector_iterator& operator=(const vector_iterator& other)
		{
			if (this == &other)
                return *this;
            _ptr = other._ptr;
			return *this;
		}

		vector_iterator& operator-=(difference_type n)
		{
			_ptr -= n;
			return *this;
		}

		vector_iterator& operator+=(difference_type n)
		{
			_ptr += n;
			return *this;
		}

		vector_iterator operator-(difference_type n) const { return _ptr - n; }

        template <typename T>
        ptrdiff_t operator-(const vector_iterator<T>& it) { return this->base() - it.base(); }

		vector_iterator operator+(difference_type n) const { return _ptr + n; }

		vector_iterator& operator++()
		{
			_ptr++;
			return *this;
		}

		vector_iterator& operator--()
		{
			_ptr--;
			return *this;
		}

		vector_iterator operator++(int)
		{
			vector_iterator tmp(*this);
			_ptr++;
			return tmp;
		}

		vector_iterator operator--(int)
		{
			vector_iterator tmp(*this);
			_ptr--;
			return tmp;
		}

		reference operator*() { return *_ptr; }

		pointer operator->() { return _ptr; }

		reference operator[](difference_type n) const { return *(_ptr + n); }

        template <typename T>
		bool operator==(const vector_iterator<T>& other) const { return _ptr == other.base(); }

        template <typename T>
		bool operator!=(const vector_iterator<T>& other) const { return _ptr != other.base(); }

        template <typename T>
		bool operator>(const vector_iterator<T>& other) const { return _ptr > other.base(); }

        template <typename T>
		bool operator<(const vector_iterator<T>& other) const { return _ptr < other.base(); }

        template <typename T>
		bool operator>=(const vector_iterator<T>& other) const { return _ptr >= other.base(); }

        template <typename T>
		bool operator<=(const vector_iterator<T>& other) const { return _ptr <= other.base(); }
	};

	template <typename T>
	vector_iterator<T> operator+(size_t n, const vector_iterator<T> &iter) { return iter + n; }

	template <typename T>
	ptrdiff_t operator-(const vector_iterator<T>& lhi, const vector_iterator<T>& rhi) { return lhi.base() - rhi.base(); }
}

#endif
