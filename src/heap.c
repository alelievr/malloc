/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 01:05:59 by alelievr          #+#    #+#             */
/*   Updated: 2016/12/22 02:08:10 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc_internal.h"

t_heap		*get_heap(void)
{
	static t_heap		*heap = NULL;
	static bool			init = false;

	if (init)
		return heap;
	init = true;
	if (heap == NULL)
		heap = alloc_and_append_new_heap();
	return heap;
}

t_heap		*alloc_and_append_new_heap(void)
{
	t_heap		*h[4];
	t_heap		*current_heap;
	static int	index = 0;

	if ((h[0] = mmap_wrapper(NULL, getpagesize())) == MAP_FAILED)
		ft_exit("failed to initialize malloc !\n");
	h[1] = h[0] + 1;
	h[2] = h[1] + 1;
	h[3] = NULL;
	h[0]->allocated = 1;
	h[1]->allocated = 0;
	h[2]->allocated = 0;
	if (FOREACH(h, he))
	{
		he->free_pages_number = MAX_PAGES_PER_HEAP;
		he->index = index++;
		ft_memset(he->pages_chunk, 0, sizeof(he->pages_chunk));
		he->next = NULL;
		current_heap = get_heap();
		if (current_heap)
		{
			while (current_heap->next)
				current_heap = current_heap->next;
			current_heap->next = he;
		}
	}
	return (h[0]);
}

bool		foreach_heap(t_heap_callback f, bool alwaysfalse)
{
	t_heap		*h;
	t_heap		*next;
	bool		succeed;

	succeed = false;
	h = get_heap();
	while (h)
	{
		next = h->next;
		if (f(h))
		{
			succeed = true;
			break ;
		}
		h = next;
	}
	if (!succeed && !alwaysfalse)
		f(alloc_and_append_new_heap());
	return succeed;
}
