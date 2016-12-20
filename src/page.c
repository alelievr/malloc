/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   page.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/20 23:25:04 by alelievr          #+#    #+#             */
/*   Updated: 2016/12/21 00:37:29 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"
#include <errno.h>

static t_heap		*g_heap;
static t_page		*current_deleting_page;

t_page		*new_page(size_t size)
{
	void		*alloc;

	if (size > 0 && size <= M_TINY)
		size = M_TINY_PAGE;
	else if (size > M_TINY && size <= M_SMALL)
		size = M_SMALL_PAGE;

	if ((alloc = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, 0, 0)) == MAP_FAILED)
	{
		if (DEBUG_PRINT)
			ft_printf("mmap error: %s\n", ft_perror(errno));
		if (DEBUG_ABORT)
			abort();
		if (DEBUG_STACKTRACE)
			stacktrace();
	}
}

static bool	delete_page_from_heap(t_page *p, t_heap *h, int index)
{
	if (p != current_deleting_page)
		return (false);
	h->pages_chunk[index] = NULL;
	h->free_pages_number++;
	munmap(p->start, p->end - p->start);
	return (true);
}

void		delete_page(t_page *p)
{
	LOCK;
	current_deleting_page = p;
	foreach_pages(delete_page_from_heap);
	UNLOCK;
}

void		foreach_pages(t_callback *f)
{
	t_heap	*heap;
	int		i;

	heap = g_heap;
	while (heap)
	{
		if (FOR(i = 0, i < MAX_PAGES_PER_HEAP, i++))
		{
			if (f(heap->pages_chunk[i], heap, i))
				GOTO(end);
		}
		heap = heap->next;
	}
	end:
}
