/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/22 00:43:02 by alelievr          #+#    #+#             */
/*   Updated: 2016/12/22 02:21:09 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc_internal.h"

static void	*realloc_large_page(t_heap *h, int index, void *ptr, size_t size)
{
	t_page		*new;

	INIT(t_page, *p, h->pages_chunk[index]);
	if ((ptr = mmap_wrapper(ptr, size)) == MAP_FAILED)
	{
		if (!(new = mmap_wrapper(NULL, sizeof(t_page) + size)))
			return NULL;
		//reassign addresses :(
		memcpy(new, p->start - sizeof(t_page), p->total_alloc_size);
		munmap_wrapper(p->start - sizeof(t_page), p->total_alloc_size);
		h->pages_chunk[index] = new;
		return (new->alloc);
	}
	p->end = p->start + size;
	p->alloc->end = p->end;
	p->total_alloc_size = size + sizeof(t_page);
	return p->start;
}

static void	*realloc_ptr_not_found(void)
{
	//do classic print/abort/... stuff
	return NULL;
}

void		*ft_realloc(void *ptr, size_t size)
{
	t_heap		*h;
	int			index;
	t_alloc		*a;

	find_page(ptr, &h, &index);
	if (h == NULL)
		return (realloc_ptr_not_found());
	ALIAS(h->pages_chunk[index], p);
	if (p->page_type == M_LARGE)
		return realloc_large_page(h, index, ptr, size);
	else if (size_to_type(size) == M_LARGE)
	{
		p = large_alloc(size);
		a = find_alloc(p, ptr);
		memcpy(p->start, a->start, a->end - a->start);
	}
	else if (p->page_type == M_TINY && size_to_type(size) == M_SMALL)
	{
		//move alloc content to another page
	}
	else if (p->page_type == M_SMALL && size_to_type(size) == M_TINY)
	{
		//exact reverse of before
	}
	else
		//basic case, no need to change page type
		;
	return NULL;
}
