/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/22 01:06:12 by alelievr          #+#    #+#             */
/*   Updated: 2017/01/07 23:23:20 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc_internal.h"

static t_heap	**g_c_heap;
static int		*g_c_index;
static void		*g_c_addr;

static bool	find_page_with_addr(t_page *p, t_heap *h, int index)
{
	if (g_c_addr >= p->start && g_c_addr <= p->end)
	{
		*g_c_index = index;
		*g_c_heap = h;
		return true;
	}
	return false;
}

bool		find_page(void *ptr, t_heap **h, int *i)
{
	g_c_heap = h;
	g_c_index = i;
	g_c_addr = ptr;
	return foreach_pages(find_page_with_addr);
}

t_alloc		*find_alloc(t_page *p, void *ptr)
{
	t_alloc		*a;

	a = p->alloc;
	while (a)
	{
		if (ptr >= a->start && ptr < a->end)
			return (a);
		a = a->next;
	}
	return (NULL);
}

void		free_alloc(t_page *p, t_alloc *a)
{
	t_alloc	*tmp;

	a->start = NULL;
	a->end = NULL;
	if (p->alloc == a)
		p->alloc = a->next;
	else
	{
		tmp = p->alloc;
		while (tmp)
		{
			if (tmp->next == a)
				break ;
			tmp = tmp->next;
		}
		tmp->next = a->next;
	}
	update_max_free_bytes_block(p);
	if (p->alloc == NULL)
		free_page(p);
}
