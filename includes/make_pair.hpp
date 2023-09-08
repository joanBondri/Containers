#pragma once
#include "pair.hpp"

namespace ft 
{
	template <class InputIterator1, class InputIterator2>
		bool equal ( InputIterator1 first1, InputIterator1 last1, InputIterator2 first2  )
		{
			while (first1!=last1) {
				if (!(*first1 == *first2))   // or: if (!pred(*first1,*first2)), for version 2
					return false;
				++first1; ++first2;
			}
			return true;
		}
	template <class T1,class T2>
  ft::pair<T1,T2> make_pair (T1 x, T2 y)
  {
    return ( ft::pair<T1,T2>(x,y) );
  }
}
