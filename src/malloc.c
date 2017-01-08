/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/08 20:21:49 by alelievr          #+#    #+#             */
/*   Updated: 2017/01/08 20:33:47 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc_internal.h"

void		*malloc(size_t size)
{
	return (ft_alloc(NULL, size));
}

void		*calloc(size_t count, size_t size)
{
	void	*ret;

	ret = ft_alloc(NULL, count * size);
	ft_memset(ret, 0, count * size);
	return (ret);
}

void		free(void *ptr)
{
	ft_free(ptr);
}

void		*realloc(void *ptr, size_t size)
{
	return ft_alloc(ptr, size);
}

void		*reallocf(void *ptr, size_t size)
{
	return ft_alloc(ptr, size);
}
