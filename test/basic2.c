#include "malloc.h"

int		main(void)
{
	void	*p1, *p2, *p3, *p4;
	mallopt(M_STACKTRACE, 1);
	mallopt(M_PRINT, 1);

	p1 = malloc(10);
	p2 = malloc(10);
	p3 = malloc(10);
	free(p3);
	p4 = malloc(100);
	p4 = malloc(10);
	dump_all();
	free(p4);
	free(p2);
	free(p1);
	dump_all();
}
