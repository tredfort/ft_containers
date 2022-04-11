#ifndef TREE_ITERATOR_HPP
#define TREE_ITERATOR_HPP

#include "node.hpp"
#include "iterator_traits.hpp"

namespace ft {
    template <class T1, class T2, class Iter>
    class tree_iterator {
    public:
        typedef Iter iterator_type;
        typedef ft::bidirectional_iterator_tag iterator_category;
        typedef typename ft::iterator_traits<iterator_type>::value_type value_type;
        typedef typename ft::iterator_traits<iterator_type>::difference_type difference_type;
        typedef typename ft::iterator_traits<iterator_type>::pointer pointer;
        typedef typename ft::iterator_traits<iterator_type>::reference reference;
        typedef node<T1, T2>* nodePointer;

    private:
        nodePointer _ptr;

    public:
        tree_iterator(nodePointer ptr = 0) :_ptr(ptr) { }

        template<class U>
        tree_iterator(const tree_iterator<T1, T2, U>& other) :_ptr(other.base()) { }

        tree_iterator& operator=(const tree_iterator& other)
        {
            _ptr = other._ptr;
            return *this;
        }

        ~tree_iterator() { }

        nodePointer base() const { return _ptr; }

        bool operator==(const tree_iterator& other) const { return _ptr == other._ptr; }

        bool operator!=(const tree_iterator& other) const { return _ptr != other._ptr; }

        reference operator*() const { return *(_ptr->data); }

        pointer operator->() const { return _ptr->data; }

        tree_iterator& operator++()
        {
            _ptr = next(_ptr);
            return *this;
        }

        tree_iterator operator++(int)
        {
            tree_iterator tmp(*this);
            _ptr = next(_ptr);
            return tmp;
        }

        tree_iterator& operator--()
        {
            _ptr = prev(_ptr);
            return *this;
        }

        tree_iterator operator--(int)
        {
            tree_iterator tmp(*this);
            _ptr = prev(_ptr);
            return tmp;
        }

    private:
        nodePointer maximum(nodePointer node)
        {
            while (node->right->type != nilNode) {
                node = node->right;
            }
            return node;
        }

        nodePointer minimum(nodePointer node)
        {
            while (node->left->type != nilNode) {
                node = node->left;
            }
            return node;
        }

        nodePointer next(nodePointer node)
        {
            if (node->type == nilNode)
                return node;

            if (node->right->type != nilNode)
                return minimum(node->right);

            nodePointer ptr = node->parent;
            while (ptr->type != nilNode && node == ptr->right) {
                node = ptr;
                ptr = ptr->parent;
            }
            return ptr;
        }

        nodePointer prev(nodePointer node)
        {
            if (node->type == nilNode)
                return node->parent;

            if (node->type != nilNode && node->left->type != nilNode)
                return maximum(node->left);

            nodePointer ptr = node->parent;
            while (ptr->type != nilNode && node == ptr->left) {
                node = ptr;
                ptr = ptr->parent;
            }

            return ptr->type != nilNode ? ptr : node;
        }
    };
}
#endif
