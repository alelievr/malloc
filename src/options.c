/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 00:42:02 by alelievr          #+#    #+#             */
/*   Updated: 2017/01/08 23:08:56 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc_internal.h"
#include <signal.h>

void	sigh(int s)
{
	ft_printf(M_ERROR_COLOR"catched [%s] !\n", strsignal(s));
	stacktrace();
}

void	mallopt(int flag, int value)
{
	if (flag == M_LIMIT_PAGES)
	{
		get_malloc_info()->max_pages = value;
		return ;
	}
	if (flag == M_CHECK_CATCH)
	{
		signal(SIGSEGV, sigh);
		signal(SIGBUS, sigh);
		signal(SIGILL, sigh);
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
