#pragma once
#include <iostream>
namespace ft
{
	template <class T, const T v>
		struct integral_constant {
			static const T value = v;
			typedef T value_type;
			typedef integral_constant<T,v> type;
			operator T() const { return v; }
		};
	typedef integral_constant<bool, true> true_type;
	typedef integral_constant<bool, false> false_type;
	template <class T>
		struct is_integral : false_type {};
	template <class T>
		struct is_integral<const T> : public is_integral<T> {};
	template <class T>
		struct is_integral<volatile const T> : public is_integral<T> {};	
	template <class T>
		struct is_integral<volatile T> : public is_integral<T> {};

	template<>
		struct is_integral<bool> : true_type {};
	template<>
		struct is_integral<int> : true_type {};
	template<>
		struct is_integral<long> : true_type {};
	template<>
		struct is_integral<long long> : true_type {};
	template<>
		struct is_integral<signed char> : true_type {};
	template<>
		struct is_integral<short int> : true_type {};
	template<>
		struct is_integral<wchar_t> : true_type {};
	template<>
		struct is_integral<char> : true_type {};
	template<>
		struct is_integral<unsigned short int> : true_type {};
	template<>
		struct is_integral<unsigned long long int> : true_type {};
	template<>
		struct is_integral<unsigned long int> : true_type {};
	template<>
		struct is_integral<unsigned int> : true_type {};
	template<>
		struct is_integral<unsigned char> : true_type {};

template<class InputIt1, class InputIt2>
bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
                             InputIt2 first2, InputIt2 last2)
{
    for (; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2)
    {
        if (*first1 < *first2)
            return true;
        if (*first2 < *first1)
            return false;
    }

    return (first1 == last1) && (first2 != last2);
}

template<class InputIt1, class InputIt2, class Compare>
bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
                             InputIt2 first2, InputIt2 last2, Compare comp)
{
    for (; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2)
    {
        if (comp(*first1, *first2))
            return true;
        if (comp(*first2, *first1))
            return false;
    }
 
    return (first1 == last1) && (first2 != last2);
}
}
