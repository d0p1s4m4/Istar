#include <istar/types.h>
#include <stdint.h>

void *
memset(void *str, int c, uintptr_t n)
{
	uint8_t *ptr;

	ptr = str;
	while (n--)
	{
		*ptr++ = c;
	}

	return (str);
}
