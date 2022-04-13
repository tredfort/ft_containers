#ifndef TREE_HPP
#define TREE_HPP

#include "node.hpp"

namespace ft {
	template<class T1, class T2, class Compare, class Alloc>
	class tree {
	public:
        typedef T1 key_type;
        typedef T2 mapped_type;
        typedef Compare key_compare;
        typedef typename Alloc::template rebind< node<T1, T2> >::other allocator_type;
        typedef typename allocator_type::value_type value_type;
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;
        typedef typename allocator_type::size_type size_type;
        typedef typename allocator_type::difference_type difference_type;

    private:
		allocator_type _alloc;
        key_compare _cmp;
        pointer _head;
        pointer _nil;
		size_type _size;

    public:
        tree() : _alloc(), _cmp(key_compare()), _head(_alloc.allocate(1)), _nil(_head), _size(0)
        {
            _alloc.construct(_nil, value_type(key_type(), mapped_type(), NULL, nilNode));
        }

        ~tree()
        {
        	clear(_head);
            free_node(_nil);
        }

        tree& operator=(const tree& other)
        {
            if (this != &other) {
                clear();
                _cmp = other._cmp;
                for (pointer ptr = other.begin(); ptr != other.end(); ptr = next(ptr)) {
					insert(*ptr->data);
                }
            }
            return *this;
        }

        pointer begin() { return minimum(_head); }

        pointer begin() const { return minimum(_head); }

        pointer end() { return _nil; }

        pointer end() const { return _nil; }

		size_type size() const { return _size; }

		size_type max_size() const { return _alloc.max_size(); }

        void clear() { clear(_head); }

		ft::pair<pointer, bool> insert(ft::pair<key_type, mapped_type> pair) { return _add(pair.first, pair.second); }

		bool erase(key_type key)
		{
        	pointer node = find(_head, key);
        	if (node == _nil)
        		return false;
			delete_node(node);
        	--_size;
        	return true;
		}

		void swap(tree& other)
		{
			std::swap(_nil, other._nil);
			std::swap(_head, other._head);
			std::swap(_cmp, other._cmp);
			std::swap(_alloc, other._alloc);
			std::swap(_size, other._size);
		}

        pointer find(key_type key) const { return find(_head, key); }

		pointer lower_bound(const key_type key) const
		{
			if (_head != _nil)
			{
				pointer node = _head;
				pointer remembered = node;
				while (node != _nil) {
					if (key == node->data->first)
						return node;
					if (_cmp(key, node->data->first)) {
						remembered = node;
						node = node->left;
					}
					else
						node = node->right;
				}
				return _cmp(key, remembered->data->first) ? remembered : _nil;
			}
			return _nil;
		}

		pointer upper_bound(const key_type key) const
		{
			if (_head != _nil)
			{
				pointer node = _head;
				pointer remembered = node;
				while (node != _nil) {

					if (_cmp(key, node->data->first)) {
						remembered = node;
						node = node->left;
					}
					else
						node = node->right;
				}
				return _cmp(key, remembered->data->first) ? remembered : _nil;
			}
			return _nil;
		}

	private:
		pointer find(pointer node, key_type key) const
		{
			if (node != _nil) {
				if (node->data->first == key)
					return node;
				else if (_cmp(key, node->data->first))
					return find(node->left, key);
				else
					return find(node->right, key);
			}
			return _nil;
		}

		pointer maximum(pointer node) const
		{
			while (node->type != nilNode && node->right->type != nilNode) {
				node = node->right;
			}
			return node;
		}

		pointer minimum(pointer node) const
		{
			while (node->type != nilNode && node->left->type != nilNode) {
				node = node->left;
			}
			return node;
		}

		pointer next(pointer node)
		{
			if (node->type == nilNode)
				return node;

			if (node->right->type != nilNode)
				return minimum(node->right);

			pointer tmp = node->parent;
			while (tmp->type != nilNode && node == tmp->right) {
				node = tmp;
				tmp = tmp->parent;
			}
			return tmp;
		}

		pointer prev(pointer node)
		{
			if (node->type == nilNode)
				return node->parent;

			if (node->type != nilNode && node->left->type != nilNode)
				return maximum(node->left);

			pointer tmp = node->parent;
			while (tmp->type != nilNode && node == tmp->left) {
				node = tmp;
				tmp = tmp->parent;
			}

			return tmp->type != nilNode ? tmp : node;
		}

		void free_node(const pointer& node)
		{
			_alloc.destroy(node);
			_alloc.deallocate(node, 1);
		}

		void clear(pointer& node)
		{
			if (node == NULL || node == _nil)
                return;

			clear(node->left);
			clear(node->right);
			if (node == _head) {
                free_node(_head);
                _head = _nil;
                _nil->parent = NULL;
				_size = 0;
			}
			else
                free_node(node);
		}

		void insert_fixup(pointer x)
		{

			/*************************************
			 *  maintain Red-Black tree balance  *
			 *  after inserting node x           *
			 *************************************/

			/* check Red-Black properties */
			while (x != _head && x->parent->type == redNode) {
				/* we have a violation */
				if (x->parent==x->parent->parent->left) {
					pointer y = x->parent->parent->right;
					if (y->type == redNode) {

						/* uncle is redNode */
						x->parent->type = blackNode;
						y->type = blackNode;
						x->parent->parent->type = redNode;
						x = x->parent->parent;
					}
					else {

						/* uncle is blackNode */
						if (x==x->parent->right) {
							/* make x a left child */
							x = x->parent;
							rotate_left(x);
						}

						/* recolor and rotate */
						x->parent->type = blackNode;
						x->parent->parent->type = redNode;
						rotate_right(x->parent->parent);
					}
				}
				else {

					/* mirror image of above code */
					pointer y = x->parent->parent->left;
					if (y->type == redNode) {

						/* uncle is redNode */
						x->parent->type = blackNode;
						y->type = blackNode;
						x->parent->parent->type = redNode;
						x = x->parent->parent;
					}
					else {

						/* uncle is blackNode */
						if (x==x->parent->left) {
							x = x->parent;
							rotate_right(x);
						}
						x->parent->type = blackNode;
						x->parent->parent->type = redNode;
						rotate_left(x->parent->parent);
					}
				}
			}
            _head->type = blackNode;
		}

		ft::pair<pointer, bool> _add(key_type key, mapped_type value)
		{
			pointer current, parent, x;

			/***********************************************
			 *  allocate node for data and insert in tree  *
			 ***********************************************/

			/* find where node belongs */
			current = _head;
			parent = _nil;
			while (current != _nil) {
				if (key==current->data->first) return ft::pair<pointer, bool>(current, false);
				parent = current;
				current = _cmp(key, current->data->first) ?
						  current->left : current->right;
			}
			x = _alloc.allocate(1);
            _alloc.construct(x, value_type(key, value, _nil, redNode));
			x->parent = parent;

			/* insert node in tree */
			if (parent != _nil) {
				if (_cmp(key, parent->data->first))
					parent->left = x;
				else
					parent->right = x;
			}
			else {
                _head = x;
			}

			insert_fixup(x);
            _nil->parent = maximum(_head);
			++_size;
			return ft::pair<pointer, bool>(x, true);
		}

		void delete_node(pointer z)
		{
        	pointer x, y;

        	/*****************************
			 *  delete node z from tree  *
			 *****************************/

        	if (z == _nil) return;

        	if (z->left == _nil || z->right == _nil) {
        		/* y has a NIL node as a child */
        		y = z;
        	}
        	else {
        		/* find tree next with a NIL node as a child */
        		y = z->right;
        		while (y->left != _nil) y = y->left;
        	}

        	/* x is y's only child */
        	if (y->left != _nil)
        		x = y->left;
        	else
        		x = y->right;

        	/* erase y from the parent chain */
        	if (x != _nil)
        		x->parent = y->parent;
        	if (y->parent != _nil)
        		if (y==y->parent->left)
        			y->parent->left = x;
        		else
        			y->parent->right = x;
        		else
        			_head = x;

        		if (y!=z) {
        			delete z->data;
        			z->data = new ft::pair<const key_type, mapped_type>(y->data->first, y->data->second);
        		}

        		if (y->type == blackNode)
					delete_fixup(x);

        		_alloc.destroy(y);
        		_alloc.deallocate(y, 1);
        		_nil->parent = maximum(_head);
		}

		void delete_fixup(pointer x)
		{

			/*************************************
			 *  maintain Red-Black tree balance  *
			 *  after deleting node x            *
			 *************************************/

			while (x != _head && x->type == blackNode) {
				if (x==x->parent->left) {
					pointer w = x->parent->right;
					if (w->type == redNode) {
						w->type = blackNode;
						x->parent->type = redNode;
						rotate_left(x->parent);
						w = x->parent->right;
					}
					if (w->left->type == blackNode && w->right->type == blackNode) {
						w->type = redNode;
						x = x->parent;
					}
					else {
						if (w->right->type == blackNode) {
							w->left->type = blackNode;
							w->type = redNode;
							rotate_right(w);
							w = x->parent->right;
						}
						w->type = x->parent->type;
						x->parent->type = blackNode;
						w->right->type = blackNode;
						rotate_left(x->parent);
						x = _head;
					}
				}
				else {
					pointer w = x->parent->left;
					if (w->type == redNode) {
						w->type = blackNode;
						x->parent->type = redNode;
						rotate_right(x->parent);
						w = x->parent->left;
					}
					if (w->right->type == blackNode && w->left->type == blackNode) {
						w->type = redNode;
						x = x->parent;
					}
					else {
						if (w->left->type == blackNode) {
							w->right->type = blackNode;
							w->type = redNode;
							rotate_left(w);
							w = x->parent->left;
						}
						w->type = x->parent->type;
						x->parent->type = blackNode;
						w->left->type = blackNode;
						rotate_right(x->parent);
						x = _head;
					}
				}
			}
			if (x->type != nilNode)
				x->type = blackNode;
		}

		void rotate_left(pointer x)
		{

			/**************************
			 *  rotate node x to left *
			 **************************/

			pointer y = x->right;

			/* establish x->right link */
			x->right = y->left;
			if (y->left != _nil) y->left->parent = x;

			/* establish y->parent link */
			if (y != _nil) y->parent = x->parent;
			if (x->parent != _nil) {
				if (x==x->parent->left)
					x->parent->left = y;
				else
					x->parent->right = y;
			}
			else {
				_head = y;
			}

			/* link x and y */
			y->left = x;
			if (x != _nil) x->parent = y;
		}

		void rotate_right(pointer x)
		{

			/****************************
			 *  rotate node x to right  *
			 ****************************/

			pointer y = x->left;

			/* establish x->left link */
			x->left = y->right;
			if (y->right != _nil) y->right->parent = x;

			/* establish y->parent link */
			if (y != _nil) y->parent = x->parent;
			if (x->parent != _nil) {
				if (x==x->parent->right)
					x->parent->right = y;
				else
					x->parent->left = y;
			}
			else {
				_head = y;
			}

			/* link x and y */
			y->right = x;
			if (x != _nil) x->parent = y;
		}
	};
}

#endif
