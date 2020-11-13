#include <istar/vga.h>

static unsigned short *vram = (void *)0xB8000;
static unsigned char vga_x = 0;
static unsigned char vga_y = 0;

static void
vga_scroll_up(void)
{
	unsigned int    y;
	unsigned int    x;

	for (y = 1; y < VGA_HEIGHT; y++)
	{
		for (x = 0; x < VGA_WIDTH; x++)
		{
			vram[(y - 1) * 80 + x] = vram[y * 80 + x];
		}
	}

	/*
	 * clear last line 
	 */
	vga_y = VGA_HEIGHT - 1;
	for (x = 0; x < VGA_WIDTH; x++)
	{
		vram[vga_y * 80 + x] = 0x0020;
	}
}

void
vga_putchar(char c, unsigned char fg, unsigned char bg)
{
	unsigned char   color;

	if (c == '\n')
	{
		vga_y++;
		vga_x = 0;
		if (vga_y == VGA_HEIGHT)
		{
			vga_scroll_up();
		}
	}
	else
	{
		color = fg | (bg << 4);
		vram[vga_y * 80 + vga_x] = c | (color << 8);
		vga_x++;
	}
}

void
vga_putstr(const char *str)
{
	const char     *s;

	for (s = str; *s != '\0'; s++)
		vga_putchar(*s, 0xF, 0);
}
