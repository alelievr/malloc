/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 21:14:23 by alelievr          #+#    #+#             */
/*   Updated: 2017/01/13 21:52:04 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc_internal.h"

static int	g_type;

static bool	show_alloc_mem_callback(t_page *p, t_heap *h, int index)
{
	if (p->page_type == g_type)
	{
		ALIAS(p->alloc, a);
		while (a)
		{
			ft_printf("%p - %p : %i octects\n", a->start, a->end, a->true_size);
			a = a->next;
		}
	}
	(void)index;
	(void)h;
	return false;
}

void		show_alloc_mem(void)
{
	static int types[] = {M_TINY, M_SMALL, M_LARGE, 0};

	LOCK;
	if (FOREACH(types, type))
	{
		g_type = type;
		foreach_pages(show_alloc_mem_callback);
	}
	UNLOCK;
}

void		show_alloc_mem_ex(void)
{

}
