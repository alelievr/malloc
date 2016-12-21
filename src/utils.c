/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 00:29:59 by alelievr          #+#    #+#             */
/*   Updated: 2016/12/21 02:10:52 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

pthread_mutex_t		g_malloc_mutex = PTHREAD_MUTEX_INITIALIZER;

static void ft_malloc_init() __attribute__((constructor));
static void ft_malloc_init()
{
}

void			*mmap_wrapper(size_t size)
{
	void	*ptr;

	if ((ptr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANON, 0, 0)) == MAP_FAILED)
	{
		if (DEBUG_PRINT)
			ERR("failed to allocate memory\n");
//		if (DEBUG_STACKTRACE)
//			stacktrace();
		if (DEBUG_ABORT)
			abort();
	}
	return (ptr);
}

void			munmap_wrapper(void *addr, size_t size)
{
	if ((munmap(addr, size)) == -1)
	{
		if (DEBUG_PRINT)
			ERR("failed to free memory\n");
		if (DEBUG_ABORT)
			abort();
	}
}
