/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 12:59:46 by alelievr          #+#    #+#             */
/*   Updated: 2017/01/10 19:24:47 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc_internal.h"

static bool		expand = false;
static bool		indent = false;

bool		dump_page(t_page *p)
{
	const char	*ind = (indent) ? "\t" : "";
	char		*color;
	char		*ptr;

	if (p->alloc == NULL)
	{
		ft_printf("%snothing allocated in the page\n", ind);
		return false;
	}
	INIT(int, i, 0);
	INIT(int, j, 0);
	if (FOR(i = 0, i < MAX_ALLOCS_IN_PAGE / 16 && ft_printf("%s%p: ", ind, p->start + i * 16 * p->page_type), ft_printf("\n") && i++))
	{
		if (FOR(j = 0, j < 16, j++))
		{
			ptr = p->alloc->start + (i * 16 + j) * p->page_type;
			color = (find_alloc(p, ptr)) ? M_ALLOCATED_BYTE_COLOR : M_UNALLOCATED_BYTE_COLOR;
			ft_printf("%s%.1x "M_CLEAR_COLOR, color, *ptr);
		}
	}
	ft_printf("\n");
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
	ft_printf("--------|------|----------------|-----------|----------\n");
	if (FOR(i = 0, i < MAX_PAGES_PER_HEAP, i++))
		if (h->pages_chunk[i])
		{
			ALIAS(h->pages_chunk[i], p);
			INIT(int, count_block, 0);
			ALIAS(p->alloc, a);
			while (a)
			{
				count_block++;
				a = a->next;
			}
			ft_printf("-> %.4i | %5s | %.10i     | %.9i | %p\n", i, type_to_string(p->page_type), count_block, p->end - p->start, p->start);
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
