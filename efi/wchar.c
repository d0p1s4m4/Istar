#include "istar/efi/types.h"
#include <istar/types.h>

wchar_t *
char_to_wchar(wchar_t *dest, char *src, size_t size)
{
	size_t i;

	if (dest != NULL)
	{
		for (i = 0; i < size && src[i] != 0; i++)
		{
			dest[i] = src[i];
		}
		dest[size] = 0;
	}

	return (dest);
}
