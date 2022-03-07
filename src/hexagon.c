#include <stdio.h>

/* Werkt nog niet met len <= 2 */
void draw_hex_line(int pad, int len, char fill, char left, char right) {
	int i;

	for (i = 0; i < pad; i++)
		printf(" ");
	len -= 2;
	printf("%c", left);
	for (i = 0; i < len; i++)
		printf("%c", fill);
	printf("%c\n", right);
}

void draw_hex(int sidelen) {
	int i;

	draw_hex_line(sidelen, sidelen, '-', '/', '\\');
	for (i = 1; i < (sidelen / 2); i++)
		draw_hex_line(sidelen - i, sidelen + (2 * i), ' ', '/', '\\');
	for (i = (sidelen / 2) - 1; i > 0; i--)
		draw_hex_line(sidelen - i, sidelen + (2 * i), ' ', '\\', '/');
	draw_hex_line(sidelen, sidelen, '-', '\\', '/');
}

int main(void) {
	draw_hex(10);
	return 0;
}