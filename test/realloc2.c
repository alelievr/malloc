/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 13:15:51 by alelievr          #+#    #+#             */
/*   Updated: 2017/01/13 13:33:10 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "malloc.h"
#include <stdio.h>

int		main(void)
{
	void	*ptr;
	char	*str = "hello it's me !\n";

	ptr = malloc(30);
	strcpy(ptr, str);
	ptr = realloc(ptr, 2000);
	printf("copied string:\n");
	printf("%s", ptr);
	if (strcmp(ptr, str))
		abort();

	ptr = malloc(1000);
	strcpy(ptr, str);
	ptr = realloc(ptr, 2000);
	printf("copied string:\n");
	printf("%s", ptr);
	if (strcmp(ptr, str))
		abort();
	fflush(stdout);
}
