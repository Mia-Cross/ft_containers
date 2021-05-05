/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enable_if.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 22:21:45 by lemarabe          #+#    #+#             */
/*   Updated: 2021/05/05 22:22:08 by lemarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENABLE_IF_HPP
# define ENABLE_IF_HPP

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