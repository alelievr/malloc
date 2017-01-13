/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/22 00:43:40 by alelievr          #+#    #+#             */
/*   Updated: 2017/01/14 00:11:27 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc_internal.h"

void		ft_free(void *ptr)
{
	t_heap		*heap;
	t_alloc		*a;
	int			index;

	DEBUG("free start\n");
	if (!ptr && M_OPT_VERBOSE)
	{
		ft_printf("NULL passed for free\n");
		return ;
	}
	if (!find_page(ptr, &heap, &index)
			|| (!(a = find_alloc(heap->pages_chunk[index], ptr))))
	{
		if (M_OPT_VERBOSE)
			ft_printf("non allocated address passed to free\n");
		return ;
	}
	ALIAS(heap->pages_chunk[index], p);
	if (M_OPT_VERBOSE)
		ft_printf("freed %s page at [%p]\n", type_to_text(p->page_type, false), ptr);
	if (p->page_type == M_LARGE)
		free_page(p);
	else
		free_alloc(p, a);
	DEBUG("free end\n");
	(void)ptr;
}
