#pragma once
#include <iostream>
#include "RBTree.hpp"
#include "iterator_traits.hpp"

namespace ft
{
	template < class Key, class U>
		class const_iterator_map;
	template < class Key, class U>
		class iterator_map
		{
			template < class K, class Us>
				friend class const_iterator_map;
			public :
	
			typedef	typename Key::value_type									value_type;
			typedef	typename Key::value_type									&reference;
			typedef	typename Key::value_type									*pointer;
			typedef	typename ft::bidirectional_iterator_tag						iterator_category;
			typedef typename std::less<Key>										key_compare;
			typedef typename std::ptrdiff_t										difference_type;
			typedef	size_t											size_type;
			
			private :
			typedef	Key*														nodeptr;
			typedef Key												node_type;
			typedef iterator_map<Key, U>							self_type;
			typedef const_iterator_map<Key, U>						citerator_type;
			typedef	typename Key::value_type::first_type						key_type;
			typedef	typename Key::value_type::second_type						mapped_type;


			public :
			iterator_map (const nodeptr ptr, const nodeptr end, const nodeptr root) :	_ptr(ptr),
			_end(end),
			_root(root)
			{}
			iterator_map (void) : _ptr(nullptr), _end(nullptr), _root(nullptr)
			{}
			iterator_map (const iterator_map& x) : _ptr(x._ptr), _end(x._end), _root(x._root)
			{}
			iterator_map& operator=(const iterator_map& x)
			{
				_ptr = x._ptr;
				_end = x._end;
				_root = x._root;
				return *this;
			}
			iterator_map& operator=(const citerator_type& x)
			{
				_ptr = x._ptr;
				_end = x._end;
				_root = x._root;
				return *this;
			}
			bool operator==(const self_type& t) const
			{
				if (t._ptr == _ptr)
					return true;
				return false;
			}
			bool operator!=(const self_type& t) const
			{
				return !(*this == t);
			} 
			bool operator==(const citerator_type& t) const
			{
				if (t.get_ptr() == _ptr)
					return true;
				return false;
			}
			bool operator!=(const citerator_type& t) const
			{
				return !(*this == t);
			} 
			value_type &operator*(void) const
			{
				return _ptr->get_data();
			}
			value_type *operator->(void) const
			{
				return &(_ptr->get_data());
			}
			self_type& operator++()
			{
				if (_ptr == max(_root))
				{
					_ptr = _end;
					return (*this);

				}
				else if (_ptr == _end)
				{
					_ptr = NULL;
					return (*this);

				}
				_ptr = successor(_ptr);
				return (*this);

			}

			self_type operator++(int)
			{
				self_type tmp = *this;
				if (_ptr == max(_root))
				{
					_ptr = _end;
					return (tmp);

				}
				else if (_ptr == _end)
				{
					_ptr = NULL;
					return (tmp);

				}
				_ptr = successor(_ptr);
				return (tmp);

			}

			self_type& operator--()
			{
				if (_ptr == _end)
				{
					_ptr = max(_root);
					return (*this);

				}
				else if (_ptr == min(_root))
				{
					_ptr = _end;
					return (*this);

				}
				_ptr = predecessor(_ptr);
				return (*this);

			}

			self_type operator--(int)
			{
				self_type tmp = *this;
				if (_ptr == _end)
				{
					_ptr = max(_root);
					return (tmp);

				}
				else if (_ptr == min(_root))
				{
					_ptr = _end;
					return (tmp);

				}
				_ptr = predecessor(_ptr);
				return (tmp);

			}
			
			private :
			node_type	*_ptr;
			node_type	*_end;
			node_type	*_root;
			
			node_type*	get_ptr(void) const
			{
				return _ptr;
			}
			node_type* min(node_type* n)
			{
				if (n == NULL || n == _end)
					return _end;
				for(; n->get_left() != _end; n = n->get_left())
				{
				}
				return n;

			}

			node_type* max(node_type* n)
			{
				if (n == NULL || n == _end)
					return _end;
				for(; n->get_right() != _end; n = n->get_right())
				{
				}
				return n;

			}

			node_type* successor(node_type* n)
			{
				if (n->get_right() != _end)
					return min(n->get_right());

				node_type* tmp = n->get_parent();
				while (tmp != _end && tmp != nullptr && n == tmp->get_right())
				{
					n = tmp;
					tmp = tmp->get_parent();

				}
				return tmp;

			}

			node_type* predecessor(node_type* n)
			{
				if (n->get_left() != _end)
					return max(n->get_left());

				node_type* tmp = n->get_parent();
				while (tmp != _end && tmp != nullptr && n == tmp->get_left())
				{
					n = tmp;
					tmp = tmp->get_parent();

				}
				return tmp;
			}
		};

	template < class Key, class U>
		class const_iterator_map
		{
			template < class K, class Us>
				friend class iterator_map;
			public :
			typedef	const typename Key::value_type									value_type;
			typedef	const typename Key::value_type									&reference;
			typedef	const typename Key::value_type									*pointer;
			typedef	typename ft::bidirectional_iterator_tag						iterator_category;
			typedef typename std::less<Key>										key_compare;
			typedef typename std::ptrdiff_t										difference_type;
			typedef	size_t											size_type;
			
			private :
			typedef	typename Key::value_type::first_type						key_type;
			typedef	typename Key::value_type::second_type						mapped_type;
			typedef	Key*														nodeptr;
			typedef Key												node_type;
			typedef const_iterator_map<Key, U>						self_type;
			typedef iterator_map<Key, U>							iterator_map_type;

			public :
			const_iterator_map (const nodeptr ptr, const nodeptr end, const nodeptr root) :	_ptr(ptr),
			_end(end),
			_root(root)
			{}
			const_iterator_map (void) : _ptr(nullptr), _end(nullptr), _root(nullptr)
			{}
			const_iterator_map (const const_iterator_map& x) : _ptr(x._ptr), _end(x._end), _root(x._root)
			{}
			const_iterator_map (const iterator_map_type& x) : _ptr(x._ptr), _end(x._end), _root(x._root)
			{}
			const_iterator_map& operator=(const const_iterator_map& x)
			{
				_ptr = x._ptr;
				_end = x._end;
				_root = x._root;
				return *this;
			}
			const_iterator_map& operator=(const iterator_map_type& x)
			{
				_ptr = x._ptr;
				_end = x._end;
				_root = x._root;
				return *this;
			}
			bool operator==(const self_type& t) const
			{
				if (t._ptr == _ptr)
					return true;
				return false;
			}
			bool operator!=(const self_type& t) const
			{
				return !(*this == t);
			} 
			bool operator==(const iterator_map_type& t) const
			{
				if (t.get_ptr() == _ptr)
					return true;
				return false;
			}
			bool operator!=(const iterator_map_type& t) const
			{
				return !(*this == t);
			} 
			const value_type &operator*(void) const
			{
				return _ptr->get_data();
			}
			const value_type *operator->(void) const
			{
				return &(_ptr->get_data());
			}
			self_type& operator++()
			{
				if (_ptr == max(_root))
				{
					_ptr = _end;
					return (*this);

				}
				else if (_ptr == _end)
				{
					_ptr = NULL;
					return (*this);

				}
				_ptr = successor(_ptr);
				return (*this);

			}

			self_type operator++(int)
			{
				self_type tmp = *this;
				if (_ptr == max(_root))
				{
					_ptr = _end;
					return (tmp);

				}
				else if (_ptr == _end)
				{
					_ptr = NULL;
					return (tmp);

				}
				_ptr = successor(_ptr);
				return (tmp);

			}

			self_type& operator--()
			{
				if (_ptr == _end)
				{
					_ptr = max(_root);
					return (*this);

				}
				else if (_ptr == min(_root))
				{
					_ptr = _end;
					return (*this);

				}
				_ptr = predecessor(_ptr);
				return (*this);

			}

			self_type operator--(int)
			{
				self_type tmp = *this;
				if (_ptr == _end)
				{
					_ptr = max(_root);
					return (tmp);

				}
				else if (_ptr == min(_root))
				{
					_ptr = _end;
					return (tmp);

				}
				_ptr = predecessor(_ptr);
				return (tmp);

			}
			
			private :
			node_type	*_ptr;
			node_type	*_end;
			node_type	*_root;
			
			node_type*	get_ptr(void) const
			{
				return _ptr;
			}
			node_type* min(node_type* n) const
			{
				if (n == NULL || n == _end)
					return _end;
				for(; n->get_left() != _end; n = n->get_left())
				{
				}
				return n;

			}

			node_type* max(node_type* n) const
			{
				if (n == NULL || n == _end)
					return _end;
				for(; n->get_right() != _end; n = n->get_right())
				{
				}
				return n;

			}

			node_type* successor(node_type* n) const
			{
				if (n->get_right() != _end)
					return min(n->get_right());

				node_type* tmp = n->get_parent();
				while (tmp != _end && tmp != nullptr && n == tmp->get_right())
				{
					n = tmp;
					tmp = tmp->get_parent();

				}
				return tmp;

			}

			node_type* predecessor(node_type* n) const
			{
				if (n->get_left() != _end)
					return max(n->get_left());

				node_type* tmp = n->get_parent();
				while (tmp != _end && tmp != nullptr && n == tmp->get_left())
				{
					n = tmp;
					tmp = tmp->get_parent();

				}
				return tmp;
			}
		};
}
