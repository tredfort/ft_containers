#ifndef SET_ITERATOR_HPP
#define SET_ITERATOR_HPP

#include "iterator_traits.hpp"
#include "node.hpp"

namespace ft {
    template <class T, class Iter>
    class set_iterator {
    public:
        typedef Iter iterator_type;
        typedef ft::bidirectional_iterator_tag iterator_category;
        typedef typename ft::iterator_traits<iterator_type>::value_type value_type;
        typedef typename ft::iterator_traits<iterator_type>::difference_type difference_type;
        typedef typename ft::iterator_traits<iterator_type>::pointer pointer;
        typedef typename ft::iterator_traits<iterator_type>::reference reference;

    private:
        typedef node<T, bool>* nodePointer;
        nodePointer _ptr;

    public:
        set_iterator(nodePointer ptr = 0) : _ptr(ptr) { }

        template<class U>
        set_iterator(const set_iterator<T, U>& other) :_ptr(other.base()) { }

        set_iterator& operator=(const set_iterator& other)
        {
            if (this == &other)
                return *this;
            _ptr = other._ptr;
            return *this;
        }

        ~set_iterator() { }

        nodePointer base() const { return _ptr; }

        bool operator==(const set_iterator& other) const { return _ptr == other.base(); }

        bool operator!=(const set_iterator& other) const { return _ptr != other.base(); }

        reference operator*() const { return _ptr->data->first; }

        pointer operator->() const { return &_ptr->data->first; }

        set_iterator& operator++()
        {
            _ptr = next(_ptr);
            return *this;
        }

        set_iterator operator++(int)
        {
            set_iterator tmp(*this);
            _ptr = next(_ptr);
            return tmp;
        }

        set_iterator& operator--()
        {
            _ptr = prev(_ptr);
            return *this;
        }

        set_iterator operator--(int)
        {
            set_iterator tmp(*this);
            _ptr = prev(_ptr);
            return tmp;
        }

    private:
        nodePointer maximum(nodePointer node)
        {
            while (node->right->type != nil_node) {
                node = node->right;
            }
            return node;
        }

        nodePointer minimum(nodePointer node)
        {
            while (node->left->type != nil_node) {
                node = node->left;
            }
            return node;
        }

        nodePointer next(nodePointer node)
        {
            if (node->type == nil_node)
                return node;

            if (node->right->type != nil_node)
                return minimum(node->right);

            nodePointer ptr = node->parent;
            while (ptr->type != nil_node && node == ptr->right) {
                node = ptr;
                ptr = ptr->parent;
            }
            return ptr;
        }

        nodePointer prev(nodePointer node)
        {
            if (node->type == nil_node)
                return node->parent;

            if (node->type != nil_node && node->left->type != nil_node)
                return maximum(node->left);

            nodePointer ptr = node->parent;
            while (ptr->type != nil_node && node == ptr->left) {
                node = ptr;
                ptr = ptr->parent;
            }

            return ptr->type != nil_node ? ptr : node;
        }
    };
}

#endif
