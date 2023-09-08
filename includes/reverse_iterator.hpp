#pragma once
#include "iterator_traits.hpp"

namespace ft {

	template <class Iterator>
		class reverse_iterator
		{
			private :
				Iterator	_ptr;
			public :
				typedef				Iterator										iterator_type;
				typedef	typename	iterator_traits<Iterator>::value_type			value_type;
				typedef	typename	iterator_traits<Iterator>::difference_type		difference_type;
				typedef	typename	iterator_traits<Iterator>::iterator_category	iterator_category;
				typedef	typename	iterator_traits<Iterator>::pointer				pointer;
				typedef	typename	iterator_traits<Iterator>::reference			reference;
							reverse_iterator (void) : _ptr(iterator_type())
				{}
							reverse_iterator (iterator_type& ite) : _ptr(ite)
				{}
				template <class Iter>
					reverse_iterator (const reverse_iterator<Iter>& rev_it) : _ptr(rev_it.get_ptr())
				{}
				reverse_iterator (const iterator_type& it) : _ptr(it)
				{}
				reverse_iterator&	operator= (const reverse_iterator& ite)
				{
					_ptr = ite._ptr;
					return *this;
				}
							virtual ~reverse_iterator ()
				{}
				iterator_type base (void) const
				{
					return _ptr;
				}
				iterator_type get_ptr(void) const
				{
					return _ptr ;
				}
				bool	operator!= (const reverse_iterator& ite) const
				{
					return _ptr != ite._ptr;
				}
				bool	operator== (const reverse_iterator& ite) const
				{
					return _ptr == ite._ptr;
				}
				bool	operator>= (const reverse_iterator& ite) const
				{
					return _ptr <= ite._ptr;
				}
				bool	operator<= (const reverse_iterator& ite) const
				{
					return _ptr >= ite._ptr;
				}
				bool	operator< (const reverse_iterator& ite) const
				{
					return _ptr > ite._ptr;
				}
				bool	operator> (const reverse_iterator& ite) const
				{
					return _ptr < ite._ptr;
				}
				reverse_iterator&	operator++ (void)
				{
					_ptr--;
					return *this;
				}
				reverse_iterator	operator++ (int)
				{
					reverse_iterator ite(*this);
					_ptr--;
					return ite;
				}
				reverse_iterator&	operator-- (void)
				{
					_ptr++;
					return *this;
				}
				reverse_iterator	operator-- (int)
				{
					reverse_iterator ite(*this);
					_ptr++;
					return ite;
				}
				reference			operator* (void) const
				{
					iterator_type ite = _ptr;
					return *(--ite);
				}
				pointer			operator-> (void) const
				{
					return &(operator*());
				}
				reverse_iterator&	operator+= (difference_type in)
				{
					_ptr -= in;
					return *this;
				}
				reverse_iterator&	operator-= (difference_type in)
				{
					_ptr += in;
					return *this;
				}
				reverse_iterator	operator+ (difference_type in) const
				{
					reverse_iterator res;
					res._ptr = _ptr - in;
					return res;
				}
				reverse_iterator	operator- (difference_type in) const
				{
					reverse_iterator res;
					res._ptr = _ptr + in;
					return res;
				}
				reference	operator[] (difference_type in) const
				{
					return *(_ptr - in - 1);
				}
		};
	template <class Iterator>
		reverse_iterator<Iterator> operator+
				(typename ft::reverse_iterator<Iterator>::difference_type n,
					const ft::reverse_iterator<Iterator>& rev_it)
		{
			return rev_it + n;
		}
	template <class Iterator1,class Iterator2>
		typename reverse_iterator<Iterator1>::difference_type operator-
				(const reverse_iterator<Iterator1>& lhs,
				 const reverse_iterator<Iterator2>& rhs)
		{
			return rhs.get_ptr() - lhs.get_ptr();
		}
	template <class Iterator1,class Iterator2>
	  	bool operator== (const reverse_iterator<Iterator1>& lhs,
				const reverse_iterator<Iterator2>& rhs)
		{
			return lhs.get_ptr() == rhs.get_ptr();
		}
	template <class Iterator1,class Iterator2>
		bool operator!= (const reverse_iterator<Iterator1>& lhs,
				const reverse_iterator<Iterator2>& rhs)
		{
			return lhs.get_ptr() != rhs.get_ptr();
		}
	template <class Iterator1,class Iterator2>
		bool operator<  (const reverse_iterator<Iterator1>& lhs,
				const reverse_iterator<Iterator2>& rhs)
		{
			return lhs.get_ptr() > rhs.get_ptr();
		}
	template <class Iterator1,class Iterator2>
		bool operator<= (const reverse_iterator<Iterator1>& lhs,
				const reverse_iterator<Iterator2>& rhs)
		{
			return lhs.get_ptr() >= rhs.get_ptr();
		}
	template <class Iterator1,class Iterator2>
		bool operator>  (const reverse_iterator<Iterator1>& lhs,
				const reverse_iterator<Iterator2>& rhs)
		{
			return lhs.get_ptr() < rhs.get_ptr();
		}
	template <class Iterator1,class Iterator2>
		bool operator>= (const reverse_iterator<Iterator1>& lhs,
				const reverse_iterator<Iterator2>& rhs)
		{
			return lhs.get_ptr() <= rhs.get_ptr();
		}
}
