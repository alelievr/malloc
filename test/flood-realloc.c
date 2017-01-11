/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood-realloc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 19:17:40 by alelievr          #+#    #+#             */
/*   Updated: 2017/01/11 01:25:50 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "libft.h"

#define SIZE	2000
#define WHILE(x) i = SIZE; while (x)

int			main(void)
{
	int		i;
	void	*ptrs[SIZE];

	mallopt(M_VERBOSE, 1);

	WHILE (i --> 0)
		ptrs[i] = malloc(24);

	WHILE (i --> 0)
		ptrs[i] = realloc(ptrs[i], 120);

	WHILE (i --> SIZE / 2)
		ptrs[i] = realloc(ptrs[i], 2000);

	ft_printf("first dump:\n");
	dump_all();

	WHILE (i --> 0)
		free(ptrs[i]);

	ft_printf("second dump:\n");
	dump_all();
}
