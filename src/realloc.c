/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/22 00:43:02 by alelievr          #+#    #+#             */
/*   Updated: 2017/01/13 23:49:57 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc_internal.h"

#define MIN(x, y) ((x < y) ? x : y)

#define UPDATE_ALLOC(alloc, st, en, siz) alloc->start = st; alloc->end = en; alloc->true_size = siz;

static void	*realloc_large_page(t_heap *h, int index, void *ptr, size_t size)
{
	t_page		*new;

	INIT(t_page, *p, h->pages_chunk[index]);
	if (M_OPT_VERBOSE)
		ft_printf("reallocating large page from %io to %io\n", p->alloc->end - p->alloc->start, size);
	if ((ptr = mmap_wrapper(ptr, sizeof(t_page) + size)) == MAP_FAILED)
	{
		DEBUG1("mmap failed to enlarge initial memory block, reallocating new block\n");
		if (!(new = mmap_wrapper(NULL, sizeof(t_page) + size)))
			return NULL;
		//reassign addresses :(
		ft_memcpy(new, p->start - sizeof(t_page), MIN(p->total_alloc_size, size));
		UPDATE_ALLOC(new->alloc, p->start, p->end, size);
		munmap_wrapper(p->_page_alloc_ptr - sizeof(t_page), p->total_alloc_size);
		h->pages_chunk[index] = new;
		return (new->alloc);
	}
	ALIAS((t_page *)ptr, new_page);
	ft_memcpy(new_page, p, sizeof(t_page));
	new_page->end = new_page->start + size;
	UPDATE_ALLOC(new_page->alloc, new_page->start, new_page->end, size);
	new_page->total_alloc_size = size + sizeof(t_page);
	return p->start;
}

static void	*realloc_ptr_not_found(void)
{
	if (M_OPT_PRINT)
		ERR("bad pointer passed to realloc !\n");
	if (M_OPT_ABORT)
		abort();
	if (M_OPT_STACKTRACE)
		stacktrace();
	return NULL;
}

static void	*ft_realloc_switch_page(void *ptr, t_heap *h, int index, size_t new_size)
{
	t_alloc		*a;
	void		*ret;

	if (M_OPT_VERBOSE)
		ft_printf("can't find space required for realloc, copying all datas to a new page\n");
	ALIAS(h->pages_chunk[index], p);
	a = find_alloc(p, ptr);
	ret = ft_alloc(NULL, new_size);
	ft_memcpy(ret, a->start, a->end - a->start);
	free_alloc(p, a);
	return (ret);
}

static void	*ft_realloc_basic(void *ptr, t_heap *h, int index, size_t size)
{
	t_alloc		*a;

	ALIAS(h->pages_chunk[index], p);
	if (!(a = find_alloc(p, ptr)))
	{
		if (M_OPT_VERBOSE)
			ft_printf("bad pointer passed to realloc, NULL.\n");
		if (M_OPT_ABORT)
			abort();
		if (M_OPT_STACKTRACE)
			stacktrace();
		return (NULL);
	}
	if ((a->next == NULL && (size_t)(p->end - a->end) > size)
			|| (a->next != NULL && (size_t)(a->next->start - a->end) > size))
	{
		if (M_OPT_VERBOSE)
			ft_printf("altering allocated size: from %i to %i\n", a->end - a->start, size);
		a->end = a->start + size;
		update_max_free_bytes_block(p);
		return (ptr);
	}
	else
		return (ft_realloc_switch_page(ptr, h, index, size));
}

void		*ft_realloc(void *ptr, size_t size)
{
	t_heap		*h;
	t_alloc		*a;
	t_page		*new_page;
	int			index;

	DEBUG("realloc start\n");
	if (!find_page(ptr, &h, &index))
	{
		if (M_OPT_VERBOSE)
			ft_printf("bad address passed to realloc, NULL.\n");
		return (NULL);
	}
	if (h == NULL)
		return (realloc_ptr_not_found());
	ALIAS(h->pages_chunk[index], p);
	if (p->page_type == M_LARGE)
		return realloc_large_page(h, index, ptr, size);
	else if (size_to_type(size) == M_LARGE)
	{
		a = find_alloc(p, ptr);
		new_page = large_alloc(size, a->start, a->end - a->start);
		add_new_page_to_heap(new_page);
		free_alloc(p, a);
		return (new_page->start);
	}
	else if ((p->page_type == M_TINY && size_to_type(size) == M_SMALL)
			|| (p->page_type == M_SMALL && size_to_type(size) == M_TINY))
		return ft_realloc_switch_page(ptr, h, index, size);
	else
		return ft_realloc_basic(ptr, h, index, size);
	return (NULL);
}
