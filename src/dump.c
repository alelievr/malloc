/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 12:59:46 by alelievr          #+#    #+#             */
/*   Updated: 2016/12/21 13:59:30 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static bool		expand = false;
static bool		indent = false;

bool		dump_page(t_page *p)
{
	const char	*ind = (indent) ? "\t" : "";
	t_alloc		*alloc;

	if ((alloc = p->alloc) == NULL)
	{
		ft_printf("%snothing allocated in the page\n", ind);
		return false;
	}
	while (alloc)
	{
		ft_sprintf("allocated: %p - %p\n", alloc->start, alloc->end);
		alloc = alloc->next;
	}
	return true;
}

static const char	*type_to_string(int type)
{
	if (type == M_TINY)
		return "TINY";
	else if (type == M_SMALL)
		return "SMALL";
	else
		return "LARGE";
}

bool		dump_heap(t_heap *h)
{
	int		i;

	indent = true;
	if (h->free_pages_number == MAX_PAGES_PER_HEAP)
	{
		ft_printf("no allocated pages in the heap block [%i]\n", h->index);
		return (false);
	}
	ft_printf("dumping all pages in the heap block [%i]\n", h->index);
	ft_printf("page id | type | blocks in page | page size | start ptr\n");
	ft_printf("-------------------------------------------------------\n");
	if (FOR(i = 0, i < MAX_PAGES_PER_HEAP, i++))
		if (h->pages_chunk[i])
		{
			ALIAS(h->pages_chunk[i], p);
			ft_printf("-> %.3i | %5s | %.8i | %p\n", i, type_to_string(p->page_type), p->end - p->start, p->start);
			if (expand)
				dump_page(p);
		}
	indent = false;
	return (true);
}

bool		dump_all(void)
{
	LOCK;
	expand = true;
	foreach_heap(dump_heap, true);
	expand = false;
	UNLOCK;
	return true;
}
