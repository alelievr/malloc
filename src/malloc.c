/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/24 16:34:51 by alelievr          #+#    #+#             */
/*   Updated: 2016/12/20 22:46:11 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"
#include <sys/mman.h>

#include <string.h>
t_heap			*get_heap(void)
{
	static t_heap	heap;
	static int		init = 0;
	int				i;

	if (!init)
	{
		i = -1;
		bzero(&heap, sizeof(heap));
		heap.infos.debug_flag = 0;
		heap.infos.max_page_size = getpagesize();
		heap.infos.max_pages = M_UNLIMITED;
		init = 1;
	}
	return (&heap);
}

t_malloc_info	*get_malloc_info(void)
{
	return (&(get_heap()->infos));
}

void			add_allocated_area(t_page *p, int index, size_t size, void *tmp)
{
	int		i;

	(void)index;
	i = -1;
	while (++i < 128)
		if (!p->alloc.allocs[i].addr)
		{
			p->alloc.allocs[i].addr = tmp;
			p->alloc.allocs[i].size = size;
		}
}

void			*find_free_zone_in_page(t_page *p, size_t size)
{
	int		i;
	void	*tmp;

	tmp = NULL;
	while (42)
	{
		i = -1;
		while (++i < 128)
		{
			if (p->alloc.allocs[i].addr && tmp)
			{
				if ((size_t)p->alloc.allocs[i].addr - (size_t) tmp >= size)
				{
					add_allocated_area(p, i, size, tmp);
					return (tmp);
				}
			}
			if (p->alloc.allocs[i].addr)
				tmp = (void *)((size_t)p->alloc.allocs[i].addr + p->alloc.allocs[i].size);
		}
		if (p->next)
			p = p->next;
		else
			break ;
	}
	return (NULL);
}

void			*alloc_first_area_found(size_t size)
{
	t_heap			*heap;
	void			*ret;
	int				i;

	heap = get_heap();
	i = -1;
	while (++i < 256)
		if ((ret = find_free_zone_in_page(heap->pages + i, size)))
			return (ret);
	return (NULL);
}

void			*allocate_new_area(size_t size)
{
	
}

void			*mmap_wrapper(size_t size)
{
	void	*ptr;

	if ((ptr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANON, 0, 0)) == MAP_FAILED)
	{
		if (DEBUG_PRINT)
			ERR("failed to allocate memory\n");
		if (DEBUG_STACKTRACE)
			stacktrace();
		if (DEBUG_ABORT)
			abort();
	}
	return (ptr);
}

void			munmap_wrapper(void *addr, size_t size)
{
	if ((munmap(addr, size)) == -1)
	{
		if (DEBUG_PRINT)
			ERR("failed to free memory\n");
		if (DEBUG_ABORT)
			abort();
	}
}

#include <stdio.h>
void			hexdump_page(t_page *p)
{
	size_t	i;
	int		alloc;

	i = 0;
	if (p->addr)
		while (i < p->size)
		{
			for (int j = 0; j < 128; j++)
				if (p->alloc.allocs[j].addr)
				{
					alloc = 1;
					break ;
				}
			if (i < p->size - 1)
				printf("\033[38;5;%im%hhx%hhx ", (alloc) ? 42 : 93, *(char *)(p->addr + i), *(char *)(p->addr + i + 1));
			i += 2;
		}
}

void			hexdump_allocated(t_allocated *a)
{
	printf("big area: %p - %p (%zu)\n", a->addr, a->addr + a->size, a->size);
}

void			*fatalloc(size_t size)
{
	const t_heap	*heap = get_heap();
	int				i;

	while (42)
	{
		i = -1;
		while (++i < 128)
			if (!heap->fatalloc.allocs[i].addr)
			{
				mmap_wrapper(size);
			}
	}
}

int				find_fatallocated_addr(void *ptr)
{
	t_heap			*heap;
	t_alloc_list	*l;
	int			i;
	int			ret;

	heap = get_heap();
	l = &heap->fatalloc;
	ret = 0;
	while (42)
	{
		i = -1;
		while (++i < 128)
			if (l->allocs[i].addr == ptr)
				return (ret + i);
		if (l->next)
			l = l->next;
		else
			break ;
		ret += 128;
	}
	return (-1);
}

int				find_allocated_addr(void *ptr)
{
	t_heap			*heap;
	t_alloc_list	*l;
	int			i;
	int			j;
	int			k;

	heap = get_heap();
	i = -1;
	
	while (++i < 256)
	{
		k = 0;
		if (!heap->pages[i].addr)
			continue ;
		l = &heap->pages[i].alloc;
		while (42)
		{
			j = -1;
			while (++j < 128)
				if (l->allocs[j].addr == ptr)
					return (((char)i << 24) | (short)k << 8 | (char)j);
			if (l->next)
				l = l->next;
			else
				break ;
			k++;
		}
	}
	return (-1);
}

void			free_fatalloc(int index)
{
	t_heap			*heap;
	t_alloc_list	*l;

	heap = get_heap();
	l = &heap->fatalloc;
	while (index >= 128)
	{
		if (l->next)
			l = l->next;
		else
			break ;
	}
	if (index >= 128)
		return ;
	else
		munmap_wrapper(l->allocs[index].addr, l->allocs[index].size);
}

void			free_if_plage_empty(t_alloc_list *l, t_alloc_list *p, int pos)
{
	int		i;

	i = -1;
	while (++i < 128)
		if (l->allocs[i].addr)
			return ;
	if (pos)
	{
		if (l->next && p)
			p->next = l->next;
		free(l);
	}
}

void			free_alloc(index)
{
	const int		i = index & 0xFF000000;
	const int		j = index & 0x000000FF;
	int				k = index & 0x00FFFF00;
	t_heap			*heap;
	t_alloc_list	*l;
	t_alloc_list	*p;
	int				pos;

	pos = 0;
	heap = get_heap();
	l = &heap->pages[i].alloc;
	while (k--)
	{
		p = l;
		l = l->next;
		pos++;
	}
	l->allocs[j].addr = NULL;
	l->allocs[j].size = 0;
	free_if_plage_empty(l, p, pos);
	(void)index;
}
