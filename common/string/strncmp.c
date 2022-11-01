#include <istar/types.h>

int
strncmp(char const *s1, char const *s2, size_t n)
{
	for (; n > 0; n--)
	{
		if (*s1++ != *s2++)
		{
			return (*(s1 - 1) - *(s2 - 1));
		}
	}

	return (0);
}
