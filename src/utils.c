/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 00:29:59 by alelievr          #+#    #+#             */
/*   Updated: 2016/12/21 00:31:09 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static void ft_malloc_init() __attribute__((constructor));
static void ft_malloc_init()
{
	g_malloc_mutex = PTHREAD_MUTEX_INITIALIZER;
}
