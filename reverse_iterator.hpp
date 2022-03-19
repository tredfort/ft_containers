#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

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

		explicit reverse_iterator(const Iterator& other) : _base(other) { }

		reverse_iterator(const reverse_iterator& other) : _base(other.base()) { }

        template<typename U>
        reverse_iterator(const reverse_iterator<U>& other) : _base(other.base()) { }

		virtual ~reverse_iterator() { }

		iterator_type base() const { return _base; }

		reference operator*() const {
			iterator_type it(_base);
			--it;
			return *it;
		}

		pointer operator->() const { return &(operator*()); }

		reverse_iterator operator+(difference_type n) const { return reverse_iterator(_base - n); }

		reverse_iterator operator-(difference_type n) const { return reverse_iterator(_base + n); }

		reverse_iterator& operator++() {
			_base--;
			return *this;
		}

		reverse_iterator& operator--() {
			_base++;
			return *this;
		}

		reverse_iterator operator++(int) {
			reverse_iterator temp(*this);
			_base--;
			return temp;
		}

		reverse_iterator operator--(int) {
			reverse_iterator temp(*this);
			_base++;
			return temp;
		}

		reverse_iterator& operator+=(difference_type n) {
			_base -= n;
			return *this;
		}

		reverse_iterator& operator-=(difference_type n) {
			_base += n;
			return *this;
		}

		reference operator[](difference_type n) const { return (this->base()[-n - 1]); }
	};

	template <class Iterator>
	bool operator==(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
		return lhs.base() == rhs.base();
	}

	template <class Iterator>
	bool operator!=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
		return !operator==(lhs, rhs);
	}

	template <class Iterator>
	bool operator<(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
		return lhs.base() > rhs.base();
	}

	template <class Iterator>
	bool operator<=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
		return lhs.base() >= rhs.base();
	}

	template <class Iterator>
	bool operator>(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
		return lhs.base() < rhs.base();
	}

	template <class Iterator>
	bool operator>=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
		return lhs.base() <= rhs.base();
	}

	template <class Iterator>
	reverse_iterator<Iterator> operator+(
			typename reverse_iterator<Iterator>::difference_type n,
			const reverse_iterator<Iterator>& rev_it) { return rev_it + n; }

	template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type operator-(
			const reverse_iterator<Iterator>& lhs,
			const reverse_iterator<Iterator>& rhs) { return rhs.base() - lhs.base(); }
}

#endif
