/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 20:49:34 by alelievr          #+#    #+#             */
/*   Updated: 2017/01/13 17:06:18 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <string.h>

#define SIZE	20000

int		main(void)
{
	void	*ptr;

	mallopt(M_VERBOSE, 1);
	malloc(12);
	for (int i = 0; i < SIZE; i++)
	{
		ptr = malloc(23);
		memset(ptr, 'A', 23);
		free(ptr);
	}
}
