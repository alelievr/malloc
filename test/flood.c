/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 20:49:34 by alelievr          #+#    #+#             */
/*   Updated: 2017/01/11 02:37:40 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

#define SIZE	200000

int		main(void)
{
	void	*ptrs[SIZE];

	mallopt(M_VERBOSE, 1);
	for (int i = 0; i < SIZE; i++)
		ptrs[i] = malloc(23);

	for (int i = 0; i < SIZE; i++)
		free(ptrs[i]);
}
