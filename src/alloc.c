/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 17:58:41 by alelievr          #+#    #+#             */
/*   Updated: 2017/01/09 01:57:38 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc_internal.h"

static t_page	*g_page;
static int		g_requested_size;
static int		g_type;

static bool		find_empty_page(t_page *p, t_heap *h, int i)
{
	if (p->page_type == g_type && p->max_free_bytes_block >= g_requested_size)
	{
		ft_printf("%i free bytes find in page:\n", g_requested_size);
		dump_page(p);
		g_page = p;
		return true;
	}
	(void)h;
	(void)i;
	return false;
}

static bool		add_page_to_heap(t_heap *h)
{
	int		i;

	if (h->free_pages_number == 0)
		return false;
	if (FOR(i = 0, i < MAX_PAGES_PER_HEAP, i++))
		if (!h->pages_chunk[i])
			h->pages_chunk[i] = g_page;
	return true;
}

static void		add_new_page_to_heap(t_page *p)
{
	LOCK;
	g_page = p;
	foreach_heap(add_page_to_heap, false);
	UNLOCK;
}

t_page		*large_alloc(size_t size)
{
	t_page	*p;

	DEBUG("large alloc start\n");
	if (!(p = mmap_wrapper(NULL, size + sizeof(t_page))))
		return NULL;
	p->page_type = M_LARGE;
	p->max_free_bytes_block = 0;
	p->total_alloc_size = size + sizeof(t_page);
	p->start = (void *)p + sizeof(t_page);
	p->end = p->start + size;
	ALIAS(p->_allocs_buff + 0, alloc);
	alloc->start = p->start;
	alloc->end = p->end;
	alloc->next = NULL;
	p->alloc = alloc;
	if (M_OPT_VERBOSE)
		ft_printf("allocated large block at address: %p\n", alloc->start);
	DEBUG("large alloc end\n");
	return p;
}

extern int write(int, char *, size_t);

void			*ft_alloc(void *ptr, size_t size)
{
	DEBUG("ft_alloc begin\n");
	mallopt(M_VERBOSE, 1);
	if (size == 0 && ptr != NULL)
	{ ft_free(ptr); return ft_alloc(NULL, MIN_ALLOC_SIZE); }
	if (ptr != NULL)
		return ft_realloc(ptr, size);
	INIT(void, *ret, NULL);
	if (g_type != M_LARGE)
	{
		LOCK;
		g_requested_size = size;
		g_type = size_to_type(size);
		if (!foreach_pages(find_empty_page))
			if (!(g_page = new_page(size, true)))
				GOTO(end);
		UNLOCK;
		return alloc_page(g_page, size);
	}
	else
		if (!(g_page = large_alloc(size)))
			GOTO(end);
		else
			ret = g_page->alloc->start;
	add_new_page_to_heap(g_page);
	end:
	DEBUG("ft_alloc end\n");
	return ret;
}
