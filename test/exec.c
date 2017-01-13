/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 23:28:18 by alelievr          #+#    #+#             */
/*   Updated: 2017/01/13 01:47:27 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <unistd.h>
#include <stdio.h>

int		main(int ac, char **av, char **environ)
{
	int		i;
	printf("executing %s binary ...\n", "bash");

	char	*bin[] = {"bash", NULL};
	char	*env[0xF00] = {"DYLD_INSERT_LIBRARIES=/Users/alelievr/c/ft_malloc/libft_malloc_x86_64_Darwin.so", "DYLD_FORCE_FLAT_NAMESPACE=1"};

	i = 0;
	while (environ[i])
	{
		env[i + 2] = environ[i];
		i++;
	}
	env[i + 2] = NULL;

	execve("/bin/bash", bin, env);
}
