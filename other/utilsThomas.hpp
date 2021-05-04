#ifndef UTILS
# define UTILS

# include <iostream>

namespace	ft
{
	template<typename X>
	void					_swap(X &c, X &d)
	{
		X _tmp = c;
		c = d;
		d = _tmp;
	}
	template<class T>
	bool		basic_comp(T a, T b)
	{
		return (a < b);
	}
}

#endif