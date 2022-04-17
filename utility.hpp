#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <cstddef>
#include <iostream>
#include "iterator_traits.hpp"

namespace ft {
	template <class T, class A>
	class vector;

	template <class Key, class T, class Compare, class A>
	class map;

    template <class Key, class Compare, class A>
    class set;

	template<class T, bool v>
	struct integral_constant {
		static const bool value = v;
		typedef T value_type;
		typedef integral_constant type;
		operator value_type() const { return value; }
	};
	template <class T> struct is_integral : public ft::integral_constant<T, false> {};
	template <> struct is_integral<bool> : public ft::integral_constant<bool, true> {};
	template <> struct is_integral<char> : public ft::integral_constant<bool, true> {};
	template <> struct is_integral<signed char> : public integral_constant<bool, true> {};
	template <> struct is_integral<unsigned char> : public integral_constant<bool, true> {};
	template <> struct is_integral<wchar_t> : public integral_constant<bool, true> {};
	template <> struct is_integral<char16_t> : public integral_constant<bool, true> {};
	template <> struct is_integral<short> : public integral_constant<bool, true> {};
	template <> struct is_integral<unsigned short> : public integral_constant<bool, true> {};
	template <> struct is_integral<int> : public integral_constant<bool, true> {};
	template <> struct is_integral<unsigned int> : public integral_constant<bool, true> {};
	template <> struct is_integral<long> : public integral_constant<bool, true> {};
	template <> struct is_integral<unsigned long> : public integral_constant<bool, true> {};
	template <> struct is_integral<long long> : public integral_constant<bool, true> {};
	template <> struct is_integral<unsigned long long> : public integral_constant<bool, true> {};

	template<bool B, class T = void> struct enable_if {};
	template<class T> struct enable_if<true, T> { typedef T type; };

template< class InputIt1, class InputIt2 >
	bool equal( InputIt1 first1, InputIt1 last1, InputIt2 first2 )
	{
		for (; first1 != last1; ++first1, ++first2) {
			if (*first1 != *first2) {
				return false;
			}
		}
		return true;
	}

template< class InputIt1, class InputIt2, class BinaryPredicate >
	bool equal( InputIt1 first1, InputIt1 last1,
				InputIt2 first2, BinaryPredicate p)
	{
		for (; first1 != last1; ++first1, ++first2) {
			if (!p(*first1, *first2)) {
				return false;
			}
		}
		return true;
	}

	template<class InputIt1, class InputIt2>
	bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2)
	{
		for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 ) {
			if (*first1 < *first2) return true;
			if (*first2 < *first1) return false;
		}
		return (first1 == last1) && (first2 != last2);
	}

	template <class T1, class T2>
	struct pair {
		typedef T1 first_type;
		typedef T2 second_type;
        first_type first;
        second_type second;

		pair() : first(), second() {}

        template <class U1, class U2>
        pair(const pair<U1, U2>& p) : first(p.first), second(p.second) {}

        pair(const first_type& k, const second_type& v) : first(k), second(v) { };

		pair& operator=(const pair& other) {
			if (this == &other)
                return *this;
            first = other.first;
			second = other.second;
			return *this;
		}

		void swap(pair& p)
		{
			std::swap(first,  p.first);
			std::swap(second, p.second);
		}
	};

	template <class T1, class T2>
	inline bool operator==(const pair<T1, T2>& x, const pair<T1, T2>& y)
	{
		return x.first == y.first && x.second == y.second;
	}

	template <class T1, class T2>
	inline bool operator!=(const pair<T1, T2>& x, const pair<T1, T2>& y)
	{
		return !(x == y);
	}

	template <class T1, class T2>
	inline bool operator< (const pair<T1, T2>& x, const pair<T1, T2>& y)
	{
		return x.first < y.first || (!(y.first < x.first) && x.second < y.second);
	}

	template <class T1, class T2>
	inline bool operator> (const pair<T1, T2>& x, const pair<T1, T2>& y) { return y < x; }

	template <class T1, class T2>
	inline bool operator>=(const pair<T1, T2>& x, const pair<T1, T2>& y) { return !(x < y); }

	template <class T1, class T2>
	inline bool operator<=(const pair<T1, T2>& x, const pair<T1, T2>& y) { return !(y < x); }

	template <class T1, class T2>
	inline pair<T1, T2> make_pair(T1 x, T2 y) { return pair<T1, T2>(x, y); }

    template <class InputIter>
    typename std::iterator_traits<InputIter>::difference_type
    distance(InputIter first, InputIter last, std::input_iterator_tag)
    {
        typename std::iterator_traits<InputIter>::difference_type r(0);
        for (; first != last; ++first)
            ++r;
        return r;
    }

    template <class RandIter>
    typename std::iterator_traits<RandIter>::difference_type
    distance(RandIter first, RandIter last, std::random_access_iterator_tag)
    {
        return last - first;
    }

    template <class InputIter>
    typename ft::iterator_traits<InputIter>::difference_type
    distance(InputIter first, InputIter last, ft::input_iterator_tag)
    {
        typename ft::iterator_traits<InputIter>::difference_type r(0);
        for (; first != last; ++first)
            ++r;
        return r;
    }

    template <class RandIter>
    typename ft::iterator_traits<RandIter>::difference_type
    distance(RandIter first, RandIter last, ft::random_access_iterator_tag)
    {
        return last - first;
    }

    template <class InputIter>
    typename ft::iterator_traits<InputIter>::difference_type
    distance(InputIter first, InputIter last)
    {
        return distance(first, last, typename ft::iterator_traits<InputIter>::iterator_category());
    }
}

namespace std {
	template <class T, class A>
	void swap(ft::vector<T, A>& v1, ft::vector<T, A>& v2 ) { v1.swap(v2); }

	template <class Key, class T, class Compare, class A>
	void swap(ft::map<Key, T, Compare, A>& m1, ft::map<Key, T, Compare, A>& m2 ) { m1.swap(m2); }

    template<class Key, class Compare, class A>
    void swap(ft::set<Key, Compare, A>& s1, ft::set<Key, Compare, A>& s2) { s1.swap(s2); }
}

#endif