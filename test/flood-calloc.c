/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood-calloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 13:06:23 by alelievr          #+#    #+#             */
/*   Updated: 2017/01/13 13:15:31 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "malloc.h"
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define MAX_SIZE	0x3FF

int		main(void)
{
	void		*ptr;
	size_t		s;
	static char	buff[MAX_SIZE] = {0};

	srand(time(NULL) + clock());
	for (int i = 0; i < 2000; i++)
	{
		s = rand() & MAX_SIZE;
		ptr = calloc(1, s);
		if (memcmp(buff, ptr, s))
		{
			printf("error !\n");
			abort();
		}
		else
			printf("OK\n");
	}
	return (0);
}
