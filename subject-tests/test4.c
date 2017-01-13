#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#define Mo (1024 * 1024)

void	print(char *s)
{
	write(1, s, strlen(s));
}


int		main(void)
{
	char *addr;

	addr = malloc(16);
	free(NULL);
	free((void *)addr + 5);
	if (realloc((void *)addr + 5, 10) == NULL)
		print("Bonjours\n");
	return (0);
}