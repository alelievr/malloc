/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   page_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 00:31:57 by alelievr          #+#    #+#             */
/*   Updated: 2017/01/13 00:40:09 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc_internal.h"

int		page_count_allocs(t_page *p)
{
	int		i;

	i = 0;
	ALIAS(p->alloc, a);
	while (a)
	{
		a = a->next;
		i++;
	}
	return (i);
}

int		page_count_free_allocs(t_page *p)
{
	int		i;
	int		j;

	j = 0;
	if (FOR(i = 0, i < MAX_ALLOCS_IN_PAGE, i++))
		if (p->_allocs_buff[i].start == NULL)
			j++;
	return (j);
}
