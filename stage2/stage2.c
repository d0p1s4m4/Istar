#include <istar/vga.h>

void
_start(void)
{
	vga_putstr("\nHello stage2");

	while (1);
}
