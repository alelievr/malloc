/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   page.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/20 23:25:04 by alelievr          #+#    #+#             */
/*   Updated: 2016/12/21 13:34:55 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"
#include <errno.h>

static t_page		*current_page;

static bool 		new_page_add(t_heap *p)
{
	int		i;

	if (p->free_pages_number != 0)
	{
		if (FOR(i = 0, i < MAX_PAGES_PER_HEAP, i++))
			if (!p->pages_chunk[i])
			{
				p->pages_chunk[i] = current_page;
				p->free_pages_number--;
			}
		return true;
	}
	return false;
}

t_page		*new_page(size_t size)
{
	t_page		*p;

	if (size > 0 && size <= M_TINY)
		size = M_TINY_PAGE;
	else if (size > M_TINY && size <= M_SMALL)
		size = M_SMALL_PAGE;

	if (!(p = mmap_wrapper(size + sizeof(t_page))))
		return NULL;
	p->page_type = (size > 0 && size <= M_TINY) ? M_TINY : TER(size > M_TINY && size <= M_SMALL, M_SMALL, M_LARGE);
	p->max_free_bytes_block = size;
	p->total_alloc_size = size + sizeof(t_page);
	p->start = (void *)p + sizeof(t_page);
	p->end = (void *)p + size + sizeof(t_page);
	p->alloc = NULL;
	LOCK;
	current_page = p;
	if (!foreach_heap(new_page_add, false))
		ft_exit("can't append new allocated page\n");
	UNLOCK;
	return p;
}

static bool	delete_page_from_heap(t_page *p, t_heap *h, int index)
{
	if (p != current_page)
		return (false);
	h->pages_chunk[index] = NULL;
	h->free_pages_number++;
	munmap(p->start, p->end - p->start);
	return (true);
}

void		delete_page(t_page *p)
{
	LOCK;
	current_page = p;
	foreach_pages(delete_page_from_heap);
	UNLOCK;
}

bool		foreach_pages(t_page_callback f)
{
	t_heap	*heap;
	int		i;
	bool	succeed;

	succeed = false;
	heap = get_heap();
	while (heap)
	{
		if (FOR(i = 0, i < MAX_PAGES_PER_HEAP, i++))
		{
			if (!heap->pages_chunk[i])
				continue ;
			if (f(heap->pages_chunk[i], heap, i))
			{
				succeed = true;
				GOTO(end);
			}
		}
		heap = heap->next;
	}
	end:
	return succeed;
}
