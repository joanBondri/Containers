#pragma once
#include <iostream>
#include "pair.hpp"
#include "make_pair.hpp"
#include "iterator_map.hpp"
#include "reverse_iterator.hpp"
#include "is_integral.hpp"
#include "RBTree.hpp"

namespace ft {
	template<
		class Arg1,
			  class Arg2,
			  class Result
				  >
				  struct binary_function
				  {
					  typedef Arg1 first_argument_type;
					  typedef Arg2 second_argument_type;
					  typedef Result result_type;
				  };
	template < class Key,
			 class T,
			 class Compare = std::less<Key>,
			 class Alloc = std::allocator<ft::pair<const Key,T> >
				 >
				 class map
				 {
					 public :
					 typedef	Key																	key_type;
					 typedef	T																	mapped_type;
					 typedef	ft::pair<const key_type,mapped_type>								value_type;
					 typedef	Compare																key_compare;
					 typedef	Alloc																allocator_type;
					 typedef	typename allocator_type::reference									reference;
					 typedef	typename allocator_type::const_reference							const_reference;
					 typedef	typename allocator_type::pointer									pointer;
					 typedef	typename allocator_type::const_pointer								const_pointer;
					 typedef typename std::ptrdiff_t												difference_type;
					 typedef	size_t																size_type;
					 typedef	iterator_map<RBNode<value_type>, value_type>						iterator;
					 typedef	const_iterator_map<RBNode<value_type>, value_type>					const_iterator;
					 typedef	ft::reverse_iterator<iterator>										reverse_iterator;
					 typedef	ft::reverse_iterator<const_iterator>								const_reverse_iterator;
					 typedef RBTree<value_type, Compare>											tree_type;

					 private :
					 key_compare 	_comp;
					 allocator_type	_alloc;
					 tree_type		_rbt;

					public :
					map() : _comp(key_compare()), _alloc(Alloc()), _rbt(tree_type(_comp))//CONSTRUCTOR
					{}
					map( const Compare& comp,
						 const Alloc& alloc = Alloc() 	) : _comp(comp), _alloc(alloc), _rbt(tree_type(_comp))
					 {}
					 template < class InputIt>
						 map( InputIt first, InputIt last, const Compare &comp = Compare(), const Alloc& alloc = Alloc() ) : _comp(comp), _alloc(alloc), _rbt(tree_type(_comp))
					 {
						 insert(first, last);
					 }
					 map& operator=(const map& x)
					 {
						 clear();
						 insert(x.begin(), x.end());
						 return *this;
					 }

					 map (const map &rhs) : _comp(key_compare()), _alloc(allocator_type()), _rbt(tree_type(_comp))
					 {
						 insert(rhs.begin(), rhs.end());
					 }

					 ~map()//DESTRUCTOR
					 { 
						 _rbt.destroy_all();

					 }
			class value_compare : public ft::binary_function<value_type, value_type, bool>
			{
				friend class map;
				typedef bool result_type;

				protected :
					value_compare( key_compare c) : _comp(c)
					{}
					private :
					key_compare _comp;
				public:
					result_type operator() ( const value_type& lhs, const value_type& rhs) const
					{
						return _comp(lhs.first, rhs.first);
					}
			};

	public:
	bool empty(void) const
	{
		return (begin() == end());
	}
	iterator begin()
	{
		return iterator(_rbt.min(), _rbt.get_end(), _rbt.get_root());
	}
	const_iterator begin() const
	{
		return const_iterator(_rbt.min(), _rbt.get_end(), _rbt.get_root());
	}
	iterator end()
	{
		return iterator(_rbt.get_end(), _rbt.get_end(), _rbt.get_root());
	}
	const_iterator end() const
	{
		return const_iterator(_rbt.get_end(), _rbt.get_end(), _rbt.get_root());
	}
	reverse_iterator rend()
	{
		return reverse_iterator(begin());
	}
	const_reverse_iterator rend() const
	{
		return const_reverse_iterator(begin());
	}
	reverse_iterator rbegin()
	{
		return reverse_iterator(end());
	}
	const_reverse_iterator rbegin() const
	{
		return const_reverse_iterator(end());
	}
	size_type size(void) const
	{
		return _rbt.size();
	}
	size_type max_size() const
	{
		return _rbt.max_size();
	}
	size_type count (const key_type& k) const
	{
		if (_rbt.search(ft::make_pair(k, mapped_type()).first) == _rbt.get_end() ||
					_rbt.search(ft::make_pair(k, mapped_type()).first) == nullptr)
			return (0);
		return (1);
	}
	mapped_type& operator[]( const key_type& key )//OPERATOR[]
	{
			insert(ft::make_pair(key, mapped_type()));
			return (_rbt.search(ft::make_pair(key, mapped_type()).first)->get_data().second);
	}
	iterator find (const key_type& k)
	{
		return (iterator(_rbt.search(ft::make_pair(k, mapped_type()).first), _rbt.get_end(), _rbt.get_root()));
	}
	const_iterator find (const key_type& k) const
	{
		return (const_iterator(_rbt.search(ft::make_pair(k, mapped_type()).first), _rbt.get_end(), _rbt.get_root()));
	}
	ft::pair<iterator, bool> insert(const value_type& value)//INSERT
	{
		try
		{
			_rbt.insert(value);
		} catch (std::out_of_range &e)
		{
			return (ft::make_pair<iterator, bool>(iterator(_rbt.search(value.first), _rbt.get_end(), _rbt.get_root()), false));
		}
		return (ft::make_pair<iterator, bool>(iterator(_rbt.search(value.first), _rbt.get_end(), _rbt.get_root()), true));

	}
	iterator insert(iterator hint, const value_type& value)
	{
		(void)hint;
		try
		{
			_rbt.insert(value);
		} catch (std::out_of_range &e)
		{}
		return(iterator(_rbt.search(value.first), _rbt.get_end(), _rbt.get_root()));

	}
	template<class InputIt>
		void insert(InputIt first, InputIt last)
		{
			while(first != last)
			{
				try
				{
					_rbt.insert(*first);
				} catch (std::out_of_range &e)
				{}
				++first;

			}

		}
	key_compare key_comp() const
	{
		return _comp;
	}
	value_compare value_comp() const
	{
		return _comp;
	}
	allocator_type get_allocator() const
	{
		return _alloc;
	}
	iterator lower_bound (const key_type& k)
	{
		return iterator(_rbt.lower_bound(ft::make_pair(k, mapped_type())), _rbt.get_end(), _rbt.get_root());
	}
	const_iterator lower_bound (const key_type& k) const
	{
		return const_iterator(_rbt.lower_bound(ft::make_pair(k, mapped_type())), _rbt.get_end(), _rbt.get_root());
	}
	iterator upper_bound (const key_type& k)
	{
		return iterator(_rbt.upper_bound(ft::make_pair(k, mapped_type())), _rbt.get_end(), _rbt.get_root());
	}
	const_iterator upper_bound (const key_type& k) const
	{
		return const_iterator(_rbt.upper_bound(ft::make_pair(k, mapped_type())), _rbt.get_end(), _rbt.get_root());
	}
	pair<const_iterator,const_iterator> equal_range (const key_type& k) const
	{
		return (ft::make_pair(lower_bound(k), upper_bound(k)));
	}
	pair<iterator,iterator>	equal_range (const key_type& k)
	{
		return (ft::make_pair(lower_bound(k), upper_bound(k)));
	}
	void clear()
	{
		_rbt.destroy();									
	}
	void swap(map &other)//SWAP
	{
		_rbt.swap(other._rbt);
	}
	iterator erase(iterator pos)
	{
		_rbt.remove(_rbt.get_root(), pos->first);
		return end();

	}
	iterator erase(iterator first, iterator last)
	{
		while (first != last)
		{
			first = find(first->first);
			erase(first++);

		}
		return end();

	}
	size_type erase (const Key& key)
	{
		if (_rbt.remove(_rbt.get_root(), key))
			return 1;
		return 0;

	}

};
	template< class Key , class Compare, class Alloc >
bool operator==( const ft::map<Key, Compare, Alloc>& lhs, const ft::map<Key, Compare, Alloc>& rhs )
{
	if (lhs.size() != rhs.size())
		return false;
	return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));	
}
template< class Key , class Compare, class Alloc >
			bool operator!=( const ft::map<Key, Compare, Alloc>& lhs, const ft::map<Key, Compare, Alloc>& rhs )
{
			return !(lhs == rhs);
				
}
template< class Key , class Compare, class Alloc >
			bool operator<( const ft::map<Key, Compare, Alloc>& lhs, const ft::map<Key, Compare, Alloc>& rhs )
{
			return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
}
template< class Key , class Compare, class Alloc >
			bool operator<=( const ft::map<Key, Compare, Alloc>& lhs, const ft::map<Key, Compare, Alloc>& rhs )
{
			return !(rhs < lhs);
				
}
template< class Key , class Compare, class Alloc >
			bool operator>( const ft::map<Key, Compare, Alloc>& lhs, const ft::map<Key, Compare, Alloc>& rhs )
{
			return (rhs < lhs);
				
}
template< class Key , class Compare, class Alloc >
			bool operator>=( const ft::map<Key, Compare, Alloc>& lhs, const ft::map<Key, Compare, Alloc>& rhs )
{
			return !(lhs < rhs);
				
}
template<class Key, class Compare, class Alloc>
			void swap(ft::map<Key, Compare, Alloc>& lhs, ft::map<Key, Compare, Alloc>& rhs)
{
			lhs.swap(rhs);
				
}
}
