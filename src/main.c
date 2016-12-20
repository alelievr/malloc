/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/24 02:55:01 by alelievr          #+#    #+#             */
/*   Updated: 2016/12/09 21:11:29 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	mallopt(int flag, int value)
{
	if (flag == M_LIMIT_PAGES)
	{
		get_malloc_info()->max_pages = value;
		return ;
	}
	if (value)
		get_malloc_info()->debug_flag |= 1 << flag;
	else
		get_malloc_info()->debug_flag &= ~(1 << flag);
}

void	*realloc(void *ptr, size_t size)
{
	(void)ptr;
	(void)size;
	return (NULL);
}

void	*malloc(size_t size)
{
	if (size > get_malloc_info()->max_page_size)
		return (fatalloc(size));
	if (size < get_malloc_info()->max_page_size)
		if (!alloc_first_area_found(size))
			return (allocate_new_area(size));
	return (NULL);
}

void	free(void *ptr)
{
	int		index;

	if (!ptr)
	{
		if (DEBUG_PRINT)
			ERR("atempt to free nullptr\n");
		if (DEBUG_ABORT)
			abort();
		return ;
	}
	if ((index = find_fatallocated_addr(ptr)))
		free_fatalloc(index);
	else if ((index = find_allocated_addr(ptr)))
		free_alloc(index);
}

void	show_alloc_mem_ex(void)
{
	t_heap		*heap;
	int			i;

	heap = get_heap();
	i = -1;
	while (++i < 256)
		if (heap->pages[i].addr)
			hexdump_page(heap->pages + i);
}

int		main(void)
{
	void	*ptr = malloc(100);
	free(ptr);
	ptr = NULL;
	while (42);
	return (0);
}
