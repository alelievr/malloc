/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 02:07:44 by alelievr          #+#    #+#             */
/*   Updated: 2017/01/07 20:38:49 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc_internal.h"

static bool	c_free_page(t_page *p, t_heap *h, int index)
{
	if (M_OPT_VERBOSE)
		ft_printf("freeing page %i (addr: %p)\n", index, p->start);
	munmap_wrapper(p, p->total_alloc_size);
	(void)h;
	(void)index;
	return false;
}

static bool	c_free_heap(t_heap *h)
{
	if (h->allocated)
		munmap_wrapper(h, getpagesize());
	return false;
}

static void	clean_heap(void) __attribute__((destructor));
static void	clean_heap(void)
{
	if (M_OPT_VERBOSE)
		ft_printf("cleaning up !\n");
	foreach_pages(c_free_page);
	foreach_heap(c_free_heap, true);
}
