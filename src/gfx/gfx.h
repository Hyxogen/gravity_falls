#ifndef GFX_H
#define GFX_H

#include <sys/types.h>
#include "map/map.h"

typedef struct imbuffer_s imbuffer_t;
typedef struct screen_s screen_t;

typedef void (*scr_flush_proc)(const imbuffer_t *buffer, void *usr_ptr);

struct imbuffer_s {
	unsigned char *buffer;
	int width;
	int height;
	int bpp;
};

struct screen_s {
	imbuffer_t buffer;
	void *usr_ptr;
	scr_flush_proc flush_proc;
};

void ib_new(imbuffer_t *buffer, int width, int height, int bpp);
void ib_destroy(imbuffer_t *buffer);

void ib_put(imbuffer_t *buffer, int x, int y, void *val, size_t size);
void ib_putb(imbuffer_t *buffer, int x, int y, unsigned char val);
void ib_clear(imbuffer_t *buffer);
void ib_clearb(imbuffer_t *buffer, unsigned char val);

void scr_new(screen_t *scr, int width, int height, int bpp, scr_flush_proc proc);
void src_flush(const screen_t *scr);
void scr_clear(const screen_t *src);

void term_proc(const imbuffer_t *buffer, void *usr_ptr);

void _render_hex(imbuffer_t *buffer, int hex_x, int hex_y, char val);
void render_map(imbuffer_t *buffer, const hexagon_t *map);
#endif
