#ifndef VECTOR_ITERATOR_HPP
#define VECTOR_ITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft {
	template <typename Iterator>
	class vector_iterator {
	public:
        typedef Iterator iterator_type;
        typedef typename ft::iterator_traits<iterator_type>::iterator_category iterator_category;
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

		vector_iterator& operator=(const vector_iterator& other) {
			if (this != &other)
    			_ptr = other._ptr;
			return *this;
		}

		vector_iterator& operator-=(difference_type n) {
			_ptr -= n;
			return *this;
		}

		vector_iterator& operator+=(difference_type n) {
			_ptr += n;
			return *this;
		}

		vector_iterator operator-(difference_type n) const { return _ptr - n; }

		vector_iterator operator+(difference_type n) const { return _ptr + n; }

		vector_iterator& operator++() {
			_ptr++;
			return *this;
		}

		vector_iterator& operator--() {
			_ptr--;
			return *this;
		}

		vector_iterator operator++(int) {
			vector_iterator tmp(*this);
			_ptr++;
			return tmp;
		}

		vector_iterator operator--(int) {
			vector_iterator tmp(*this);
			_ptr--;
			return tmp;
		}

		reference operator*() { return *_ptr; }

		pointer operator->() { return _ptr; }

		reference operator[](difference_type n) const { return *(_ptr + n); }

		bool operator==(const vector_iterator& other) const { return _ptr == other._ptr; }

		bool operator!=(const vector_iterator& other) const { return _ptr != other._ptr; }

		bool operator>(const vector_iterator& other) const { return _ptr > other._ptr; }

		bool operator<(const vector_iterator& other) const { return _ptr < other._ptr; }

		bool operator>=(const vector_iterator& other) const { return _ptr >= other._ptr; }

		bool operator<=(const vector_iterator& other) const { return _ptr <= other._ptr; }
	};

	template <typename T>
	vector_iterator<T> operator+(size_t n, const vector_iterator<T> &iter) { return iter + n; }

	template <typename T>
	ptrdiff_t operator-(const vector_iterator<T> &lhi, const vector_iterator<T> &rhi) { return lhi.base() - rhi.base(); }
}

#endif
