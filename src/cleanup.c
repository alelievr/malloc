/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 02:07:44 by alelievr          #+#    #+#             */
/*   Updated: 2016/12/22 02:07:52 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc_internal.h"

static bool	free_page(t_page *p, t_heap *h, int index)
{
	munmap_wrapper(p, p->total_alloc_size);
	(void)h;
	(void)index;
	return false;
}

static bool	free_heap(t_heap *h)
{
	if (h->allocated)
		munmap_wrapper(h, getpagesize());
	return false;
}

static void	clean_heap(void) __attribute__((destructor));
static void	clean_heap(void)
{
	ft_printf("cleaning up !\n");
	foreach_pages(free_page);
	foreach_heap(free_heap, true);
}
