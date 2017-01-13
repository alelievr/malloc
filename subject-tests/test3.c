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
	char *addr1;
	char *addr3;

	addr1 = (char *)malloc(16 * Mo);
	strcpy(addr1, "Bonjours\n");
	print(addr1);
	addr3 = (char *)realloc(addr1, 128 * Mo);
	addr3[127 * Mo] = 42;
	print(addr3);
	return (0);
}
