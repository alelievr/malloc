/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood-large.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 13:34:00 by alelievr          #+#    #+#             */
/*   Updated: 2017/01/13 14:58:16 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <time.h>
#include <stdlib.h>

#define SIZE		100

int		main(void)
{
	void	*ptr[SIZE];

	mallopt(M_VERBOSE, 1);
	srand(time(NULL));

	for (int j = 0; j < 20; j++)
	{
		for (int i = 0; i < SIZE; i++)
			ptr[i] = malloc(rand() & 0xFF0);
		for(int i = 0; i < SIZE; i++)
			free(ptr[i]);
	}
}
