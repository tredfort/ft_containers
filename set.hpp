#ifndef SET_HPP
#define SET_HPP

#include "tree.hpp"
#include "set_iterator.hpp"
#include "reverse_iterator.hpp"

namespace ft {
    template<class Key,
            class Compare = std::less<Key>,
            class Allocator = std::allocator<Key>
    >
    class set {
    public:
        typedef Key key_type;
        typedef key_type value_type;
        typedef Compare key_compare;
        typedef key_compare value_compare;
        typedef Allocator allocator_type;
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::size_type size_type;
        typedef typename allocator_type::difference_type difference_type;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;
        typedef ft::set_iterator<Key, const value_type*> iterator;
        typedef ft::set_iterator<Key, const value_type*> const_iterator;
        typedef ft::reverse_iterator<iterator> reverse_iterator;
        typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

    private:
        tree<Key, bool, Compare, Allocator> _tree;
        key_compare _key_compare;
        allocator_type _alloc;

    public:

        set() :_tree(), _key_compare(key_compare()), _alloc(allocator_type()) { }

        set(
                const Compare& comp,
                const Allocator& alloc = allocator_type()
                        ) :_tree(), _key_compare(comp), _alloc(alloc) { }

        template< class InputIt >
        set(
                InputIt first,
                InputIt last,
                const Compare& comp = Compare(),
                const Allocator& alloc = allocator_type()
                    ) :_tree(), _key_compare(comp), _alloc(alloc) { insert(first, last); }

        set(const set& other) { *this = other; }


        ~set() { }

        set& operator=(const set& other)
        {
            if (this == &other)
                return *this;
            _tree = other._tree;
            _alloc = other._alloc;
            _key_compare = other._key_compare;
            return *this;
        }

        allocator_type get_allocator() const { return _alloc; }

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

        void clear() { _tree.clear(); }

        ft::pair<iterator, bool> insert(const value_type& value) { return _tree.insert(ft::pair<const value_type, bool>(value, true)); }

        iterator insert(iterator hint, const value_type& value)
        {
            (void) hint;
            return _tree.insert(ft::pair<value_type, bool>(value, true)).first;
        }

        template<class InputIterator>
        void insert(InputIterator first, InputIterator last)
        {
            for (; first!=last; ++first) {
                _tree.insert(ft::pair<value_type, bool>(*first, true));
            }
        }

        void erase(iterator pos) { _tree.erase(*pos); }

        void erase(iterator first, iterator last)
        {
            for (; first!=last;) {
                Key key = *first;
                ++first;
                _tree.erase(key);
            }
        }

        size_type erase(const key_type& key) { return _tree.erase(key) ? 1 : 0; }

        void swap(set& other)
        {
            _tree.swap(other._tree);
            std::swap(_alloc, other._alloc);
            std::swap(_key_compare, other._key_compare);
        }

        size_type count(const key_type& key) const { return (const_iterator(_tree.find(key)) != end()) ? 1 : 0; }

        iterator find(const key_type& key) { return iterator(_tree.find(key)); }

        const_iterator find(const key_type& key) const { return const_iterator(_tree.find(key)); }

        ft::pair<const_iterator, const_iterator> equal_range(const key_type& key) const {
            return ft::pair<const_iterator, const_iterator>(lower_bound(key), upper_bound(key));
        }

        ft::pair<iterator, iterator> equal_range(const key_type& key)
        {
            return ft::pair<iterator, iterator>(lower_bound(key), upper_bound(key));
        }

        iterator lower_bound(const key_type& key) { return iterator(_tree.lower_bound(key)); }

        const_iterator lower_bound(const key_type& key) const { return const_iterator(_tree.lower_bound(key)); }

        iterator upper_bound(const key_type& key) { return iterator(_tree.upper_bound(key)); }

        const_iterator upper_bound(const key_type& key) const { return const_iterator(_tree.upper_bound(key)); }

        key_compare key_comp() const { return _key_compare; }

        value_compare value_comp() const { return value_compare(Compare()); }

        friend bool operator==(
                const set<Key, Compare, Allocator>& lhs,
                const set<Key, Compare, Allocator>& rhs)
        {
            return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
        }

        friend bool operator!=(
                const set<Key, Compare, Allocator>& lhs,
                const set<Key, Compare, Allocator>& rhs)
        {
            return !(lhs==rhs);
        }

        friend bool operator<(
                const set<Key, Compare, Allocator>& lhs,
                const set<Key, Compare, Allocator>& rhs)
        {
            return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
        }

        friend bool operator<=(
                const set<Key, Compare, Allocator>& lhs,
                const set<Key, Compare, Allocator>& rhs)
        {
            return !(rhs<lhs);
        }

        friend bool operator>(
                const set<Key, Compare, Allocator>& lhs,
                const set<Key, Compare, Allocator>& rhs)
        {
            return rhs<lhs;
        }

        friend bool operator>=(
                const set<Key, Compare, Allocator>& lhs,
                const set<Key, Compare, Allocator>& rhs)
        {
            return !(lhs<rhs);
        }
    };
}

#endif
