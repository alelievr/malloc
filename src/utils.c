/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 00:29:59 by alelievr          #+#    #+#             */
/*   Updated: 2016/12/22 02:08:35 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc_internal.h"

pthread_mutex_t		g_malloc_mutex = PTHREAD_MUTEX_INITIALIZER;

static void ft_malloc_init() __attribute__((constructor));
static void ft_malloc_init()
{
}

static void		stacktrace(void)
{

}

void			*mmap_wrapper(void *p, size_t size)
{
	void	*ptr;

	if ((ptr = mmap(p, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, 0, 0)) == MAP_FAILED)
	{
		if (M_OPT_PRINT)
			ERR("failed to allocate memory\n");
		if (M_OPT_STACKTRACE)
			stacktrace();
		if (M_OPT_ABORT)
			abort();
	}
	return (ptr);
}

void			munmap_wrapper(void *addr, size_t size)
{
	if ((munmap(addr, size)) == -1)
	{
		if (M_OPT_PRINT)
			ERR("failed to free memory\n");
		if (M_OPT_ABORT)
			abort();
	}
}

int				size_to_type(size_t size)
{
	return (size > 0 && size <= M_TINY) ? M_TINY : TER(size > M_TINY && size <= M_SMALL, M_SMALL, M_LARGE); 
}
