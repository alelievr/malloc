/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 17:58:41 by alelievr          #+#    #+#             */
/*   Updated: 2017/01/13 21:37:27 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc_internal.h"
static t_page	*g_page;
static int		g_requested_size;
static int		g_type;
static int		g_page_index;

extern int write(int, char *, size_t);

static bool		find_empty_page(t_page *p, t_heap *h, int i)
{
	if (p->page_type == g_type && p->max_free_bytes_block >= g_requested_size)
	{
		g_page = p;
		g_page_index = i;
		return true;
	}
	(void)h;
	(void)i;
	return false;
}

static bool		add_page_to_heap(t_heap *h)
{
	int		i;
	bool	added = false;

	if (h->free_pages_number == 0)
		return false;
	if (FOR(i = 0, i < MAX_PAGES_PER_HEAP, i++))
		if (!h->pages_chunk[i])
		{
			h->pages_chunk[i] = g_page;
			h->free_pages_number--;
			added = true;
			break ;
		}
	return added;
}

void			add_new_page_to_heap(t_page *p)
{
	LOCK;
	g_page = p;
	foreach_heap(add_page_to_heap, false);
	UNLOCK;
}

t_page			*large_alloc(size_t size, void *data, size_t dsize)
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
	p->_page_alloc_ptr = p;
	ALIAS(p->_allocs_buff + 0, alloc);
	alloc->start = p->start;
	alloc->end = p->end;
	alloc->next = NULL;
	alloc->true_size = size;
	if (data)
		memcpy(alloc->start, data, dsize);
	p->alloc = alloc;
	if (M_OPT_VERBOSE)
		ft_printf("allocated large block at address: %p\n", alloc->start);
	DEBUG("large alloc end\n");
	return p;
}

void			*ft_alloc(void *ptr, size_t size)
{
	//mallopt(M_VERBOSE, 1);
	if (size == 0 && ptr != NULL)
	{ ft_free(ptr); return ft_alloc(NULL, MIN_ALLOC_SIZE); }
	if (ptr != NULL)
		return ft_realloc(ptr, size);
	DEBUG("ft_alloc begin\n");
	INIT(void, *ret, NULL);
	g_type = size_to_type(size);
	if (g_type != M_LARGE)
	{
		LOCK;
		g_requested_size = size;
		g_page_index = -1;
		if (!foreach_pages(find_empty_page))
			if (!(g_page = new_page(size, true)))
				GOTO(end);
		UNLOCK;
		{ //this is a debug block
			int i = 0, k = 0;
			i = 128 - page_count_allocs(g_page);
			k = page_count_free_allocs(g_page);
			DEBUG("on page [%i] not alloc number: %i\n", g_page_index, i);
			DEBUG("free alloc block: %i\n", k);
			if (i != k)
			{
				ft_printf("error detected, aborting !\n");
				abort();
			}
		}
		DEBUG("trying to alloc size: %i on page with size %i:\n", size, g_page->max_free_bytes_block);
		ret = alloc_page(g_page, size);
		GOTO(end);
	}
	else
		if (!(g_page = large_alloc(size, NULL, 0)))
			GOTO(end);
		else
			ret = g_page->alloc->start;
	add_new_page_to_heap(g_page);
	end:
	DEBUG("ft_alloc end\n");
	return ret;
}
