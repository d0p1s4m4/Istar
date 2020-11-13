#ifndef _ISTAR_VGA_H_
# define _ISTAR_VGA_H_

# define VGA_WIDTH 80
# define VGA_HEIGHT 25

void            vga_putchar(char, unsigned char, unsigned char);
void            vga_putstr(const char *);

#endif							/* !_ISTAR_VGA_H_ */
