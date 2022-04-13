#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

namespace ft {
	template<class T, class Container = ft::vector<T> >
	class stack {
	public:
		typedef T value_type;
		typedef Container container_type;
		typedef typename container_type::size_type size_type;

	protected:
		container_type container;

	public:
		explicit stack(const container_type& container = container_type()) :container(container) { }

		bool empty() const { return container.empty(); }

		size_type size() const { return container.size(); }

		value_type& top() { return container.back(); }

		const value_type& top() const { return container.back(); }

		void push(const value_type& value) { container.push_back(value); }

		void pop() { container.pop_back(); }

		friend bool operator==(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
		{
            return lhs.container==rhs.container;
		}

		friend bool operator<(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
		{
			return lhs.container<rhs.container;
		}
	};

	template<class T, class Container>
	bool operator!=(const stack<T, Container>& lhs, const stack<T, Container>& rhs) { return !(lhs==rhs); }

	template<class T, class Container>
	bool operator<=(const stack<T, Container>& lhs, const stack<T, Container>& rhs) { return !(rhs<lhs); }

	template<class T, class Container>
	bool operator>(const stack<T, Container>& lhs, const stack<T, Container>& rhs) { return rhs<lhs; }

	template<class T, class Container>
	bool operator>=(const stack<T, Container>& lhs, const stack<T, Container>& rhs) { return !(lhs<rhs); }
}

#endif
