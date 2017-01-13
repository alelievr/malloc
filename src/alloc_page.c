/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_page.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 13:50:13 by alelievr          #+#    #+#             */
/*   Updated: 2017/01/13 21:38:29 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc_internal.h"

#define ROUND_TO_MIN_SIZE(x, y) (((size_t)x < (size_t)y) ? y : y)

static void	alloc_start_page(t_page *p, t_alloc *free_block, size_t size)
{
	t_alloc		*tmp;

	free_block->start = p->start;
	free_block->end = p->start + size;
	free_block->true_size = size;
	if (p->alloc == NULL)
		p->alloc = free_block;
	else
	{
		tmp = p->alloc;
		p->alloc = free_block;
		p->alloc->next = tmp;
	}
}

static void	alloc_at_page(t_alloc *prev, t_alloc *free_block, size_t size)
{
	t_alloc		*tmp;

	free_block->start = prev->end;
	free_block->end = prev->end + size;
	free_block->true_size = size;
	tmp = prev->next;
	prev->next = free_block;
	free_block->next = tmp;
}

void		update_max_free_bytes_block(t_page *p)
{
	long		max;
	t_alloc		*alloc;
	int			i;

	DEBUG2("updating max free bytes block, old value: %i\n", p->max_free_bytes_block);
	alloc = p->alloc;
	max = 0;
	i = 0;
	if (alloc)
	{
		while (alloc->next)
		{
			if (alloc->next->start - alloc->end > max)
				max = alloc->next->start - alloc->end;
			alloc = alloc->next;
			i++;
		}
		if (p->end - alloc->end > max)
			max = p->end - alloc->end;
		p->max_free_bytes_block = max;
	}
	else
		p->max_free_bytes_block = p->end - p->start;
	if (i == MAX_ALLOCS_IN_PAGE - 1)
		p->max_free_bytes_block = 0;
	DEBUG2("updated max free bytes blocks, new value: %i\n", p->max_free_bytes_block);
}

static void		alloc_page_after_start(t_alloc *alloc, t_alloc *free_alloc_block, size_t size)
{
	bool		allocated;

	allocated = false;
	while (alloc->next)
	{
		if (alloc->next->start - alloc->end > (long)size)
		{
			allocated = true;
			alloc_at_page(alloc, free_alloc_block, size);
			break ;
		}
		alloc = alloc->next;
	}
	//if block was not found between allocs, allocated at the end
	if (!allocated)
	{
		DEBUG3("allocating block at the end of the alloc list\n");
		alloc_at_page(alloc, free_alloc_block, size);
	}
}

void		*alloc_page(t_page *p, size_t size)
{
	t_alloc		*free_alloc_block = NULL;
	t_alloc		*alloc;
	int			i;

	size = ROUND_TO_MIN_SIZE(size, p->page_type);
	DEBUG("alloc page start, alloc block count: %i\n", page_count_allocs(p));
	DEBUG1("free block count: %i\n", page_count_free_allocs(p));
	//find free block
	if (FOR(i = 0, i < MAX_ALLOCS_IN_PAGE, i++))
		if (p->_allocs_buff[i].start == NULL)
		{
			free_alloc_block = p->_allocs_buff + i;
			break ;
		}
	if (!free_alloc_block)
		ft_printf("can't find free alloc block !\n");
	alloc = p->alloc;
	//check if enouth space between strt of page and first allocated block:
	if (alloc == NULL || alloc->start - p->start > (long)size)
		alloc_start_page(p, free_alloc_block, size);
	else
		alloc_page_after_start(alloc, free_alloc_block, size);
	DEBUG1("free block count: %i\n", page_count_free_allocs(p));
	DEBUG("alloc page end, alloc block count: %i\n", page_count_allocs(p));
	if (M_OPT_VERBOSE)
		ft_printf("allocated %s block of [%i] at address: %p\n", type_to_text(size_to_type(size)), size, free_alloc_block->start);
	update_max_free_bytes_block(p);
	return free_alloc_block->start;
}
