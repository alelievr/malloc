/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 23:28:18 by alelievr          #+#    #+#             */
/*   Updated: 2017/01/13 23:14:06 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <unistd.h>
#include <stdio.h>

int		main(int ac, char **av, char **environ)
{
	int		i;
	char	*bin = "/bin/ls";

	printf("executing %s binary ...\n", bin);

	char	*args[] = {bin, "-Gl", NULL};
	char	*env[0xF00] = {"DYLD_INSERT_LIBRARIES=/Users/alelievr/c/ft_malloc/libft_malloc_x86_64_Darwin.so", "DYLD_FORCE_FLAT_NAMESPACE=1"};

	i = 0;
	while (environ[i])
	{
		env[i + 2] = environ[i];
		i++;
	}
	env[i + 2] = NULL;

	execve(bin, args, env);
}
