#ifndef NODE_HPP
#define NODE_HPP

#include "utility.hpp"

namespace ft {

	enum NodeType {
		nilNode,
		blackNode,
		redNode
	};

	template<class T1, class T2>
	struct node {
		typedef ft::pair<const T1, T2> value_type;
		NodeType type;
		node* parent;
		node* left;
		node* right;
		value_type* data;

        node(T1 key, T2 value, node* nil = NULL, NodeType type = blackNode)
                : type(type), parent(nil), left(nil), right(nil), data(new value_type(key, value)) { }

		node(const node& other) { *this = other; }

		node& operator=(const node& other)
		{
			if (this!=&other) {
                type = other.type;
                parent = other.parent;
                left = other.left;
                right = other.right;
                data = new value_type(other.data->first, other.data->second);
            }
			return *this;
		}

		~node()
		{
			if (data) {
				delete data;
				data = NULL;
			}
		}
	};
}

#endif
