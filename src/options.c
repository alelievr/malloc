/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 00:42:02 by alelievr          #+#    #+#             */
/*   Updated: 2016/12/22 02:08:20 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc_internal.h"

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

t_malloc_info		*get_malloc_info(void)
{
	static t_malloc_info		info;

	return &info;
}
