#ifndef TREE_HPP
#define TREE_HPP

#include "node.hpp"
#include "tree_iterator.hpp"

namespace ft {
	template< class T1, class T2, class Compare, class Alloc >
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
		typedef ft::tree_iterator<T1, T2, ft::pair<T1, T2>* > iterator;
		typedef ft::tree_iterator<T1, T2, const ft::pair<T1, T2>* > const_iterator;

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
            _removeTheWholeThree(_head);
            free_node(_nil);
        }

        tree& operator=(const tree& other)
        {
            if (this != &other) {
                clear();
                _cmp = other._cmp;
                for (const_iterator it = other.begin(), ite = other.end(); it!=ite; ++it) {
                    insert(it);
                }
            }
            return *this;
        }

        iterator begin() { return iterator(minimum(_head)); }

        const_iterator begin() const { return const_iterator(minimum(_head)); }

        iterator end() { return iterator(_nil); }

        const_iterator end() const { return const_iterator(_nil); }

        void clear() { _removeTheWholeThree(_head); }

        pointer maximum(pointer node) const
        {
            while (node != _nil && node->right != _nil) {
                node = node->right;
            }
            return node;
        }

        pointer minimum(pointer node) const
        {
            while (node != _nil && node->left != _nil) {
                node = node->left;
            }
            return node;
        }

        ft::pair<pointer, bool> insert(ft::pair<key_type, mapped_type> pair)
        {
            return _add(pair.first, pair.second);
        }

        ft::pair<pointer, bool> insert(pointer hint, ft::pair<key_type, mapped_type> pair)
        {
            (void) hint;
            return _add(pair.first, pair.second);
        }

        template< class InputIterator >
        ft::pair<pointer, bool> insert(InputIterator it)
        {
            return _add(it->first, it->second);
        }

        pointer search(key_type key) const
        {
            return _search(_head, key);
        }

        bool erase(key_type key) { return _remove(key); }

        size_type size() const { return _size; }

        void swap(tree& other)
        {
            std::swap(_nil, other._nil);
            std::swap(_head, other._head);
            std::swap(_cmp, other._cmp);
            std::swap(_alloc, other._alloc);
            std::swap(_size, other._size);
        }

        size_type max_size() const { return _alloc.max_size(); }


		pointer _search(pointer node, key_type key) const
		{
			if (node != _nil) {
				if (node->data->first == key)
                    return node;
				else if (_cmp(key, node->data->first))
                    return _search(node->left, key);
				else
                    return _search(node->right, key);
			}
			return pointer(_nil);
		}

		pointer lower_bound(const key_type key) const
		{
			if (_head == _nil)
				return pointer(_nil);
			else {
				pointer t = _head;
				pointer remembered = t;
				while (t != _nil) {
					if (key==t->data->first) {
						return t;
					}
					if (_cmp(key, t->data->first)) {
						remembered = t;
						t = t->left;
					}
					else {
						t = t->right;
					}
				}
				return _cmp(key, remembered->data->first) ? remembered : _nil;
			}
		}

		pointer upper_bound(const key_type key) const
		{
			if (_head == _nil)
				return pointer(_nil);
			else {
				pointer t = _head;
				pointer remembered = t;
				while (t != _nil) {
//					if (key==t->data->first) {
//						return t;
//					}
					if (_cmp(key, t->data->first)) {
						remembered = t;
						t = t->left;
					}
					else {
						t = t->right;
					}
				}
				return _cmp(key, remembered->data->first) ? remembered : _nil;
			}
		}

		void free_node(const pointer& np)
		{
			_alloc.destroy(np);
			_alloc.deallocate(np, 1);
		}

		bool _remove(key_type key, pointer v = NULL)
		{
			pointer t = _search(v ? v : _head, key);
			if (t == _nil)
                return false;
			_deleteNode(t);
			--_size;
			return true;
		}

		void _removeTheWholeThree(pointer& ptr)
		{
			if (ptr == NULL || ptr == _nil)
                return;
			if (ptr->left)
                _removeTheWholeThree(ptr->left);
			if (ptr->right)
                _removeTheWholeThree(ptr->right);
			if (ptr == _head) {
                free_node(_head);
                _head = _nil;
                _nil->parent = NULL;
				_size = 0;
			}
			else
                free_node(ptr);
		}

		void _rotateLeft(pointer x)
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

		void _rotateRight(pointer x)
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

		void _insertFixup(pointer x)
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
							_rotateLeft(x);
						}

						/* recolor and rotate */
						x->parent->type = blackNode;
						x->parent->parent->type = redNode;
						_rotateRight(x->parent->parent);
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
							_rotateRight(x);
						}
						x->parent->type = blackNode;
						x->parent->parent->type = redNode;
						_rotateLeft(x->parent->parent);
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

			_insertFixup(x);
            _nil->parent = maximum(_head);
			++_size;
			return ft::pair<pointer, bool>(x, true);
		}

		void deleteFixup(pointer x)
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
						_rotateLeft(x->parent);
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
							_rotateRight(w);
							w = x->parent->right;
						}
						w->type = x->parent->type;
						x->parent->type = blackNode;
						w->right->type = blackNode;
						_rotateLeft(x->parent);
						x = _head;
					}
				}
				else {
					pointer w = x->parent->left;
					if (w->type == redNode) {
						w->type = blackNode;
						x->parent->type = redNode;
						_rotateRight(x->parent);
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
							_rotateLeft(w);
							w = x->parent->left;
						}
						w->type = x->parent->type;
						x->parent->type = blackNode;
						w->left->type = blackNode;
						_rotateRight(x->parent);
						x = _head;
					}
				}
			}
			if (x->type != nilNode)
				x->type = blackNode;
		}

		void _deleteNode(pointer z)
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
				deleteFixup(x);

			_alloc.destroy(y);
			_alloc.deallocate(y, 1);
            _nil->parent = maximum(_head);
		}
	};
}

#endif
