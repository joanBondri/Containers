#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include "reverse_iterator.hpp"
#include "is_integral.hpp"
#include "enable_if.hpp"

namespace ft {

	template <class It>
	typename std::iterator_traits<It>::difference_type distance (It first, It last)
	{
		typename std::iterator_traits<It>::difference_type result = 0;
        while (first != last) {
            ++first;
            ++result;
        }
        return result;
	}


template < class T, typename Alloc = std::allocator<T> > 
class vector 
{
	public :
		typedef				T										value_type;
		typedef				Alloc									allocator_type;
		typedef typename	allocator_type::reference				reference;
		typedef typename	allocator_type::const_reference			const_reference;
		typedef typename	allocator_type::pointer					pointer;
		typedef typename	allocator_type::const_pointer			const_pointer;
		typedef			 	T *										iterator;
		typedef			 	const T *								const_iterator;
		typedef typename	ft::reverse_iterator<iterator>			reverse_iterator;
		typedef typename	ft::reverse_iterator<const_iterator>	const_reverse_iterator;
		typedef				std::ptrdiff_t								difference_type;
		typedef				size_t									size_type;

	private :
		allocator_type		_allocator;
		value_type*			_list;
		size_type			_size;
		size_type			_capacity;
	public :
		vector (const allocator_type& alloc = allocator_type()) : _allocator(alloc),  _list(), _size(0), _capacity(0)
		{}
		vector (const ft::vector<T, Alloc>& x, const allocator_type& alloc = allocator_type()) : _allocator(alloc),  _list(), _size(0), _capacity(0)
		{
			erase(begin(), end());
			insert(begin(), x.begin(), x.end());
		}
		vector (size_type n, const value_type val = value_type(),
				const allocator_type& alloc = allocator_type()): _allocator(alloc), _list(), _size(0), _capacity(0)
		{
			insert(end(), n, val);
		}
		
		template <class InputIterator>
			vector (InputIterator first, InputIterator last,
					const allocator_type& alloc = allocator_type(),
					typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0) :	_allocator(alloc),
																												_list(),
																												_size(0),
																												_capacity(0)
			{
				insert(end(), first, last);
			}
		vector& operator= (const vector& x)
		{
			reserve(x._capacity);
			assign(x.begin(), x.end());
			return *this;
		}
		void swap (vector& x)
		{
			
			value_type*			swap_list = x._list;
			allocator_type		swap_allocator = x._allocator;
			size_type			swap_size = x._size;
			size_type			swap_capacity = x._capacity;

			x._allocator = _allocator;
			x._size = _size;
			x._capacity = _capacity;
			x._list = _list;
			_list = swap_list;
			_capacity = swap_capacity;
			_size = swap_size;
			_allocator = swap_allocator;
		}
		//ITERATOR
		iterator end(void)
		{
			return _list + _size;
		}

		const_iterator end(void) const
		{
			return _list + _size;
		}
		
		reverse_iterator rend()
		{
			return reverse_iterator(begin());
		}
		const_reverse_iterator rend() const
		{
			return const_reverse_iterator(begin());
		}
		
		iterator begin(void)
		{
			return _list;
		}
		const_iterator begin(void) const
		{
			return _list;
		}
		reverse_iterator rbegin()
		{
			return reverse_iterator(end());
		}
		const_reverse_iterator rbegin() const
		{
			return const_reverse_iterator(end());
		}
		reference front (void)
		{
			return *(begin());
		}
		const_reference front (void) const
		{
			return *(begin());
		}
		reference back (void)
		{
			return *(end() - 1);
		}
		const_reference back (void) const
		{
			return *(end() - 1);
		}
		const_reference at(size_type n) const
		{
			std::stringstream exep; 
			exep << "vector::_M_range_check: __n (which is " << n << ") >= this->size() (which is " << _size << ")";
			if (n > _size)
				throw std::out_of_range(exep.str());
			return *(_list + n);
		}

		reference at(size_type n)
		{
			std::stringstream exep; 
			exep << "vector::_M_range_check: __n (which is " << n << ") >= this->size() (which is " << _size << ")";
			if (n > _size)
				throw std::out_of_range(exep.str());
			return *(_list + n);
		}
		value_type* data() throw ()
		{
			return _list;
		}
		const value_type* data() const throw ()
		{
			return _list;
		}
		template <class InputIterator>
			void assign (InputIterator first, InputIterator last,
					 typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0)
			{
				erase(begin(), end());
				difference_type n = ft::distance(first, last);
				while (n-- > 0)
				{
					push_back(*first);
					first++;
				}
			}
		void assign (size_type n, const value_type& val)
		{
			erase(begin(), end());
			while (n != 0)
			{
				push_back(val);
				n--;
			}
		}
		//CAPACITY
		bool empty(void) const
		{
			return _size ? false : true;
		}
		size_type capacity() const
		{
			return _capacity;
		}
		void clear(void)
		{
			erase(begin(), end());
		}
		void reserve(size_type n)
		{
			if (n > max_size())
				throw(std::length_error("vector::reserve"));
			if (n <= capacity())
				return ;
			difference_type old_capacity = capacity();
			pointer old_begin = _list;
			pointer save_begin = _list;
			pointer old_end = _list + _size;
			_list = _allocator.allocate(n);
			pointer _end = _list;
			_capacity = n;
			while (old_begin != old_end)
			{
				_allocator.construct(_end, *(old_begin));
				_allocator.destroy(old_begin);
				_end++;
				old_begin++;
			}
			if (old_capacity)
				_allocator.deallocate(save_begin, old_capacity);
		}

		virtual ~vector ()
		{
			clear();
			if (_capacity)
				_allocator.deallocate(_list, _capacity);
		}

		allocator_type get_allocator() const
		{
			return _allocator;
		}

		reference operator[] (size_type n)
		{
			return _list[n];
		}

		const_reference operator[] (size_type n) const
		{
			return _list[n];
		}

		size_type max_size(void) const
		{
			return _allocator.max_size();
		}

		size_type size(void) const
		{
				return _size;
		}
		void resize (size_type n, value_type val = value_type())
		{
			if (n < _size)
				erase(begin() + n, begin() + size());
			else
			{
					if (n > _capacity)
					{
						if (n <= _size * 2)
							reserve(_size * 2);
						else
							reserve(n);
					}
					for (size_type i = _size; i < n; i++)
					{
						_allocator.construct(_list + i, val);
					}
					_size = n;
			}
		}
		void push_back (const value_type& val)
		{
			insert(end(), val);
		}
		void pop_back()
		{
			if (_size > 0)
			{
				_allocator.destroy(_list + _size - 1);
				_size--;
			}
		}
		iterator erase(iterator position)
		{
				size_type		offset;

				offset = 0;
				for (iterator it = begin(); it != position; it++)
				{
					offset++;
				}
				_allocator.destroy(_list + offset);
				for (size_type i = offset; i <size() - 1; i++)
				{
					_allocator.construct(_list + i, *(_list + i + 1));
					_allocator.destroy(_list + i + 1);
				}
				_size--;
				return (position);
		}
		iterator erase(iterator first, iterator last)
		{
			iterator	first_end = end();
			size_type	pag = last - first;
			iterator	first_bis = first;
			while (first_bis < last)
				_allocator.destroy(first_bis++);
			for (iterator ite = first; ite < first_end - pag; ite++)
			{
				_allocator.construct(ite, *(ite + pag));
				_allocator.destroy(ite + pag);
			}
			_size -= pag;
			return first;
		}
		iterator insert (iterator position, const value_type& val)
		{
			size_type index = position - begin();
			if (capacity() < size() + 1)
			{
				reserve(capacity() ? capacity() * 2 : 1);
				position = begin() + index;
			}
			for (iterator ite = end() - 1;
					ite >= position;
					--ite)
			{
				_allocator.construct(ite + 1, *ite);
				_allocator.destroy(ite);

			}
			//std::cout << "ici meme cap = " << capacity() << ", size = " << size()  << ", pos = " << (long long)position << ", pos = " << (long long)_list << std::endl;
			_allocator.construct(position, val);
			_size += 1;
			return position;
		}

		void insert (iterator position, size_type n, const value_type& val)
		{
			if ( n == 0 )
				return ;
			size_type index = position - begin();
			while (capacity() < size() + n)
			{
				if (size() + n <= _size * 2)
					reserve(_size * 2);
				else
					reserve(size() + n);
				position = begin() + index;
			}
			for (iterator ite = end() - 1;
					ite >= position;
					--ite)
			{
				_allocator.construct(ite + n, *ite);
				_allocator.destroy(ite);
			}
			_size += n;
			while (n-- > 0)
				_allocator.construct(position++, val);
		}

		template <class InputIterator>
			void insert (iterator position, InputIterator first, InputIterator last,
					typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0)
			{
				if (first == last)
					return ;
				size_type index = position - begin();
				difference_type n = ft::distance(first, last);
				if(capacity() <= n + size())
				{
					if (size() + n <= _size * 2)
						reserve(_size * 2);
					else
						reserve(size() + n);
					position = begin() + index;
				}
				for (iterator ite = end() - 1;
						ite >= position;
						--ite)
				{
					_allocator.construct(ite + n, *ite);
					_allocator.destroy(ite);
				}
				_size += n;
				while (first != last)
					_allocator.construct(position++, *(first++));
			}
};
template< class T, class Alloc >
	bool operator==( const ft::vector<T,Alloc>& lhs,
			 const ft::vector<T,Alloc>& rhs )
{
	typename ft::vector<T,Alloc>::const_iterator it_l = lhs.begin();
	typename ft::vector<T,Alloc>::const_iterator it_r = rhs.begin();

	if (lhs.size() != rhs.size())
		return false;
	while (it_l < lhs.end())
	{
		if (*it_l != *it_r)
			return false;
		it_l++;
		it_r++;
	}
	return true;
}
template< class T, class Alloc >
	bool operator!=( const ft::vector<T,Alloc>& lhs,
			 const ft::vector<T,Alloc>& rhs )
{
	return !(lhs == rhs);
}

template< class T, class Alloc >
	bool operator>=( const ft::vector<T,Alloc>& lhs,
			 const ft::vector<T,Alloc>& rhs )
{
	return (ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()) || lhs == rhs);
}
template< class T, class Alloc >
	bool operator>( const ft::vector<T,Alloc>& lhs,
			 const ft::vector<T,Alloc>& rhs )
{
	return (ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()));
}
template< class T, class Alloc >
	bool operator<( const ft::vector<T,Alloc>& lhs,
			 const ft::vector<T,Alloc>& rhs )
{
	return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
}
template< class T, class Alloc >
	bool operator<=( const ft::vector<T,Alloc>& lhs,
			 const ft::vector<T,Alloc>& rhs )
{
	return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()) || rhs == lhs);
}
template< class T, class Alloc >
	void	swap(vector<T, Alloc> &x, vector<T, Alloc> &y)
	{
		x.swap(y);
		
	}		
}

