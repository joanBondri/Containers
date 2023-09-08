#pragma once
#include <iostream>
#include "pair.hpp"
#define BLACK 0
#define RED 1

namespace ft {


	template < class T>
		class RBNode 
		{
			public :
			typedef	T&											reference;
			typedef	T*											pointer;
			typedef	const T											const_value_type;
			typedef	T											value_type;
			typedef	bool										color_type;
			typedef RBNode<T>									self_type;

			public :
			value_type	_data;
			color_type	_color;
			RBNode*		_right;
			RBNode*		_left;
			RBNode*		_parent;

			public :
			RBNode(const value_type b) : _data(b)
			{}
			RBNode(void) : _data(value_type()), _color(RED),
			_right(nullptr), _left(nullptr), _parent(nullptr)
			{}
			RBNode(const value_type value, color_type const color,
					RBNode* const r, RBNode* const l, RBNode* const parent) : _data(value), _color(color),
			_right(r), _left(l), _parent(parent)
			{}
			self_type* get_right(void) const
			{
				return _right;
			}
			self_type* get_left(void) const
			{
				return _left;
			}
			void	set_right(self_type* r)
			{
				_right = r;
			}
			void	set_left(self_type* l)
			{
				_left = l;
			}
			const_value_type &get_data(void) const
			{
				return _data;
			}
			value_type &get_data(void)
			{
				return _data;
			}
			void		set_data(value_type& da)
			{
				_data = da;
			}
			self_type*	get_parent(void) const
			{
				return _parent;
			}
			void	set_parent(self_type* unit)
			{
				_parent = unit;
			}
			color_type	get_color(void) const
			{
				return _color;
			}
			void		set_color(color_type co)
			{
				_color = co;
			}
			const value_type &operator* (void) const
			{
				return (_data);
			}
			value_type *operator-> (void) const
			{
				return (&_data);
			}
			self_type* get_root(void) const
			{
				self_type* root = _parent;
				while (root && root->get_parent())
					root = root->get_parent();
				return root;
			}

		};


	template < class value,
			 class Compare = std::less<typename value::first_type>,
			 class Allocator = std::allocator<RBNode<value> > >
				 class RBTree
				 {
					public :
					 typedef bool								color_type;
					 typedef	value								value_type;
					 typedef	typename value::first_type			key_type;
					 typedef	Compare								key_compare;
					 typedef typename std::ptrdiff_t							difference_type;
					 typedef	size_t								size_type;
					 typedef RBNode<value_type>					node_type;
					 typedef Allocator							allocator_type;
					 private :
					 node_type		*_root;
					 allocator_type	_node_alloc;
					 node_type		*_end;
					 key_compare		_cmp;
					 size_type		_size;

					public :
					 //constructor
					 RBTree (key_compare const& cmp = key_compare()) :	_root(nullptr),
					 _node_alloc(allocator_type()),
					 _end(_node_alloc.allocate(1)),
					 _cmp(cmp),
					 _size(0)
					 {
						 _node_alloc.construct(_end, node_type());
						 _root = _end;
						 _size = 0;
					 }
					 RBTree (const RBTree& x)
					 {
						 *this = x;
					 }

					 //destructor
					 void	destroy_recursive(node_type *root)
					 {
						 if (root == _end || root == nullptr)
							 return ;
						 destroy_recursive(root->get_right());
						 destroy_recursive(root->get_left());
						 _node_alloc.destroy(root);
						 _node_alloc.deallocate(root, 1);
					 }
					 void	destroy(void)
					 {
						 destroy_recursive(_root);
						 _root = _end;
						 _size = 0;
					 }
					 void	destroy_all(void)
					 {
						 destroy_recursive(_root);
						 _root = _end;
						 _size = 0;
						 _node_alloc.destroy(_end);
						 _node_alloc.deallocate(_end, 1);
					 }
					 ~RBTree ()
					 {
					 }

					 //tools
					 node_type	*next(node_type* k1, node_type* k2)
					 {
						 if (k1 == _end || k2 == _end || k1 == nullptr || k2 == nullptr)
							 return _end;
						 if (_cmp((**k1).first, (**k2).first))
							 return k2->get_left();
						 return k2->get_right();
					 }
					 bool	key_equal(const value_type &k1, const value_type &k2) const
					 {
						 return (!_cmp(k1.first, k2.first) && !_cmp(k2.first, k1.first));
					 }
					 void	associate_node(node_type *parent, node_type *child)
					 {
						 if (!child)
							 return ;
						 if (child->get_parent() && child->get_parent()->get_left() == child)
							 child->get_parent()->set_left(_end);
						 else if (child->get_parent() && child->get_parent()->get_right() == child)
							 child->get_parent()->set_right(_end);
						 child->set_parent(parent);
						 if (!parent)
							 return ;
						 if (_cmp((**parent).first, (**child).first))
						 {
							 if (parent->get_left())
								 parent->set_left(_end);
							 parent->set_left(child);
						 }
						 else
						 {
							 if (parent->get_right())
								 parent->set_right(_end);
							 parent->set_right(child);
						 }
					 }
					 void	swap(RBTree& x)
					 {
						 node_type		*root = _root;
						 node_type		*end = _end;
						 allocator_type	node_alloc = _node_alloc;
						 key_compare		cmp = _cmp;
						 size_type		size = _size;

						 _root = x._root;
						 _end = x._end;
						 _node_alloc = x._node_alloc;
						 _cmp = x._cmp;
						 _size = x._size;

						 x._root = root;
						 x._end = end;
						 x._node_alloc = node_alloc;
						 x._cmp = cmp;
						 x._size = size;
					 }
					 //boundries
					 node_type* lower_bound(const value_type& v) const
					 {
						 node_type *p = min();

						 for ( ; p != _end; p = successor(p) )
						 {
							 if (!_cmp((**p).first, v.first))
								 break ;

						 }
						 return p;

					 }
					 void	display_node(node_type* no) const
					 {
						 if (no == _end || no == nullptr)
						 {
						 	std::cout << "we don't dislay end" << std::endl;
							return ;
						 }
						 std::cout << "========================" << std::endl;
						 std::cout << "key: "<< no->get_data().first << " | value: " << no->get_data().second << std::endl;
						std::cout << "parent : " << no->get_parent() << std::endl;
						std::cout << "right  : " << no->get_right() << std::endl;
						if (no->get_right() != _end)
							std::cout << "key: "<< no->get_right()->get_data().first << " | value: " << no->get_right()->get_data().second << std::endl;
						std::cout << "left   : " << no->get_left() << std::endl;
						if (no->get_left() != _end)
							std::cout << "key: "<< no->get_left()->get_data().first << " | value: " << no->get_left()->get_data().second << std::endl;
						 std::cout << "========================" << std::endl;
					 }
					 node_type *upper_bound(const value_type& v) const
					 {
						 node_type *p = min();

						 for ( ; p != _end; p = successor(p) )
						 {
							 if (_cmp(v.first, (**p).first))
							 {
								 break ;
							 }

						 }
						 return p;

					 }
					 //Rotation
					 void	left_rotation(node_type* no)
					 {
						 if (!no)
							 return ;
						 node_type* y = no->get_right();
						 node_type*  beta = _end;
						 if (y)
							 beta = y->get_left();
						 associate_node(no->get_parent(), y);
						 associate_node(no, beta);
						 associate_node(y, no);
					 }

					 void	right_rotation(node_type* no)
					 {
						 if (!no)
							 return ;
						 node_type* y = no->get_left();
						 node_type*  beta = _end;
						 if (y)
							 beta = y->get_right();
						 associate_node(no->get_parent(), y);
						 associate_node(no, beta);
						 associate_node(y, no);
					 }
					 public :

					 //getter
					 node_type	*get_end() const
					 {
						 return _end;
					 }
					 const node_type	*get_cend() const
					 {
						 return _end;
					 }

					 //min and max
					 node_type	*min(node_type *s) const
					 {
						 if (s == nullptr || s == _end)
							 return _end;
						 for (; s->get_left() != _end; s = s->get_left())
						 {
						 }
						 return s;
					 }
					 node_type	*min() const
					 {
						 return min(_root);
					 }
					 node_type	*max(node_type *s) const
					 {
						 if (s == nullptr || s == _end)
							 return _end;
						 for (; s->get_right() != _end; s = s->get_right());
						 return s;
					 }
					 node_type	*max() const
					 {
						 return max(_root);
					 }

					 node_type	*search(const key_type& key) const
					 {
						 return _search(_root, key);
					 }

					 node_type*	_search(node_type *node, const key_type key) const
					 {
						 if (node == _end || node == nullptr)
							 return node;
						 else if (_cmp(key, (**node).first))
							 return _search(node->get_left(), key);
						 else if (_cmp((**node).first, key))
							 return _search(node->get_right(), key);
						 else
							 return node;

					 }
					 //size and max_size
					 size_type	size(node_type *s) const
					 {
						 if (s == nullptr)
							 return 0;
						 return (s == _end ? 0 : size(s->get_right()) + size(s->get_left()) + 1);
					 }
					 size_type	size () const
					 {
						 return _size;
					 }
					 size_type	max_size()                    const
					 {
						 return _node_alloc.max_size();
					 }
					 //insert remove and checkers
					 void	insert(value_type val)
					 {
						 node_type *unit = _node_alloc.allocate(1);
						 _node_alloc.construct(unit, node_type(val, RED, _end, _end, nullptr));
						 if (_root == _end)
						 {
							_root = unit;
							_size = size(_root);
						 	unit->set_color(BLACK);
							 return ;
						 }
						 node_type *no = _root;
						 if (_root != _end && _root != nullptr && key_equal((**no), (**unit)))
						 {
							 destroy_recursive(unit);
							 throw std::out_of_range("Invalid key");
							 return ;
						 }
						 while (next(unit, no) != _end)
						 {
							no = next(unit, no);
							 if (key_equal((**no), (**unit)))
							 {
								 destroy_recursive(unit);
								 throw std::out_of_range("Invalid key");
								 return ;
							 }
							
						 }
						if (key_equal((**no), (**unit)))
						{
							 destroy_recursive(unit);
							 throw std::out_of_range("Invalid key");
							 return ;
						 }
						 if(_cmp((**unit).first, (**no).first))
							 no->set_left(unit);
						 else
							 no->set_right(unit);
						 unit->set_parent(no);
						 fix_insert(_root);
						_size = size(_root);
					 }

					 void	_trans(node_type *u, node_type *v)
					 {
						 if (u->get_parent() == nullptr)
							 _root = v;
						 else if (u == u->get_parent()->get_left())
							 u->get_parent()->set_left(v);
						 else
							 u->get_parent()->set_right(v);
						 v->set_parent(u->get_parent());
					 }

					 bool	remove(node_type *unit, key_type key)
					 {
						 node_type	*buff_one;
						 node_type	*buff_parent;
						 node_type	*buff_two;
						node_type	*find_one = nullptr;
						 while (unit != _end && unit != nullptr)
						 {
							 if (_cmp((**unit).first, key))
								 unit = unit->get_right();
							 else if (_cmp(key, (**unit).first))
								 unit = unit->get_left();
							 else
							 {
								 find_one = unit;
								 unit = unit->get_right();
								 break ;
							 }
						 }
						 if (find_one == nullptr)
							 return false;
						 buff_one = find_one;
						 buff_parent = find_one->get_parent();
						 color_type find_color = buff_one->get_color();
						 if (find_one->get_left() == _end)
						 {
							 buff_two = find_one->get_right();
							 _trans(find_one, find_one->get_right());
						 }
						 else if (find_one->get_right() == _end)
						 {
							 buff_two = find_one->get_left();
							 _trans(find_one, find_one->get_left());
						 }
						 else
						 {
							 buff_one = min(find_one->get_right());
							 find_color = buff_one->get_color();
							 buff_two = buff_one->get_right();
								 if (buff_one->get_parent() == find_one)
									 buff_two->set_parent(buff_one);
								 else
								 {
									 _trans(buff_one, buff_one->get_right());
									 buff_one->set_right(find_one->get_right());
									 buff_one->get_right()->set_parent(buff_one);
								 }
								 _trans(find_one, buff_one);
								 buff_one->set_left(find_one->get_left());
								 buff_one->get_left()->set_parent(buff_one);
								 buff_one->set_color(find_one->get_color());
						 }
						 if (buff_two->get_parent())
						 	_root = buff_two->get_root();
						 else
						 	_root = buff_two;
						 _node_alloc.destroy(find_one);
						 _node_alloc.deallocate(find_one, 1);					
						 if (find_color == BLACK)
							 fix_delete(buff_two);
						 _size--;
						 return true;
					 }

					 //predecessor and successor
					 node_type	*successor(node_type* unit) const
					 {
						 if (unit == nullptr || unit == _end)
							 return _end;
						 node_type	*no;
						 if (unit->get_right() != _end)
						 {
							 no = unit->get_right();
							 while (no->get_left() != _end)
								 no = no->get_left();
						 	//display_node(no);
							 return no;
						 }
						 else
						 {
							 no = unit;
							 while (no->get_parent())
							 {
								 if (no->get_parent()->get_left() == no)
									 return no->get_parent();
								 no = no->get_parent();
							 }
							 return (_end);
						 }
					 }
					 node_type	*predecessor(node_type* unit) const
					 {
						 if (unit == nullptr || unit == _end)
							 return _end;
						 node_type	*no;
						 if (unit->get_left() != _end)
						 {
							 no = unit->get_left();
							 while (no->get_right() != _end)
								 no = no->get_right();
							 return no;
						 }
						 else
						 {
							 no = unit;
							 while (no->get_parent())
							 {
								 if (no->get_parent()->get_right() == no)
									 return no->get_parent();
								 no = no->get_parent();
							 }
							 return (nullptr);
						 }
					 }

					 node_type	*get_root(void) const
					 {
						 return _root;
					 }

					 void	fix_delete(node_type *k)
					 {
						 node_type *s;
						 while (k != _root && k->get_color() == BLACK)
						 {
							 if (k == k->get_parent()->get_left())
							 {
								 s = k->get_parent()->get_right();
								 if (s->get_color() == RED)
								 {
									 s->set_color(BLACK);
									 k->get_parent()->set_color(RED);
									 left_rotation(k->get_parent());
									 s = k->get_parent()->get_right();
								 }
								 if (s->get_left()->get_color() == BLACK && s->get_right()->get_color() == BLACK)
								 {
									 s->set_color(RED);
									 k = k->get_parent();
								 }
								 else
								 {
									 if (s->get_right()->get_color() == BLACK)
									 {
										 s->get_left()->set_color(BLACK);
										 s->set_color(RED);
										 right_rotation(s);
										 s = k->get_parent()->get_right();
									 }
									 s->set_color(k->get_parent()->get_color());
									 k->get_parent()->set_color(BLACK);
									 s->get_right()->set_color(BLACK);
									 left_rotation(k->get_parent());
									 k = k->get_root();
								 }
							 }
							 else
							 {
								 s = k->get_parent()->get_left();
								 if (s->get_color() == RED)
								 {
									 s->set_color(BLACK);
									 k->get_parent()->set_color(RED);
									 right_rotation(k->get_parent());
									 s = k->get_parent()->get_left();
								 }
								 if (s->get_right()->get_color() == BLACK && s->get_left()->get_color() == BLACK)
								 {
									 s->set_color(RED);
									 k = k->get_parent();
								 }
								 else
								 {
									 if (s->get_left()->get_color() == BLACK)
									 {
										 s->get_right()->set_color(BLACK);
										 s->set_color(RED);
										 left_rotation(s);
										 s = k->get_parent()->get_left();
									 }
									 s->set_color(k->get_parent()->get_color());
									 k->get_parent()->set_color(BLACK);
									 s->get_left()->set_color(BLACK);
									 right_rotation(k->get_parent());
									 k = k->get_root();
								 }
							 }
						 }
						 k->set_color(BLACK);
					 }

					 void	fix_insert(node_type *k)
					 {

						 while ( k->get_parent() && k->get_parent()->get_color() == RED)
						 {
							 if (k->get_parent() == k->get_parent()->get_parent()->get_right())
							 {
								 node_type *u = k->get_parent()->get_parent()->get_left();
								 if (u && u->get_color() == RED)
								 {
									 u->set_color(BLACK);
									 k->get_parent()->set_color(BLACK);
									 k->get_parent()->get_parent()->set_color(RED);
									 k = k->get_parent()->get_parent();
								 }
								 else
								 {
									 if (k == k->get_parent()->get_left())
									 {
										 k = k->get_parent();
										 right_rotation(k);
									 }
									 k->get_parent()->set_color(BLACK);
									 k->get_parent()->get_parent()->set_color(RED);
									 left_rotation(k->get_parent()->get_parent());
								 }
							 }
							 else
							 {
								 node_type *u = k->get_parent()->get_parent()->get_right();
								 if (u && u->get_color() == RED)
								 {
									 u->set_color(BLACK);
									 k->get_parent()->set_color(BLACK);
									 k->get_parent()->get_parent()->set_color(RED);
									 k = k->get_parent()->get_parent();
								 }
								 else
								 {
									 if (k == k->get_parent()->get_right())
									 {
										 k = k->get_parent();
										 left_rotation(k);
									 }
									 k->get_parent()->set_color(BLACK);
									 k->get_parent()->get_parent()->set_color(RED);
									 right_rotation(k->get_parent()->get_parent());
								 }
							 }
							 if (k == _root)
								 break ;
						 }
						 _root->set_color(BLACK);
					 }
				 };
}
