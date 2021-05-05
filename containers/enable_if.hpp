#ifndef FT_UTILS_HPP
# define FT_UTILS_HPP

# include <limits>
namespace ft
{	
	template< bool condition, class T = void>
	struct enable_if{}; //nothing defined when not true.

	template<class T>
	struct enable_if<true, T>
	{
		typedef T type;
	};
}

#endif