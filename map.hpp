#ifndef MAP_HPP
#define MAP_HPP

#include "utility.hpp"
#include "reverse_iterator.hpp"
#include "tree.hpp"
#include "node.hpp"
#include "tree_iterator.hpp"

namespace ft {
	template< class Key,
			class T,
			class Compare = std::less<Key>,
			class Alloc = std::allocator<ft::pair<const Key, T> >
	>
	class map {
	public:
		typedef Key key_type;
		typedef T mapped_type;
        typedef ft::pair<const Key, T> value_type;
		typedef Compare key_compare;
        typedef tree<const Key, T, Compare, Alloc> tree_type;
		typedef Alloc allocator_type;
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;
        typedef typename allocator_type::size_type size_type;
        typedef typename allocator_type::difference_type difference_type;

//        typedef ft::tree_iterator<const key_type, mapped_type, pointer> iterator;
//        typedef ft::tree_iterator<const key_type, mapped_type, const_pointer> const_iterator;

        typedef typename tree_type::iterator iterator;
        typedef typename tree_type::const_iterator const_iterator;

        typedef ft::reverse_iterator<iterator> reverse_iterator;
        typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

        class value_compare : public std::binary_function<value_type, value_type, bool> {
            friend class map;
        protected:
            key_compare _comp;
            value_compare(key_compare c) :_comp(c) { }

        public:
            bool operator()(const value_type& x, const value_type& y) const
            {
                return _comp(x.first, y.first);
            }
        };

	private:
        tree_type _tree;
		key_compare _key_compare;
		allocator_type _alloc;

	public:
		explicit map(
				const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type()
		)
				:_tree(), _key_compare(comp), _alloc(alloc) { }

		template< class InputIterator >
		map(
                InputIterator first,
				InputIterator last,
				const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type()
		)
				:
				_tree(), _key_compare(comp), _alloc(alloc) { insert(first, last); }

		map(const map& other) { *this = other; }

		~map() { }

		map& operator=(const map& other)
		{
			_tree = other._tree;
			return *this;
		}

		iterator begin() { return iterator(_tree.begin()); }

		const_iterator begin() const { return const_iterator(_tree.begin()); }

		iterator end() { return iterator(_tree.end()); }

        const_iterator end() const { return const_iterator(_tree.end()); }

		reverse_iterator rbegin() { return reverse_iterator(_tree.end()); }

        const_reverse_iterator rbegin() const { return reverse_iterator(_tree.end()); }

		reverse_iterator rend() { return reverse_iterator(_tree.begin()); }

        const_reverse_iterator rend() const { return reverse_iterator(_tree.begin()); }

		bool empty() const { return _tree.size() == 0; }

		size_type size() const { return _tree.size(); }

		size_type max_size() const { return _tree.max_size(); }

		mapped_type& operator[](const key_type& k)
		{
			ft::pair<iterator, bool> res = insert(ft::pair<Key, mapped_type>(k, _tree.search(k)->data->second));
			return res.first->second;
		}

		ft::pair<iterator, bool> insert(const value_type& val) { return _tree.insert(val); }

		iterator insert(iterator hint, const value_type& val)
		{
            (void) hint;
            return _tree.insert(val).first;
		}

		template< class InputIterator >
		void insert(InputIterator first, InputIterator last)
		{
            for (; first!=last; ++first) {
                _tree.insert(first);
            }
		}
		void erase(iterator position) { _tree.erase(position->first); }

		size_type erase(const key_type& key) { return _tree.erase(key) ? 1 : 0; }

        void erase(iterator first, iterator last)
		{
            while (first!=last) {
                Key key = first->first;
                ++first;
                _tree.erase(key);
            }
		}

		void swap(map& other) { _tree.swap(other._tree); }

		void clear() { _tree.clear(); }

		key_compare key_comp() const { return _key_compare; }

		value_compare value_comp() const { return value_compare(Compare()); }

		iterator find(const key_type& key) { return iterator(_tree.search(key)); }

        const_iterator find(const key_type& key) const { return const_iterator(_tree.search(key)); }

		mapped_type& at(const Key& key)
		{
			iterator it = find(key);
			if (it==end()) {
				throw std::out_of_range("map");
			}
			return it->second;
		}

		const mapped_type& at(const Key& key) const
		{
			iterator it = find(key);
			if (it==end()) {
				throw std::out_of_range("map");
			}
			return it->second;
		}

		size_type count(const key_type& key) const { return (const_iterator(_tree.search(key)) != end()) ? 1 : 0; }

		iterator lower_bound(const key_type& key) { return iterator(_tree.lower_bound(key)); }

		const_iterator lower_bound(const key_type& key) const { return const_iterator(_tree.lower_bound(key)); }

		iterator upper_bound(const key_type& key) { return iterator(_tree.upper_bound(key)); }

		const_iterator upper_bound(const key_type& key) const { return const_iterator(_tree.upper_bound(key)); }

		ft::pair<const_iterator, const_iterator> equal_range(const key_type& key) const {
            return ft::pair<const_iterator, const_iterator>(lower_bound(key), upper_bound(key));
        }

        ft::pair<iterator, iterator> equal_range(const key_type& key) {
            return ft::pair<iterator, iterator>(lower_bound(key), upper_bound(key));
        }

		allocator_type get_allocator() const { return _alloc; }

		friend bool operator==(
                const map<Key, T, Compare, Alloc>& lhs,
				const map<Key, T, Compare, Alloc>& rhs
                )
		{
			if (lhs.size()!=rhs.size())
				return false;
			return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
		}

		friend bool operator!=(
                const map<Key, T, Compare, Alloc>& lhs,
				const map<Key, T, Compare, Alloc>& rhs
                )
                { return !(lhs==rhs); }

		friend bool operator<(
                const map<Key, T, Compare, Alloc>& lhs,
				const map<Key, T, Compare, Alloc>& rhs
                )
		{
			const_iterator lb = lhs.begin();
			const_iterator le = lhs.end();
			const_iterator rb = rhs.begin();
			const_iterator re = rhs.end();
			return ft::lexicographical_compare(lb, le, rb, re);
		}

		friend bool operator<=(
                const map<Key, T, Compare, Alloc>& lhs,
				const map<Key, T, Compare, Alloc>& rhs
                )
                { return !(rhs<lhs); }

		friend bool operator>(
                const map<Key, T, Compare, Alloc>& lhs,
				const map<Key, T, Compare, Alloc>& rhs
                )
		{ return rhs<lhs; }

		friend bool operator>=(
                const map<Key, T, Compare, Alloc>& lhs,
				const map<Key, T, Compare, Alloc>& rhs
                )
		{ return !(lhs<rhs); }
	};
}
#endif
