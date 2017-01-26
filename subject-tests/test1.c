#include <stdlib.h> 
#include "malloc.h"

int main() 
{ 
int i; 
char *addr; 

i = 0; 
mallopt(M_VERBOSE, 1);
while (i < 1024) 
{
addr = (char*)malloc(1024);	
addr[0] = 42;
i++; 
} 
return (0); 
} 
